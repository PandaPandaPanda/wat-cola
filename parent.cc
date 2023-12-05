#include "parent.h"

using namespace std;

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ):
  prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {} // Parent ctor

void Parent::main() {
  PRINT(prt.print(Printer::Parent, 'S');)
  for (;;) {
    _Accept(~Parent) {                                                            // listen for destructor call
      break;
    } _Else {                                                                     // accept non-blocking - busy wait
      yield(parentalDelay);
      unsigned int amount = mprng(1,3);                                           // gift amount
      unsigned int id = mprng(0, numStudents-1);                                  // student to gift
      PRINT(prt.print(Printer::Parent, 'D', id, amount);)
      bank.deposit(id, amount);                                                   // gift student money
    } // _Accept
  } // for
  PRINT(prt.print(Printer::Parent, 'F');)
} // Parent::main
