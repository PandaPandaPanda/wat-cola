#include "student.h"

using namespace std;

void Student::main() {
  WATCard::FWATCard future_giftcard = groupoff.giftCard();
  WATCard::FWATCard future_watcard = cardOffice.create(id, 5);

  if (debug) {cout << "student get machine " << nameServer.getMachine(id)->getId() << endl;} 
  if (debug) {cout << "student get machine " << nameServer.getMachine(id)->getId() << endl;}

  _Select(future_watcard) {
    try {
      card = future_watcard();
      if (debug) {
        cout << endl <<"Student " << id << " has received a card with balance " << card->getBalance() << endl;
      }
    } catch (WATCardOffice::Lost) {
      PRINT( prt.print(Printer::Student, id, 'L'); )
      if (debug) {
        cout << endl << "Student " << id << " has lost his card" << endl;
      }
    }
  }
  
  _Select(future_giftcard) {
    if (debug) {
      cout << endl <<"Student " << id << " has received a giftcard" << endl;
    }
  }

  while(true) {}
}

Student::Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
  unsigned int id, unsigned int maxPurchases ) : 
  prt(prt), nameServer(nameServer), cardOffice(cardOffice), groupoff(groupoff), id(id), maxPurchases(maxPurchases) {
}

