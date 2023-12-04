#include <uPRNG.h>
#include <iostream>
#include <string>
#include <uPRNG.h>

#include "unistd.h" // getpid

#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watcardoffice.h"
#include "nameServer.h"
#include "vendingmachine.h"
#include "truck.h"
#include "bottlingPlant.h"
#include "student.h"
#include "groupoff.h"

using namespace std;

PRNG mprng; // my prng

int main( int argc, char *argv[] ) {
  const string DefaultConfigFile = "soda.config";  // global defaults
  const intmax_t DefaultSeed = getpid();
  const int DefaultProcessors = 1; 			

  string configFile = DefaultConfigFile; // default configFile
  int seed = DefaultSeed; // default seed value
  int processors = DefaultProcessors; // default processors

  struct cmd_error {};
  try {
    switch(argc) {
      case 4: processors = convert(argv[3]); if (processors <= 0) { throw cmd_error(); };
      // fallthrough
      case 3: seed = convert(argv[2]); if (seed <= 0) { throw cmd_error(); };
      // fallthrough
      case 2: configFile = argv[1];
      // fallthrough
      case 1: break;
      default: throw cmd_error();
    }
  } catch (...) {
    cout << "Usage: " << argv[0] << "[ config-file | 'd' [ seed (> 0) | 'd' [ processors (> 0) | 'd' ] ] ]" << endl;
    exit( EXIT_FAILURE );							// TERMINATE
  } // try

  mprng.set_seed( seed );

  ConfigParms params;
  processConfigFile(configFile.c_str(), params );
  uProcessor p[processors - 1] __attribute__(( unused )); // create (processors-1) more processors

  Printer prt(params.numStudents, params.numVendingMachines, params.numCouriers);

  Bank bank(params.numStudents);
  Parent parent(prt, bank, params.numStudents, params.parentalDelay);
  WATCardOffice office(prt, bank, params.numCouriers);

  Groupoff groupoff(prt, params.numStudents, params.sodaCost, params.groupoffDelay);
  NameServer ns(prt, params.numVendingMachines, params.numStudents);
  VendingMachine* vmList[params.numVendingMachines];
  for (unsigned int id = 0; id < params.numVendingMachines; id+=1) {
      vmList[id] = new VendingMachine(prt, ns, id, params.sodaCost);
  }
  BottlingPlant bp(prt, ns, params.numVendingMachines, params.maxShippedPerFlavour,
         params.maxStockPerFlavour, params.timeBetweenShipments);

  Student* students[params.numStudents];
  for (unsigned int i = 0; i < params.numStudents; i++) {
    students[i] = new Student(prt, ns, office, groupoff, i, params.maxPurchases);
  } // for
  // wait for students to finish
  for (unsigned int i = 0; i < params.numStudents; i++) {
    delete students[i];
  } // for
  delete[] students;

  // delete [] vmList;

  while(true) {}
} // main
