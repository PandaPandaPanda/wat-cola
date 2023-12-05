#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H
#include "bottlingPlant.h"

_Task NameServer;
_Monitor Printer;
class WATCard;

extern PRNG mprng;

_Task VendingMachine {
	Printer & prt;
	NameServer & name_server;
	unsigned int id;
	unsigned int soda_cost; 
	unsigned int* items;				// vending machine inventory
    uCondition vm_queue;				// shadow queue to pass BottlingPlant::buy arguments into main
	void main();
	struct BuyInfo {					// used to pass BottlingPlant::buy arguments into main for concurrency
		BottlingPlant::Flavours flavour;
		WATCard & card;
		uBaseTask & student;			// student task that called buy (for main to raise exception on)
		BuyInfo( BottlingPlant::Flavours flavour, WATCard & card, uBaseTask & student);
	};
  public:
	_Event Free {};						// free, advertisement
	_Event Funds {};					// insufficient funds
	_Event Stock {};					// flavour out of stock
	VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost );
	void buy( BottlingPlant::Flavours flavour, WATCard & card );
	unsigned int * inventory() __attribute__(( warn_unused_result ));
	void restocked();
	_Nomutex unsigned int cost() const;
	_Nomutex unsigned int getId() const;
	~VendingMachine();
};

#endif
