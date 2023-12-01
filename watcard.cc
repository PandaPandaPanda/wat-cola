#include <cassert>

#include "watcard.h"

using namespace std;

WATCard::WATCard() : balance{0} {}

void WATCard::deposit( unsigned int amount ) {
  balance += amount;
}

void WATCard::withdraw( unsigned int amount ) {
  assert(balance >= amount);
  balance -= amount;
}

unsigned int WATCard::getBalance() {
  return balance;
}