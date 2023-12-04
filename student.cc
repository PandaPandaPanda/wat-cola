#include "student.h"
#include "bottlingPlant.h"
#include "vendingmachine.h"
#include "nameServer.h"

using namespace std;

void Student::main() {

  // begins by selecting a random number of bottles to purchase [1, MaxPurchases], a random favourite flavour [0, 3]
  int bottles_to_purchase = mprng(1, maxPurchases);
  BottlingPlant::Flavours fav_flavour = (BottlingPlant::Flavours)mprng(0, BottlingPlant::Flavours::NUM_OF_FLAVOURS-1);
  
  PRINT( prt.print(Printer::Student, id, 'S', fav_flavour, bottles_to_purchase);)
  
  // creates a gift card from Groupoff with a value of SodaCost
  WATCard::FWATCard future_giftcard = groupoff.giftCard();
  // creates a WATCard from the WATCardOffice with a $5 balance
  WATCard::FWATCard future_watcard = cardOffice.create(id, 5);
  // obtains the location of a vending machine from the name serve
  VendingMachine* vm = nameServer.getMachine(id);
  PRINT( prt.print(Printer::Student, id, 'V', vm->getId());)

  for (;;) {
    future_watcard = cardOffice.create(id, 5);
    _Select(future_watcard) {
      try {
        card = future_watcard();
        if (debug) {cout << endl <<"Student " << id << " has received a watcard " << endl;}
        break;
      } catch (WATCardOffice::Lost &l) {
        PRINT( prt.print(Printer::Student, id, 'L'); )
        if (debug) {cout << endl << "Student " << id << " has lost his card" << endl;}
      }
    }
  }
  _Select(future_giftcard) {
    if (debug) {cout << endl <<"Student " << id << " has received a giftcard" << endl;}
  }

  for ( ;bottles_to_purchase > 0; ) {
    yield(prng(1,10));
    for ( ;; ) {
      try{
        _Enable{
          vm->buy(fav_flavour, *card);
        }
      } _Catch(VendingMachine::Free &f) {
        PRINT( prt.print(Printer::Student, id, 'A', fav_flavour, card->getBalance());)
        if (prng(0,1) == 0) {
          yield(4);
        } else {
          PRINT( prt.print(Printer::Student, id, 'X');)
        }
        break; // attempt purcahse another soda - also need to wait
      } _Catch(VendingMachine::Funds &f) {
        // add money
        if (debug) {cout << endl << "BROKE ALERT" << endl;}
        continue; // didnt purchase - no wait
      } _Catch(VendingMachine::Stock &s) {
        vm = nameServer.getMachine(id);
        if(debug) {cout << endl  << "STOCK ALERT" << endl;}
        continue; // didnt purchase - no wait
      }
      PRINT( prt.print(Printer::Student, id, 'B', fav_flavour, card->getBalance());)
      bottles_to_purchase -= 1; // reduce only on regular purchase (not free sodas)
      break;
    }

  }
  PRINT( prt.print(Printer::Student, id, 'F');)
}

Student::Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
  unsigned int id, unsigned int maxPurchases ) : 
  prt(prt), nameServer(nameServer), cardOffice(cardOffice), groupoff(groupoff), id(id), maxPurchases(maxPurchases) {
}

