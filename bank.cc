#include "bank.h"

using namespace std;

Bank::Bank( unsigned int numStudents ): numStudents(numStudents) {
  accounts = new unsigned int[numStudents]();
} // Bank ctor

Bank::~Bank() {
  delete[] accounts;
} // Bank dtor

void Bank::deposit( unsigned int id, unsigned int amount ) {
  accounts[id]+=amount;
} // Bank::deposit

void Bank::withdraw( unsigned int id, unsigned int amount ) {
  while (accounts[id] < amount) {             // only accept deposit until account has enough money
      _Accept(deposit);
  } // for

  accounts[id] -= amount;                     // give money to courier
} // Bank::withdraw
