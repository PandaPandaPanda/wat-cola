#include "student.h"

using namespace std;

void Student::main() {
  WATCard::FWATCard future_card = cardOffice.create(id, 5);

  _Select(future_card) {
    try {
      card = future_card();
      if (debug) {
        cout << "Student " << id << " has received a card with balance " << card->getBalance() << endl;
      }
    } catch (WATCardOffice::Lost) {
      PRINT( prt.print(Printer::Student, id, 'L'); )
      if (debug) {
        cout << "Student " << id << " has lost his card" << endl;
      }
    }
  }

  // cardOffice.transfer(id, 5, card);
  while (true) {}
}

Student::Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
  unsigned int id, unsigned int maxPurchases ) : 
  prt(prt), nameServer(nameServer), cardOffice(cardOffice), groupoff(groupoff), id(id), maxPurchases(maxPurchases) {
}

