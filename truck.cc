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
            cargo = new unsigned int[BottlingPlant::Flavours::NUM_OF_FLAVOURS]();   // int array to show cargo per flavour
            machineList = nameServer.getMachineList();                              // get machine list from server
           } // Truck ctor

Truck::~Truck() {
    delete[] cargo;
} // Truck dtor

void Truck::main() {
    PRINT(prt.print(Printer::Truck, 'S');)
    for(;;) {
        yield(mprng(0,10));                                                         // yield random number of times before each shipment
        try {
            _Enable {
                plant.getShipment(cargo);                                           // get new shipment of soda, old soda discarded
                PRINT({
                    int totalPickedUp = 0;
                    for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                        totalPickedUp += cargo[i];
                    } // for
                    
                    prt.print(Printer::Truck, 'P', totalPickedUp);
                }) // PRINT
            } // _Enable
        } _Catch(BottlingPlant::Shutdown & e) {                                     // if plant is shutting down the truck temrinates
            PRINT(prt.print(Printer::Truck, 'F');)
            return;
        } // try
                                                                                    // curMachine ensures cyclid order restocking 
        for (unsigned int servedVending = 0; servedVending < numVendingMachines; servedVending+=1) { // return to plant after complete cycle
            bool noCargo = true;                                                    // return to plant if no more cargo
            unsigned int* machineInventory = machineList[curMachine]->inventory();  // begin restock by calling inventory

            PRINT({
                int total_remaining = 0;
                for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                    total_remaining += cargo[i];
                } // for
                prt.print(Printer::Truck, 'd', machineList[curMachine]->getId(), total_remaining);
            }) // PRINT
            for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {   // restock machine and check if truck is out of cargo
                unsigned int neededStock = maxStockPerFlavour - machineInventory[i];// restock up to maxStockPerFlavour
                if (noCargo && cargo[i]!=0) {
                    noCargo = false;
                } // if
                if (neededStock > cargo[i]) {                                       
                    machineInventory[i] += cargo[i];
                    cargo[i] = 0;
                } else {
                    machineInventory[i]+=neededStock;
                    cargo[i]-=neededStock;
                } // if
            } // for
            PRINT({
                int total_unfilled = 0;
                for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                    total_unfilled = maxStockPerFlavour - machineInventory[i];
                } // for
                if (total_unfilled > 0) {                                           // fill unsuccessful if there is room available on any flavor
                    prt.print(Printer::Truck, 'U', machineList[curMachine]->getId(), total_unfilled);
                } // if
            }) // PRINT

            machineList[curMachine]->restocked();                                   // delivery ended - notify machine
            PRINT({
                int total_remaining = 0;
                for (int i = 0; i < BottlingPlant::Flavours::NUM_OF_FLAVOURS; i+=1) {
                    total_remaining += cargo[i];
                } // for
                
                prt.print(Printer::Truck, 'D', machineList[curMachine]->getId(), total_remaining);
            }) // PRINT
            if (mprng(100) == 0) {                                                  // 1 in 100 chance of flat tire
                PRINT(prt.print(Printer::Truck, 'W');)
                yield(10);
            } // if
            if (noCargo) {                                                          // if no cargo - machine was not served, return to plant
                break;
            } // if

            curMachine = (1+curMachine) % numVendingMachines;                       // cur machine was served, go to next machine
        } // for
    } // for
} // Truck::main

