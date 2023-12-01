#include "Bank.h"

using namespace std;

Bank::Bank( unsigned int numStudents ): numStudents(numStudents) {
    accounts = new unsigned int[numStudents]();
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
    accounts[id]+=amount;
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    if (accounts[id] >= amount) {
        accounts[id] -= amount;
        // give money to courier
    } else {
        for ( ;; ) {
            _Accept(deposit) {
                if (accounts[id] >= amount) {
                    accounts[id] -= amount;
                    // give money to courier
                    break;
                }
            }
        }
    }
}
