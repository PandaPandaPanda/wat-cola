#ifndef WATCARD_H
#define WATCARD_H

class WATCard {
	WATCard( const WATCard & ) = delete;	// prevent copying
	WATCard( const WATCard && ) = delete;
	WATCard & operator=( const WATCard & ) = delete;
	WATCard & operator=( const WATCard && ) = delete;
  public:
	typedef Future_ISM<WATCard *> FWATCard;	// future watcard pointer
	WATCard();
	void deposit( unsigned int amount );
	void withdraw( unsigned int amount );
	unsigned int getBalance();
};

#endif