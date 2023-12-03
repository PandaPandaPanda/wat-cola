#include "student.h"

using namespace std;

void Student::main() {
       WATCard::FWATCard future_card = cardOffice.create(id, 5);

       // cardOffice.transfer(id, 5, card);
       while (true) {}
}

Student::Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
			 unsigned int id, unsigned int maxPurchases ) : 
       prt(prt), nameServer(nameServer), cardOffice(cardOffice), groupoff(groupoff), id(id), maxPurchases(maxPurchases) {
}

