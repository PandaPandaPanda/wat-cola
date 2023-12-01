#ifndef PARENT_H
#define PARENT_H

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
