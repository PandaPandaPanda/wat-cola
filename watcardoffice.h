#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include <queue>
#include <unordered_map>
#include <uPRNG.h>

#include "watcard.h"
#include "bank.h"
#include "printer.h"

extern PRNG mprng;

_Task WATCardOffice {
	struct Job {												// marshalled arguments and return future
		unsigned int sid; 								// student id
    unsigned int amount; 							// amount to transfer
    WATCard* card; 										// actual card carried
		WATCard::FWATCard result;					// return future
		Job( unsigned int sid, unsigned int amount, WATCard* card ) : sid( sid ), amount( amount ), card( card ) {}
	};
	_Task Courier { 									// communicates with bank
		Printer & prt; 									// printer to print courier info
		Bank & bank; 										// bank to communicate with (withdraw money for student card)
		WATCardOffice * office; 				// office to communicate with (request work)
		unsigned int id; 								// courier id
		void main();

	  public:
		Courier( Printer & prt, Bank & bank, WATCardOffice * office, unsigned int id );
	};					

	Printer & prt; 											// printer to print office info
	Bank & bank; 												// bank to communicate with (parent deposit money)
	unsigned int numCouriers; 					// number of couriers
	std::queue<Job *> jobs; 						// queue of jobs
	Courier ** couriers; 								// array of couriers
	std::unordered_map<unsigned int, WATCard*> card_map; // map of student id to watcard

	void main();
  public:
	_Event Lost {};										// lost WATCard
	WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
	~WATCardOffice();
	WATCard::FWATCard create( unsigned int sid, unsigned int amount ) __attribute__(( warn_unused_result ));
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card ) __attribute__(( warn_unused_result ));
	Job * requestWork() __attribute__(( warn_unused_result ));
};

#endif
