#ifndef TRUCK_H
#define TRUCK_H

_Task VendingMachine

_Task Truck {
	Printer & prt;
	NameServer & nameServer;
	BottlingPlant & plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;
	int* cargo;
	VendingMachine ** machineList;
	int curMachine;
	void main();
  public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
	~Truck();
};

#endif
