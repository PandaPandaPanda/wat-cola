#include <cassert>

#include "watcardoffice.h"

using namespace std;

void WATCardOffice::main() {
  PRINT( prt.print( Printer::WATCardOffice, 'S' ); )
  for ( ; ; ) {
    _Accept( ~WATCardOffice ) {
      // cleanup all job when shutting down
      for ( ; !jobs.empty() ; ) {
        delete jobs.front();
        jobs.pop();
      }

      break;
    } or _Accept( create ) {
      Job * new_job = jobs.back();
      PRINT( prt.print( Printer::WATCardOffice, 'C', new_job->sid, new_job->amount ); )
    } or _Accept( transfer ) {
      Job * new_job = jobs.back();
      PRINT( prt.print( Printer::WATCardOffice, 'T', new_job->sid, new_job->amount ); )
    } or _When( !jobs.empty() ) _Accept( requestWork ) {
      PRINT( prt.print( Printer::WATCardOffice, 'W' ); )
      jobs.pop();
    }
  }

  PRINT( prt.print( Printer::WATCardOffice, 'F' ); )
}

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) : prt{prt}, bank{bank}, numCouriers{numCouriers}  {
  couriers = new Courier*[numCouriers];
  for ( unsigned int i = 0; i < numCouriers; i++ ) { // create fixed # of couriers
    couriers[i] = new Courier( prt, bank, this, i );
  }
} 

WATCardOffice::~WATCardOffice() {
  if (debug) { cout << "watcardoffice destructor" << endl; }
  for ( unsigned int i = 0; i < numCouriers; i++) {
    // manually unblock couriers
    _Accept(requestWork);
  }
  for ( unsigned int i = 0; i < numCouriers; i++ ) {
    delete couriers[i];
  }
  delete[] couriers;
  if (debug) { cout << " couriers deleted" << endl;}

  for (pair<unsigned int, WATCard*> p : card_map) {
    delete p.second;
  }
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
  WATCard * card = new WATCard();
  card_map[sid] = card;

  Job * job = new Job( sid, amount, card );
  jobs.push(job);

  return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
  Job* job = new Job(sid, amount, card);
  jobs.push(job);

  return job->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
  if (debug) { cout << "request work" << endl; }
  if ( jobs.empty() ) {
    return nullptr;
  }
  Job * job = jobs.front();
  // pop job in watcardoffice main

  return job;
}

void WATCardOffice::Courier::main() {
  PRINT( prt.print( Printer::Courier, id, 'S' ); )

  for ( ; ; ) {
    _Accept( ~Courier ) {
      break;
    } _Else {
      /* caller courier blocks until a Job request is ready 
      since requestWork is a public member of task */
      if (debug) { cout << "courier request work" << endl; }
      Job * job = office->requestWork();

      // if no job, then watcardoffice is shutting down
      if ( job == nullptr ) {
        if(debug) { cout << "courier no job" << endl; }
        break;
      }
      
      PRINT( prt.print( Printer::Courier, id, 't', job->sid, job->amount ); )
      /* caller courier blocks until the bank has enough to withdraw and return */
      bank.withdraw( job->sid, job->amount );
      job->card->deposit( job->amount ); // deposit money into card

      if ( mprng(6) == 0 ) { // 1 in 6 chance of losing card
        PRINT( prt.print( Printer::Courier, id, 'L', job->sid ); )
        office->card_map.erase( job->sid );
        job->result.exception( new Lost() );
      } else {
        PRINT( prt.print( Printer::Courier, id, 'T', job->sid, job->amount ); )
        job->result.delivery( job->card );
      }
      delete job;
    }
  }

  PRINT( prt.print( Printer::Courier, id, 'F' ); )
}

WATCardOffice::Courier::Courier( Printer & prt, Bank & bank, WATCardOffice * office, unsigned int id ) 
  : prt{prt}, bank{bank}, office{office}, id{id} {}
