#include "vendingmachine.h"
#include "bottlingPlant.h"
#include "nameServer.h"
#include <iostream>

using namespace std;

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost )
    : prt(prt), nameServer(nameServer), id(id), sodaCost(sodaCost) {
        items = new unsigned int[BottlingPlant::Flavours::NUM_OF_FLAVOURS]();
        nameServer.VMregister(this);
    };

VendingMachine::~VendingMachine() {
    delete[] items;
}


void VendingMachine::main() {
    for (;;) {
        _Accept(~VendingMachine) {
            break;
        } or _Accept(inventory) {
            cout << "inventory called" << endl;
        } _Else {}
    }
}

_Nomutex unsigned int VendingMachine::getId() const {
    return id;
};

unsigned int* VendingMachine::inventory() {
    return items;
}
