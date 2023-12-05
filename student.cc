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
  WATCard* card = nullptr;
  future_giftcard = groupoff.giftCard();
  // creates a WATCard from the WATCardOffice with a $5 balance
  future_watcard = cardOffice.create(id, 5);
  // obtains the location of a vending machine from the name serve
  VendingMachine* vm = nameServer.getMachine(id);
  PRINT( prt.print(Printer::Student, id, 'V', vm->getId());)

  for ( ;bottles_to_purchase > 0; ) {
    yield(mprng(1,10));
    for ( ;; ) {
      // to wait for money to be transferred either from the WATCardOffice to theirWATCard or from Groupoff to their gift card.
      // use the gift card first if both have money
      bool using_giftcard = false;
      _Select(future_giftcard) {
        giftcard = future_giftcard();
        card = giftcard;
        using_giftcard = true;
      } or _Select(future_watcard) {
        try {
          watcard = future_watcard();
          card = watcard;
        } catch (WATCardOffice::Lost &l) {
          // the student must create a new WATCard from the WATCardOffice with a $5 balance
          PRINT( prt.print(Printer::Student, id, 'L'); )
          future_watcard.reset();
          future_watcard = cardOffice.create(id, 5);
          continue; // re-attempt to purchase a soda without yielding as a purchase has not occurred.
        }
      }

      try{
        _Enable{
          vm->buy(fav_flavour, *card);
        }
      } _Catch(VendingMachine::Free &f) {
        // a free bottle of soda (which does not count as a purchased soda), 
        PRINT( prt.print(Printer::Student, id, using_giftcard ? 'a': 'A', fav_flavour, card->getBalance());)
        // 50% change the student watches an advertisement associated with it by yielding 4 times
        if (mprng(2) == 0) {
          yield(4);
          break;
        }
        PRINT( prt.print(Printer::Student, id, 'X');)
        break; // attempt purcahse another soda - also need to wait
      } _Catch(VendingMachine::Funds &f) {
        /*
        insufficient funds, a student transfers the current vending-machine soda-cost plus $5 
        to their WATCard via the WATCard office and attempts another purchase
        */
        future_watcard = cardOffice.transfer(id, 5 + vm->cost(), future_watcard());
        continue; // didnt purchase - no wait
      } _Catch(VendingMachine::Stock &s) {
        /*
        out of the student’s favourite flavour, the student must obtain a new vending machine 
        from the name server and attempt another purchase
        */
        vm = nameServer.getMachine(id);
        PRINT( prt.print(Printer::Student, id, 'V', vm->getId());)
        continue; // didnt purchase - no wait
      }
      /*
      vending machine debits the WATCard and delivers a bottle of soda, 
      the student drinks it and attempts another purchase
      */
      PRINT( prt.print(Printer::Student, id, using_giftcard ? 'G': 'B', fav_flavour, card->getBalance());)
      if (using_giftcard) {
        future_giftcard.reset(); // used gift card
      }
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

Student::~Student() {
  if (giftcard!=nullptr) {
    delete giftcard;
  }
  if (watcard!=nullptr) {
    delete watcard;
  }

  _When(giftcard == nullptr) _Select(future_giftcard) {
    giftcard = future_giftcard();
    delete giftcard;
  }
  _When(watcard == nullptr) _Select(future_watcard) {
    try {
      watcard = future_watcard();
      delete watcard;
    } catch (WATCardOffice::Lost &l) {
      // the student must create a new WATCard from the WATCardOffice with a $5 balance
      PRINT( prt.print(Printer::Student, id, 'L'); )
    }
  }
}
