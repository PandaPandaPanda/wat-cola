#include "truck.h"
#include "bottlingPlant.h"
#include "nameServer.h"
#include "vendingmachine.h"
using namespace std;

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour )
           : prt(prt), nameServer(nameServer), plant(plant), 
           numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {
            cargo = new unsigned int[BottlingPlant::Flavours::NUM_OF_FLAVOURS]();
            machineList = nameServer.getMachineList();
           }

Truck::~Truck() {
    delete[] cargo;
}

void Truck::main() {
    for(;;) {
        yield(prng(0,10));
        try {
            _Enable {
                if (debug) {
                    cout << "cur cargo: ";
                    for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                        cout << cargo[i] << " ";
                    }
                    cout << endl;
                }
                plant.getShipment(cargo);
                if (debug) {
                    cout << "cur cargo: ";
                    for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                        cout << cargo[i] << " ";
                    }
                    cout << endl;
                }
            }
        } _Catch(BottlingPlant::Shutdown & e) {
            return;
        }
        for (int servedVending = 0; servedVending < numVendingMachines; servedVending+=1) {
            bool noCargo = true;
            cout << "calling inventory" << endl;
            for (int i = 0; i < 3; i+=1) {
                cout << machineList[i]->getId();
            } 
            unsigned int* machineInventory = machineList[curMachine]->inventory();
            for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                unsigned int neededStock = maxStockPerFlavour - machineInventory[i];
                if (noCargo && cargo[i]!=0) {
                    noCargo = false;
                }
                if (neededStock > cargo[i]) {
                    machineInventory[i] += cargo[i];
                    cargo[i] = 0;
                } else {
                    machineInventory[i]+=neededStock;
                    cargo[i]-=neededStock;
                }
            }
            if (debug) {
                cout << "restocked: ";
                for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                    cout << machineInventory[i] << " ";
                }
                cout << endl;
                cout << "leftover cargo: ";
                for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                    cout << cargo[i] << " ";
                }
                cout << endl;
            }
            if (prng(100) == 42) {
                yield(10);
            }
            if (noCargo) {
                break;
            }
            curMachine = (1+curMachine) % numVendingMachines;
        }

    }
}

