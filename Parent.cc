#include "Parent.h"

using namespace std;

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ):
    prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

void Parent::main() {
    for (;;) {
        _Accept(~Parent) {
            break;
        } _Else {
            yield(parentalDelay);
            unsigned int amount = prng(0,3);
            unsigned int id = prng(0, numStudents-1);
            bank.deposit(id, amount);
        }
    }
}
