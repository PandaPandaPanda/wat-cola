#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include <queue>

#include "watcard.h"

_Task WATCardOffice {
	struct Job {							// marshalled arguments and return future
		Args args;							// call arguments (YOU DEFINE "Args")
		WATCard::FWATCard result;			// return future
		Job( Args args ) : args( args ) {}
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
	std::queue<Job> jobs;
	Courier ** couriers;

	void main();
  public:
	_Event Lost {};							// lost WATCard
	WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
	~WATCardOffice() {
	WATCard::FWATCard create( unsigned int sid, unsigned int amount ) __attribute__(( warn_unused_result ));
	WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card ) __attribute__(( warn_unused_result ));
	Job * requestWork() __attribute__(( warn_unused_result ));
};

#endif
