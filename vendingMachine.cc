#include "vendingmachine.h"
#include "bottlingPlant.h"

using namespace std;

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost )
    : prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost) {
        inventory = new int[BottlingPlant::Flavours::NUM_OF_FLAVOURS];
    };

VendingMachine::~VendingMachine() {
    delete[] inventory;
}

VendingMachine::inventory() {
    return inventory;
}
