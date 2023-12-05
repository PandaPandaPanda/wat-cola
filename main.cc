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
struct cmd_error {};

void output_usage(char* exec_cmd) {                                                         // output usage
    cerr << "Usage: " << exec_cmd << "[ config-file | 'd' [ seed (> 0) | 'd' [ processors (> 0) | 'd' ] ] ]" << endl;
} // output_usage

void parse_and_convert(int &arg, char * argv[], int argv_index) {
    int using_default = 0;                                                              
    using_default = !strcmp( argv[argv_index], "d" );
    if (!using_default) {
        arg = convert( argv[argv_index] );                                                  // convert specified arg
        if ( arg <= 0 ) {                                                                   // all arg for this question must be > 0 
            throw cmd_error();
        } // if
    } // if
} // parse_and_convert

int main( int argc, char *argv[] ) {
  const string DefaultConfigFile = "soda.config";                                           // global defaults
  const intmax_t DefaultSeed = getpid();
  const int DefaultProcessors = 1; 			

  string configFile = DefaultConfigFile;                                                    // default configFile
  int seed = DefaultSeed;                                                                   // default seed value
  int processors = DefaultProcessors;                                                       // default processors

  try {
    switch(argc) {
      case 4: parse_and_convert(processors, argv, 3);
      // fallthrough
      case 3: parse_and_convert(seed, argv, 2);
      // fallthrough
      case 2: 
        if (strcmp( argv[1], "d" )) {
          configFile = argv[1];
        }
      // fallthrough
      case 1: break;
      default: throw cmd_error();
    } // switch
  } catch (...) {
    output_usage(argv[0]);
    exit( EXIT_FAILURE );
  } // try

  mprng.set_seed( seed );

  ConfigParms params;
  processConfigFile(configFile.c_str(), params );
  uProcessor p[processors - 1] __attribute__(( unused ));                                 // create (processors-1) more processors
  // create in order: printer, bank, parent, WATCard office, groupoff, name server, vending machines, bottling plant, and students
  Printer prt(params.numStudents, params.numVendingMachines, params.numCouriers);

  Bank bank(params.numStudents);
  Parent parent(prt, bank, params.numStudents, params.parentalDelay);
  WATCardOffice office(prt, bank, params.numCouriers);
  Groupoff groupoff(prt, params.numStudents, params.sodaCost, params.groupoffDelay);
  NameServer ns(prt, params.numVendingMachines, params.numStudents);
  uNoCtor<VendingMachine> vmList[params.numVendingMachines];
  for (unsigned int id = 0; id < params.numVendingMachines; id+=1) {
      vmList[id].ctor(prt, ns, id, params.sodaCost);
  } // for
  BottlingPlant *bp = new BottlingPlant(prt, ns, params.numVendingMachines, params.maxShippedPerFlavour,
         params.maxStockPerFlavour, params.timeBetweenShipments);
  Student* students[params.numStudents];
  for (unsigned int i = 0; i < params.numStudents; i+=1) {
    students[i] = new Student(prt, ns, office, groupoff, i, params.maxPurchases);
  } // for
  for (unsigned int i = 0; i < params.numStudents; i+=1) {                                // wait for students to finish
    delete students[i];
  } // for
  delete bp;                                                                              // delete BP before vending machine which is stack allocated
                                                                                          // all stack allocated objects deleted
} // main
