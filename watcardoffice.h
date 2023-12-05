#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include <queue>
#include <vector>
#include <uPRNG.h>

#include "watcard.h"
#include "bank.h"
#include "printer.h"

extern PRNG mprng;

_Task WATCardOffice {
	struct Job {										// marshalled arguments and return future
		unsigned int sid;
    unsigned int amount;
    WATCard* card; 								// actual card carried
		WATCard::FWATCard result;			// return future
		Job( unsigned int sid, unsigned int amount, WATCard* card ) : sid( sid ), amount( amount ), card( card ) {}
	};
	_Task Courier { // communicates with bank
		Printer & prt;
		Bank & bank;
		WATCardOffice * office;
		unsigned int id;
		void main();

	  public:
		Courier( Printer & prt, Bank & bank, WATCardOffice * office, unsigned int id );
	};					

	Printer & prt;
	Bank & bank;
	unsigned int numCouriers;
	std::queue<Job *> jobs;
	Courier ** couriers;
	std::vector<WATCard*> watCards;

	void main();
  public:
	_Event Lost {};							// lost WATCard
	WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
	~WATCardOffice();
	WATCard::FWATCard create( unsigned int sid, unsigned int amount ) __attribute__(( warn_unused_result ));
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card ) __attribute__(( warn_unused_result ));
	Job * requestWork() __attribute__(( warn_unused_result ));
};

#endif
