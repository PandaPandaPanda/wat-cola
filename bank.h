#ifndef BANK_H
#define BANK_H

// ==== Global debug
#include <iostream>
extern bool debug;
// ====

_Monitor Bank {
	unsigned int numStudents;
	unsigned int* accounts;
  public:
	Bank( unsigned int numStudents );
	void deposit( unsigned int id, unsigned int amount );
	void withdraw( unsigned int id, unsigned int amount );
	~Bank()
};

#endif

