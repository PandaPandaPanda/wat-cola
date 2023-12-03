#ifndef TRUCK_H
#define TRUCK_H

_Monitor Printer;
_Task VendingMachine;
_Task NameServer;
_Task BottlingPlant;

// ==== Global debug
#include <iostream>
extern bool debug;
// ====

_Task Truck {
	Printer & prt;
	NameServer & nameServer;
	BottlingPlant & plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;
	unsigned int* cargo;
	VendingMachine ** machineList;
	int curMachine = 0;
	void main();
  public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
	~Truck();
};

#endif
