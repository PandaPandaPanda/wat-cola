#include "truck.h"
#include "bottlingPlant.h"
#include "nameServer.h"
#include "vendingmachine.h"
#include "printer.h"
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
    PRINT(prt.print(Printer::Truck, 'S');)
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
                PRINT({
                    int totalPickedUp = 0;
                    for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                        totalPickedUp += cargo[i];
                    }
                    
                    prt.print(Printer::Truck, 'P', totalPickedUp);
                })
                if (debug) {
                    cout << "cur cargo: ";
                    for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                        cout << cargo[i] << " ";
                    }
                    cout << endl;
                }
            }
        } _Catch(BottlingPlant::Shutdown & e) {
            if(debug){cout << "TRUCK finished" << endl;}
            PRINT(prt.print(Printer::Truck, 'F');)
            return;
        }
        for (unsigned int servedVending = 0; servedVending < numVendingMachines; servedVending+=1) {
            bool noCargo = true;
            if(debug){cout << "calling inventory" << endl;}
            unsigned int* machineInventory = machineList[curMachine]->inventory();

            PRINT({
                int total_remaining = 0;
                for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                    total_remaining += cargo[i];
                }
                prt.print(Printer::Truck, 'd', machineList[curMachine]->getId(), total_remaining);
            })
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
            PRINT({
                int total_unfilled = 0;
                for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                    total_unfilled = maxStockPerFlavour - machineInventory[i];
                }
                if (total_unfilled > 0) {
                    prt.print(Printer::Truck, 'U', machineList[curMachine]->getId(), total_unfilled);
                }
            })
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
            // delivery ended
            machineList[curMachine]->restocked();
            PRINT({
                int total_remaining = 0;
                for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                    total_remaining += cargo[i];
                }
                
                prt.print(Printer::Truck, 'D', machineList[curMachine]->getId(), total_remaining);
            })
            if (prng(100) == 0) {
                PRINT(prt.print(Printer::Truck, 'W');)
                yield(10);
            }
            if (noCargo) {
                break;
            }

            curMachine = (1+curMachine) % numVendingMachines;
        }
    }
}

