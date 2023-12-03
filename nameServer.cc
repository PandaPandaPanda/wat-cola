#include "nameServer.h"
#include <iostream>

using namespace std;

NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents )
    : prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
        machines = new VendingMachine*[numVendingMachines]();
    };

void NameServer::main() {
    for (;;) {
        _Accept(~NameServer) {
            break;
        } or _Accept(VMregister) {
            cout << "vm register called" << endl;
        } or _Accept(getMachineList) {
            cout << "machine list" << endl;
        } _Else {}
    }
}

void NameServer::VMregister( VendingMachine * vendingmachine ) {
    machines[cur_machine] = vendingmachine;
    cur_machine+=1;
}

VendingMachine** NameServer::getMachineList() {
    return machines;
}
