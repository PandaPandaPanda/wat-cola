#include "bottlingPlant.h"
#include "truck.h"
#include "printer.h"
#include <iostream>

using namespace std;

BottlingPlant::BottlingPlant(Printer& prt, NameServer& nameServer, unsigned int numVendingMachines,
              unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
              unsigned int timeBetweenShipments) 
              : prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments) {
    truck = new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);
    stock = new unsigned int[BottlingPlant::Flavours::NUM_OF_FLAVOURS]();

}

BottlingPlant::~BottlingPlant() {
    delete[] stock;
    if (debug) {cout << "deleting truck" << endl;}
    delete truck;
}

void BottlingPlant::main() {
    PRINT(prt.print(Printer::BottlingPlant, 'S');)
    for (;;) {
        if (!closing) {
            yield(timeBetweenShipments);
            if (debug) {cout << "production run: " << endl;}
            for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                stock[i]=mprng(0, maxShippedPerFlavour);
            }
            if (debug) {
                cout << "stock: ";
                for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                    cout << stock[i] << " ";
                }
                cout << endl;
            }
            PRINT({
                int totalProduced = 0;
                for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                    totalProduced += stock[i];
                }
                
                prt.print(Printer::BottlingPlant, 'G', totalProduced);
            })
        }
        _Accept(getShipment) {
            unsigned int* cargo = (unsigned int*)bp_queue.front();
            bool no_stock = true;
            for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                cargo[i] = stock[i];
                if (stock[i]!=0) {
                    no_stock = false;
                }
                stock[i] = 0;
            }
            if (no_stock && closing) {
                cout << "raising shutdown at truck" << endl;
                _Resume Shutdown() _At *truck;
                bp_queue.signalBlock();
                prt.print(Printer::BottlingPlant, 'F');
                return;
            }
            prt.print(Printer::BottlingPlant, 'P');
            bp_queue.signalBlock();
        } or _Accept(~BottlingPlant) {
            closing = true;
        };
    }
}

void BottlingPlant::getShipment(unsigned int cargo[]) {
    bp_queue.wait((uintptr_t)cargo);
}
