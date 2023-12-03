#include "watcardoffice.h"

using namespace std;

void WATCardOffice::main() {

  for ( ; ; ) {
    _Accept( ~WATCardOffice ) {
      break;
    } or _Accept( create ) {
      Job * new_job = jobs.back();
      //...
    } or _Accept( transfer ) {
      Job * new_job = jobs.back();
      //...
    } or _When( !jobs.empty() ) _Accept( requestWork ) {
      //...
      jobs.pop();
    }
  }

}

void WATCardOffice::Courier::main() {

  for ( ; ; ) {
    _Accept( ~Courier ) {
      break;
    } _Else {
      /* caller courier blocks until a Job request is ready 
      since requestWork is a public member of task */
      Job * job = office.requestWork();
      assert( job );
      
      /* caller courier blocks until the bank has enough to withdraw and return */
      bank.withdraw( job->sid, job->amount );
      job->card->deposit( job->amount ); // deposit money into card

      if ( prng(0, 5) == 0 ) { // 1 in 6 chance of losing card
        delete job->card;
        job->result.exception( new Lost() );
      } else {
        job->result.delivery( job->card );
      }
      delete job;
    }
  }
}

WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) 
: prt{prt}, bank{bank}, numCouriers{numCouriers}  {
  for ( unsigned int i = 0; i < numCouriers; i++ ) { // create fixed # of couriers
    couriers[0] = new Courier( prt, bank, *this, i );
  }
} 

WATCardOffice::~WATCardOffice() {
  for ( unsigned int i = 0; i < numCouriers; i++ ) {
    delete couriers[i];
  }

  for ( ; !jobs.empty() ; ) {
    delete jobs.front();
    jobs.pop();
  }
}

WATCard::FWATCard create( unsigned int sid, unsigned int amount ) __attribute__(( warn_unused_result )) {
  WATCard * card = new WATCard();
  Job * job = new Job( sid, amount, card );
  jobs.push(job);

  return job->result;
}

WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card ) __attribute__(( warn_unused_result )) {
  Job* job = new Job(sid, amount, card);
  jobs.push(job);

  return job->result;
}

Job * requestWork() __attribute__(( warn_unused_result )) {
  assert( !jobs.empty() );
  Job * job = jobs.front();
  // pop job in watcardoffice main

  return job;
}