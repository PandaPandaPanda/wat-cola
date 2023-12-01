#include "BottlingPlant.h"

using namespace std;

BottlingPlant::BottlingPlant(Printer& prt, NameServer& nameServer, unsigned int numVendingMachines,
              unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
              unsigned int timeBetweenShipments) 
              : prt(prt), nameServer(nameServer), numVendingMachines(numVendingMachines), maxShippedPerFlavour(maxShippedPerFlavour), maxStockPerFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments) {
    truck = Truck::Truck(prt, nameServer, &this, numVendingMachines, maxStockPerFlavour);
    stock = new int[BottlingPlant::Flavours::NUM_OF_FLAVOURS]();

}

BottlingPlant::~BottlingPlant() {
    delete[] stock;
}

void BottlingPlant::main() {
    for (;;) {
        yield(timeBetweenShipments);
        for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
            stock[i]+=prng(0, maxShippedPerFlavour);
            if (stock[i] > maxStockPerFlavour) {
                stock[i] = maxStockPerFlavour;
            }
        }
        _Accept(getShipment) or _Accept(~BottlingPlant) {
            closing = true;
            break;
        };
    }
}

void BottlingPlant::getShipment(unsigned int cargo[]) {
    bool none_copied = true;
    for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
        cargo[i] = stock[i];
        if (none_copied == true && stock[i]!=0) {
            none_copied = false;
        }
        stock[i] = 0;
    }
    if (closing && none_copied) {
        _Resume Shutdown() _At truck;
    }
}
