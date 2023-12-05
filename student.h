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
	NameServer & nameServer;
	WATCardOffice & cardOffice;
	Groupoff & groupoff;
	unsigned int id;
	unsigned int maxPurchases;

	WATCard* giftcard = nullptr;
	WATCard* watcard = nullptr;
	WATCard::FWATCard future_giftcard;
	WATCard::FWATCard future_watcard;

	void main();
  public:
	Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
			 unsigned int id, unsigned int maxPurchases );
};

#endif
