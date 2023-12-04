#ifndef PARENT_H
#define PARENT_H

#include <uPRNG.h>

#include "bank.h"
#include "printer.h"

// ==== Global debug
#include <iostream>
extern bool debug;
// ====

extern PRNG mprng;

_Task Parent {
	Printer & prt;
	Bank & bank;
	unsigned int numStudents;
	unsigned int parentalDelay;
	void main();
  public:
	Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
	~Parent();
};

#endif
