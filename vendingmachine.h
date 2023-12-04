#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H
#include "bottlingPlant.h"

_Task NameServer;
_Monitor Printer;
class WATCard;

_Task VendingMachine {
	Printer & prt;
	NameServer & name_server;
	unsigned int id;
	unsigned int soda_cost; 
	unsigned int* items;
    uCondition vm_queue;
	void main();
	struct BuyInfo {
		BottlingPlant::Flavours flavour;
		WATCard & card;
		uBaseTask & student;
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
