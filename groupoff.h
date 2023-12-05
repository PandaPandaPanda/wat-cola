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
	unsigned int groupoffDelay; 					// delay between giftcard distribution
	unsigned int cards_cnt; 							// number of giftcards created
	WATCard::FWATCard* future_giftcards; // array of giftcard futures

	void main();
  public:
	Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
	~Groupoff();
	WATCard::FWATCard giftCard();
};

#endif
