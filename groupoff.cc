#include "groupoff.h"
#include <iostream>

using namespace std;

Groupoff::Groupoff(Printer& prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay)
    : prt(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay) {
        future_giftcards = new WATCard::FWATCard[numStudents];
    };

Groupoff::~Groupoff() {
    delete[] future_giftcards;
}

void Groupoff::main() {
    prt.print(Printer::Groupoff, 'S');
    // begins by first accepting a call from all students to obtain a future gift-card
    for (unsigned i = 0; i < numStudents; i++) {
        _Accept(giftCard) {
            cards_cnt+=1;
        }
    }

    // periodically creates and puts a real WATCard with value SodaCost into a random future gift-card
    for (unsigned int i = 0; i < numStudents; i++) {
        // loops until all the future gift-cards are assigned a real WATCard or a call to its destructor occurs
        _Accept(~Groupoff) {
            break;
        } _Else {
            yield(groupoffDelay);
            WATCard* giftcard = new WATCard();
            giftcard->deposit(sodaCost);

            unsigned int idx = mprng(0, numStudents - i - 1);
            WATCard::FWATCard future_giftcard = future_giftcards[idx];
            /*
            swap the future giftcard with the last one (to avoid duplicate gifting)
            this future will not be used anymore as i increases and the index will
            not be select by subsequent mprng calls
            */
            swap(future_giftcards[idx], future_giftcards[numStudents - i - 1]);

            PRINT(prt.print(Printer::Groupoff, 'D', giftcard->getBalance());)

            future_giftcard.delivery(giftcard); // put the giftcard into the future
        }
    }

    prt.print(Printer::Groupoff, 'F');
}

WATCard::FWATCard Groupoff::giftCard() {
    WATCard::FWATCard future_giftcard;
    future_giftcards[cards_cnt] = future_giftcard;
    return future_giftcard;
}
