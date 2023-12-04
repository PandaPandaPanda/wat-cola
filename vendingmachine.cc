#include "vendingmachine.h"
#include "bottlingPlant.h"
#include "watcard.h"
#include "nameServer.h"
#include "student.h"
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

VendingMachine::BuyInfo::BuyInfo( BottlingPlant::Flavours flavour, WATCard & card, uBaseTask & student )
: flavour(flavour), card(card), student(student) {}


void VendingMachine::main() {
    for (;;) {
        _Accept(~VendingMachine) {
            break;
        } or _Accept(inventory) {
            _Accept(restocked){} or _Accept(~VendingMachine) {break;};
        } or _Accept(buy) {
            BuyInfo buyInfo = *(BuyInfo*)vmQueue.front();
            unsigned int balance = buyInfo.card.getBalance();
            if (balance < sodaCost) {
                _Resume Funds() _At buyInfo.student;
            }
            if (items[buyInfo.flavour]==0) {
                _Resume Stock() _At buyInfo.student;
            }
            items[buyInfo.flavour]-=1;
            if (prng(5) == 0) { // free soda
                if (prng(0,1) == 0) { // student will watch ad
                    _Resume Free() _At buyInfo.student;
                }
            } else {
                buyInfo.card.withdraw(sodaCost);
            }
        }
    }
}

void VendingMachine::buy( BottlingPlant::Flavours flavour, WATCard & card ) {
    BuyInfo buyInfo(flavour, card, uThisTask());
    vmQueue.wait((uintptr_t)&buyInfo);
}

void VendingMachine::restocked() {};

_Nomutex unsigned int VendingMachine::cost() const {
    return sodaCost;
};

_Nomutex unsigned int VendingMachine::getId() const {
    return id;
};

unsigned int* VendingMachine::inventory() {
    return items;
}
