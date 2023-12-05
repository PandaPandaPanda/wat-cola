#ifndef BANK_H
#define BANK_H

_Monitor Bank {
	unsigned int numStudents;
	unsigned int* accounts;				// keeps track of balance of every student's account
  public:
	Bank( unsigned int numStudents );
	void deposit( unsigned int id, unsigned int amount );
	void withdraw( unsigned int id, unsigned int amount );
	~Bank();
};

#endif

