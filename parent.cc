#include "parent.h"
#include <iostream>

using namespace std;

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ):
  prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

void Parent::main() {
  PRINT(prt.print(Printer::Parent, 'S');)
  for (;;) {
    _Accept(~Parent) {
      break;
    } _Else {
      yield(parentalDelay);
      unsigned int amount = mprng(1,3);
      unsigned int id = mprng(0, numStudents-1);
      PRINT(prt.print(Printer::Parent, 'D', id, amount);)
      bank.deposit(id, amount);
    }
  }
  PRINT(prt.print(Printer::Parent, 'F');)
}
