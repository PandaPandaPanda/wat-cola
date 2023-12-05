#ifndef GROUPOFF_H
#define GROUPOFF_H

#include <uPRNG.h>

#include "watcard.h"
#include "printer.h"

extern PRNG mprng;

_Task Groupoff {
	Printer& prt;
	unsigned int numStudents;
	unsigned int sodaCost;
	unsigned int groupoffDelay;
	unsigned int cards_cnt;
	WATCard::FWATCard* future_giftcards;

	void main();
  public:
	Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
	~Groupoff();
	WATCard::FWATCard giftCard();
};

#endif
