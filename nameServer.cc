#include "nameServer.h"

using namespace std;

NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents )
    : prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
        machines = new VendingMachine[numVendingMachines]();
    };

void NameServer::VMregister( VendingMachine * vendingmachine ) {
    machines[cur_machine] = vendingMachine;
    cur_machine+=1;
}

NameServer::getMachineList() {
    return machines;
}
