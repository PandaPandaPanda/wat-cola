#ifndef PARENT_H
#define PARENT_H

#include "bank.h"
#include "printer.h"

// ==== Global debug
#include <iostream>
extern bool debug;
// ====

_Task Parent {
	Printer & prt;
	Bank & bank;
	unsigned int numStudents;
	unsigned int parentalDelay;
	void main();
  public:
	Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
