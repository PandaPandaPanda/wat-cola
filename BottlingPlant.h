#ifndef BOTTLINGPLANT_H
#define BOTTLINGPLANT_H

_Task BottlingPlant {
	void main();
  public:
	enum Flavours { ..., NUM_OF_FLAVOURS };	// flavours of soda (YOU DEFINE)
	_Event Shutdown {};					// shutdown plant
	BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
				 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
				 unsigned int timeBetweenShipments );
	void getShipment( unsigned int cargo[] );
};

#endif
