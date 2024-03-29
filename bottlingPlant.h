#ifndef BOTTLINGPLANT_H
#define BOTTLINGPLANT_H

#include <uPRNG.h>

_Task Truck;
_Task NameServer;
_Monitor Printer;

extern PRNG mprng;

_Task BottlingPlant {
	Printer & prt;
	NameServer & nameServer;
	Truck* truck;
	unsigned int numVendingMachines;
	unsigned int maxShippedPerFlavour;
	unsigned int maxStockPerFlavour;
	unsigned int timeBetweenShipments;
	unsigned int * stock;
	bool closing = false;
	uCondition bp_queue;
	void main();
  public:
	enum Flavours { Blues_Black_Cherry, Classic_Cream_Soda, Rock_Root_Beer, Jazz_Lime, NUM_OF_FLAVOURS };	// flavours of soda (YOU DEFINE)
	_Event Shutdown {};					// shutdown plant
	BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
				 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
				 unsigned int timeBetweenShipments );
	void getShipment( unsigned int cargo[] );
	~BottlingPlant();
};

#endif
