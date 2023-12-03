#ifndef GROUPOFF_H
#define GROUPOFF_H

#include "watcard.h"

_Monitor Printer;

_Task Groupoff {
	Printer& prt;
	unsigned int numStudents;
	unsigned int sodaCost;
	unsigned int groupoffDelay;
	WATCard::FWATCard future;
	void main();
  public:
	Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
	WATCard::FWATCard giftCard();
};

#endif
