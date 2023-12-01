#include <uPRNG.h>
#include <iostream>
#include <string>
#include <uPRNG.h>

#include "unistd.h" // getpid

#include "config.h"

#include "printer.h"
#include "bank.h"
#include "parent.h"

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



} // main
