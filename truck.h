#ifndef TRUCK_H
#define TRUCK_H

_Monitor Printer;
_Task VendingMachine;
_Task NameServer;
_Task BottlingPlant;

_Task Truck {
	Printer & prt;
	NameServer & nameServer;
	BottlingPlant & plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;
	unsigned int* cargo;				// truck cargo - contains inventory for each flavor
	VendingMachine ** machineList;		// list pointers to all vending machines
	int curMachine = 0;					// id of current machine being served
	void main();
  public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
	~Truck();
};

#endif
