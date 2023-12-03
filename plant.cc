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

}

BottlingPlant::~BottlingPlant() {
    delete[] stock;
}

void BottlingPlant::main() {
    PRINT(prt.print(Printer::BottlingPlant, 'S');)
    for (;;) {
        yield(timeBetweenShipments);
        if (debug) {cout << "production run: " << endl;}
        for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
            stock[i]=prng(0, maxShippedPerFlavour);
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
        _Accept(getShipment) {
            if (closing) {
                bool no_stock = true;
                for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                    if (stock[i]!=0) {
                        no_stock = false;
                        break;
                    }
                }
                if (no_stock) {
                    _Resume Shutdown() _At *truck;
                    return;
                }
            }
            prt.print(Printer::BottlingPlant, 'P');

        } or _Accept(~BottlingPlant) {
            closing = true;
            break;
        };
    }
    prt.print(Printer::BottlingPlant, 'F');
}

void BottlingPlant::getShipment(unsigned int cargo[]) {
    for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
        cargo[i] = stock[i];
    }
}
