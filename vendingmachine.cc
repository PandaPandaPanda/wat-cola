#include "vendingmachine.h"
#include "bottlingPlant.h"
#include "watcard.h"
#include "nameServer.h"
#include "student.h"
#include <iostream>

using namespace std;

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost )
    : prt(prt), name_server(nameServer), id(id), soda_cost(sodaCost) {
        items = new unsigned int[BottlingPlant::Flavours::NUM_OF_FLAVOURS]();
        name_server.VMregister(this);
    };

VendingMachine::~VendingMachine() {
    delete[] items;
}

VendingMachine::BuyInfo::BuyInfo( BottlingPlant::Flavours flavour, WATCard & card, uBaseTask & student )
: flavour(flavour), card(card), student(student) {}


void VendingMachine::main() {
    PRINT( prt.print(Printer::Vending, id, 'S', soda_cost);)
    for (;;) {
        if (debug) cout << "VendingMachine "<< id << " ::main: before _Accept" << endl;
        _Accept(~VendingMachine) {
            if (debug) cout << "VendingMachine "<< id << " ::main: destructor called" << endl;
            PRINT( prt.print(Printer::Vending, id, 'F');)
            break;
        } or _Accept(inventory) {
            if (debug) cout << "VendingMachine "<< id << " ::main: inventory called" << endl;
            PRINT( prt.print(Printer::Vending, id, 'r');)
            // currently restocking
            _Accept(restocked);
            if (debug) cout << "VendingMachine "<< id << " ::main: after restocked" << endl;
            PRINT( prt.print(Printer::Vending, id, 'R');)
        } or _Accept(buy) {
            if (debug) cout << "VendingMachine "<< id << " ::main: buy called" << endl;
            BuyInfo buy_info = *(BuyInfo*)vm_queue.front();
            unsigned int balance = buy_info.card.getBalance();
            if (balance < soda_cost) {
                if (debug) cout << "VendingMachine "<< id << " ::main: insufficient funds" << endl;
                _Resume Funds() _At buy_info.student;
                vm_queue.signalBlock();
                if (debug) cout << "VendingMachine "<< id << " ::main: after Funds" << endl;
                continue;
            }
            if (items[buy_info.flavour]==0) {
                if (debug) cout << "VendingMachine "<< id << " ::main: out of stock" << endl;
                _Resume Stock() _At buy_info.student;
                vm_queue.signalBlock();
                if (debug) cout << "VendingMachine "<< id << " ::main: after Stock" << endl;
                continue;
            }
            items[buy_info.flavour]-=1;
            if (mprng(5) == 0) { // free soda
                if (debug) cout << "VendingMachine "<< id << " ::main: free soda" << endl;
                PRINT( prt.print(Printer::Vending, id, 'A');)
                _Resume Free() _At buy_info.student;
                vm_queue.signalBlock();
                if (debug) cout << "VendingMachine "<< id << " ::main: after Free" << endl;
                continue;
            } else {
                if (debug) cout << "VendingMachine "<< id << " ::main: charged" << endl;
                PRINT( prt.print(Printer::Vending, id, 'B', buy_info.flavour, items[buy_info.flavour]);)
                buy_info.card.withdraw(soda_cost);
                vm_queue.signalBlock();
                if (debug) cout << "VendingMachine "<< id << " ::main: after charged" << endl;
            }
        }
    }
}

void VendingMachine::buy( BottlingPlant::Flavours flavour, WATCard & card ) {
    BuyInfo buy_info(flavour, card, uThisTask());
    vm_queue.wait((uintptr_t)&buy_info);
}

void VendingMachine::restocked() {};

_Nomutex unsigned int VendingMachine::cost() const {
    return soda_cost;
};

_Nomutex unsigned int VendingMachine::getId() const {
    return id;
};

unsigned int* VendingMachine::inventory() {
    return items;
}
