#ifndef NAMESERVER_H
#define NAMESERVER_H

#include "printer.h"
#include "vendingmachine.h"

_Task NameServer {
	Printer & prt;
	unsigned int numVendingMachines;
	unsigned int numStudents;
	unsigned int machine_cnt = 0;
	VendingMachine** machines;
	unsigned int* sid_to_machineid;
	// buffer variables for storing param variables for task main
	unsigned int cur_id;

	void main();
  public:
	NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
	~NameServer();
	void VMregister( VendingMachine * vendingmachine );
	VendingMachine * getMachine( unsigned int id ) __attribute__(( warn_unused_result ));
	VendingMachine ** getMachineList() __attribute__(( warn_unused_result ));
};

#endif
