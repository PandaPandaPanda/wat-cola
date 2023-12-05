#ifndef STUDENT_H
#define STUDENT_H

#include <uPRNG.h>

#include "watcardoffice.h"
#include "nameServer.h"
#include "groupoff.h"

extern PRNG mprng;

_Monitor Printer;
_Task Groupoff;

_Task Student {
	Printer & prt;
	NameServer & nameServer;  		// get vending machine location
	WATCardOffice & cardOffice; 	// create watcard
	Groupoff & groupoff; 					// distributing giftcard
	unsigned int id; 							// student id
	unsigned int maxPurchases; 		// maximum number of bottles to purchase

	WATCard* giftcard = nullptr; 	// giftcard is a WATCard pointer
	WATCard* watcard = nullptr; 	// watcard is a WATCard pointer
	WATCard::FWATCard future_giftcard; // future_giftcard is a WATCard future
	WATCard::FWATCard future_watcard; // future_watcard is a WATCard future

	void main();
  public:
	Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
			 unsigned int id, unsigned int maxPurchases );
};

#endif
