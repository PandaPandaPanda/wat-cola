#include "parent.h"

// ==== Global debug
bool debug = true;
// ====

using namespace std;

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ):
    prt(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

void Parent::main() {
    for (;;) {
        _Accept(~Parent) {
            break;
        } _Else {
            yield(parentalDelay);
            unsigned int amount = prng(1,3);
            unsigned int id = prng(0, numStudents-1);
            if (debug) {cout << "Parent::main: Depositing $" << amount << " into account of student " << id << endl;}
            bank.deposit(id, amount);
        }
    }
}
