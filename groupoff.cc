#include "groupoff.h"
#include "watcard.h"
using namespace std;

Groupoff::Groupoff(Printer& prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay)
    : prt(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay) {

    };

void Groupoff::main() {
    unsigned int numCalls = 0;
    for (;;) {
        _Accept(giftCard) {
            numCalls+=1;
            if (numCalls == numStudents) {
                break;
            }
        } _Else {}
    }
}

WATCard::FWATCard Groupoff::giftCard() {
    return future;
}
