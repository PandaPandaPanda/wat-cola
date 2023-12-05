#include "vendingmachine.h"
#include "bottlingPlant.h"
#include "watcard.h"
#include "nameServer.h"
#include "student.h"

using namespace std;

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost )
    : prt(prt), name_server(nameServer), id(id), soda_cost(sodaCost) {
        items = new unsigned int[BottlingPlant::Flavours::NUM_OF_FLAVOURS]();   // inventory of all flavours
        name_server.VMregister(this);
    } // VendingMachine ctor

VendingMachine::~VendingMachine() {
    delete[] items;
} // VendingMachine dtor

VendingMachine::BuyInfo::BuyInfo( BottlingPlant::Flavours flavour, WATCard & card, uBaseTask & student )
: flavour(flavour), card(card), student(student) {} // VendingMachine::BuyInfo ctor - used in for VendingMachine::buy


void VendingMachine::main() {
    PRINT( prt.print(Printer::Vending, id, 'S', soda_cost);)
    for (;;) {
        _Accept(~VendingMachine) {                                              // listen for dtor call and terminate
            PRINT( prt.print(Printer::Vending, id, 'F');)
            break;
        } or _Accept(inventory) {                                               // begin stocking after inventory call
            PRINT( prt.print(Printer::Vending, id, 'r');)
                                                                                // currently restocking - cannot accept buy calls
            _Accept(restocked);                                                 // finish restocking
            PRINT( prt.print(Printer::Vending, id, 'R');)
        } or _Accept(buy) {
            BuyInfo buy_info = *(BuyInfo*)vm_queue.front();                     // use shadow queue info to process buy call in main
            unsigned int balance = buy_info.card.getBalance();
            if (balance < soda_cost) {                                          // check student card balance
                _Resume Funds() _At buy_info.student;                           // raise exception if insufficient
                vm_queue.signalBlock();                                         // let buy caller continue
                continue;
            } // if
            if (items[buy_info.flavour]==0) {                                   // check stock
                _Resume Stock() _At buy_info.student;                           // raise exception if insufficient
                vm_queue.signalBlock();                                         // let buy caller continue
                continue;
            } // if
            items[buy_info.flavour]-=1;                                         // take soda out from inventory
            if (mprng(5) == 0) {                                                // 1 in 5 chance of free soda
                PRINT( prt.print(Printer::Vending, id, 'A');)
                _Resume Free() _At buy_info.student;                            // raise free soda exception at student 
                vm_queue.signalBlock();                                         // let buy caller continue
                continue;
            } else {                                                            // soda is not free
                PRINT( prt.print(Printer::Vending, id, 'B', buy_info.flavour, items[buy_info.flavour]);)
                buy_info.card.withdraw(soda_cost);                              // withdraw money from card
                vm_queue.signalBlock();                                         // let buy caller continue
            } // if
        } // _Accept
    } // for
} // VendingMachine::main

void VendingMachine::buy( BottlingPlant::Flavours flavour, WATCard & card ) {
    BuyInfo buy_info(flavour, card, uThisTask());                               // pass params into stack-allocated object
    vm_queue.wait((uintptr_t)&buy_info);                                        // pass object to main via shadow queue
} // VendingMachine::buy

void VendingMachine::restocked() {}; // VendingMachine::restocked - used to notify vending machine that restocking is done

_Nomutex unsigned int VendingMachine::cost() const {
    return soda_cost;
} // VendingMachine::cost

_Nomutex unsigned int VendingMachine::getId() const {
    return id;
} // VendingMachine::getId

unsigned int* VendingMachine::inventory() {
    return items;
} // VendingMachine::inventory
