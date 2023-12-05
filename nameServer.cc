#include "nameServer.h"

using namespace std;

NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents )
    : prt(prt), numVendingMachines(numVendingMachines), numStudents(numStudents) {
        machines = new VendingMachine*[numVendingMachines];
        
        sid_to_machineid = new unsigned int[numStudents];
        // logically distributing the students evenly across the vending machines in a round-robin fashion
        for (unsigned int i = 0; i < numStudents; i++) {
            sid_to_machineid[i] = i % numVendingMachines;
        } // for
} // NameServer::NameServer

NameServer::~NameServer() {
    delete[] machines; // delete array, vending machine itself is cleanup elsewhere
    delete[] sid_to_machineid; // delete mapping of student id to machine id
} // NameServer::~NameServer

void NameServer::main() {
    PRINT( prt.print(Printer::NameServer, 'S'); )

    for (;;) {
        // all machines are registered before accepting calls to other members
        _Accept(~NameServer) {
            break;
        } or _When(machine_cnt < numVendingMachines) _Accept(VMregister) {
            machine_cnt+=1;
            PRINT( prt.print(Printer::NameServer, 'R', machine_cnt); )
        } or _When(machine_cnt == numVendingMachines) _Accept(getMachine) { 
            /*
            update the student's assigned machine id
            name server must cycle through the vending machines separately for each student 
            starting from the initial position via modulo incrementing to ensure a student 
            has a chance to visit every machine
            */ 
            PRINT( prt.print(Printer::NameServer, 'N', cur_id, sid_to_machineid[cur_id]);)
            sid_to_machineid[cur_id] = (sid_to_machineid[cur_id] + 1) % numVendingMachines;
        } or _When(machine_cnt == numVendingMachines) _Accept(getMachineList) {
        } // _Accept
    } // for

    PRINT( prt.print(Printer::NameServer, 'F'); )
} // NameServer::main

void NameServer::VMregister( VendingMachine * vendingmachine ) {
    machines[machine_cnt] = vendingmachine;
} // NameServer::VMregister

VendingMachine * NameServer::getMachine( unsigned int id ) {
    cur_id = id; // save value of id for main to use
    return machines[sid_to_machineid[id]]; // get the machine student is currently assigned to
} // NameServer::getMachine

VendingMachine** NameServer::getMachineList() {
    return machines;
} // NameServer::getMachineList
