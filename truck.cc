#include "truck.h"
#include "bottlingPlant.h"
using namespace std;

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour )
           : prt(prt), nameServer(nameServer), plant(plant), 
           numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour) {
            cargo = new int[BottlingPlant::Flavours::NUM_OF_FLAVOURS]();
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
                plant.getShipment(cargo);
            }
        } _CatchResume(BottlingPlant::Shutdown) {
            break;
        }
        for (;;) {
            bool noCargo = true;
            int* machineInventory = machineList[curMachine]->inventory();
            for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                int neededStock = maxStockPerFlavour - machineInventory[i]
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
            if (prng(100) == 42) {
                yield(10);
            }
            if (noCargo) {
                break;
            } else {
                curMachine = (1+curMachine) % numVendingMachines;
            }
        }

    }
}

