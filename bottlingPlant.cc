#include "bottlingPlant.h"
#include "truck.h"
#include "printer.h"

using namespace std;

BottlingPlant::BottlingPlant(Printer& prt, NameServer& nameServer, unsigned int numVendingMachines,
              unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
              unsigned int timeBetweenShipments) 
              : prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments) {
    truck = new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);
    stock = new unsigned int[BottlingPlant::Flavours::NUM_OF_FLAVOURS]();
} // BottlingPlant ctor

BottlingPlant::~BottlingPlant() {
    delete[] stock;
    delete truck;
} // BottlingPlant dtor 

void BottlingPlant::main() {
    PRINT(prt.print(Printer::BottlingPlant, 'S');)
    for (;;) {
        if (!closing) {                                                                 // start production run if plant is not closing                               
            yield(timeBetweenShipments);
            for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                stock[i]=mprng(0, maxShippedPerFlavour);                                // production run - replace stock with newly produced soda
            } // for
            PRINT({
                int totalProduced = 0;
                for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                    totalProduced += stock[i];
                } // for
                
                prt.print(Printer::BottlingPlant, 'G', totalProduced);
            }) // PRINT
        } // if
        _Accept(getShipment) {
            unsigned int* cargo = (unsigned int*)bp_queue.front();                      // get cargo pointer from shadow queue
            bool no_stock = true;                                                       // check if there is stock in plant
            for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {       // restock truck cargo
                cargo[i] = stock[i];
                if (stock[i]!=0) {
                    no_stock = false;
                } // if
                stock[i] = 0;
            } // for
            if (no_stock && closing) {                                                  // throw shutdown if plant is closing and no shipment is copied in (no stock)
                _Resume Shutdown() _At *truck;
                bp_queue.signalBlock();                                                 // let getShipment caller (truck) continue and terminate
                prt.print(Printer::BottlingPlant, 'F');
                return;                                                                 // terminate plant
            } // if
            prt.print(Printer::BottlingPlant, 'P');
            bp_queue.signalBlock();                                                     // let getShipment caller (truck) continue 
        } or _Accept(~BottlingPlant) {
            closing = true;                                                             // plant is closing on dtor call - no more production runs
        } // _Accept
    } // for
} // BottlingPlant::main

void BottlingPlant::getShipment(unsigned int cargo[]) {                     // pass param to main via shadow queue
    bp_queue.wait((uintptr_t)cargo);
} // BottlingPlant::getShipment
