#include <iostream>
#include "printer.h"

using namespace std;

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers) 
    : numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {
    buffer = new Printer::Item[numStudents+numVendingMachines+numCouriers+6];           // create buffer
    buffer[0].kind = Printer::Kind::Parent;                                             // create items for Kinds with no ids
    buffer[1].kind = Printer::Kind::Groupoff;
    buffer[2].kind = Printer::Kind::WATCardOffice;
    buffer[3].kind = Printer::Kind::NameServer;
    buffer[4].kind = Printer::Kind::Truck;
    buffer[5].kind = Printer::Kind::BottlingPlant;
    for (unsigned int i = 6; i < 6+numStudents; i+=1) {                                 
        buffer[i].kind = Printer::Kind::Student;                                        // create items for students
    } // for
    for (unsigned int i = 6+numStudents; i < 6+numStudents+numVendingMachines; i+=1) {  
        buffer[i].kind = Printer::Kind::Vending;                                        // create items for vending machines
    } // for
    for (unsigned int i = 6+numStudents+numVendingMachines; i < numStudents+numVendingMachines+numCouriers+6; i+=1) {
        buffer[i].kind = Printer::Kind::Courier;                                        // create items for couriers
    } // for
    PRINT({
        cout << "Parent\tGropoff\tWATOff\tNames\tTruck\tPlant\t";                       // print beginning labels
        for (unsigned int i = 0; i < numStudents; i += 1) {                             // print beginning student labels
            cout << "Stud" << i << "\t";
        }  // for
        for (unsigned int i = 0; i < numVendingMachines; i += 1) {                      // print beginning vending machine labels
            cout << "Mach" << i << "\t";
        }  // for
        for (unsigned int i = 0; i < numCouriers; i += 1) {                             // print beginning courier labels
            cout << "Cour" << i << "\t";
        }  // for
        cout << endl;
        for (unsigned int i = 0; i < numStudents+numVendingMachines+numCouriers+6; i += 1) {
            cout << "*******"
                 << "\t";
        }  // for
        cout << endl;
    }) // PRINT

}  // Printer ctor

Printer::~Printer() {
    PRINT({
        Printer::flush();                                           // flush buffer before ending
        std::cout << "*****************" << std::endl;              // print ending lines
    }) // PRINT

    delete[] buffer;
} // Printer dtor

void Printer::flush_parent(Item item) {                             // what to print if item is a parent
    switch(item.state) {
        case 'S':
            cout << "S";
            break;
        case 'D':
            cout << "D" << item.v1 << "," << item.v2;
            break;
        case 'F':
            cout << 'F';
            break; 
    } // switch
} // Printer::flush_parent

void Printer::flush_groupoff(Item item) {                           // what to print if item is a groupoff
    switch(item.state) {
        case 'S':
            cout << "S";
            break;
        case 'D':
            cout << "D" << item.v1;
            break;
        case 'F':
            cout << 'F';
            break; 
    } // switch
} // Printer::flush_groupoff

void Printer::flush_office(Item item) {                             // what to print if item is a watcard office
    switch(item.state) {
        case 'S':
            cout << "S";
            break;
        case 'W':
            cout << "W";
            break;
        case 'C':
            cout << "C" << item.v1 << "," << item.v2;
            break;
        case 'T':
            cout << "T" << item.v1 << "," << item.v2;
            break;
        case 'F':
            cout << 'F';
            break; 
    } // switch
} // Printer::flush_office

void Printer::flush_name(Item item) {                               // what to print if item is a name server
    switch(item.state) {
        case 'S':
            cout << "S";
            break;
        case 'R':
            cout << "R" << item.v1;
            break;
        case 'N':
            cout << "N" << item.v1 << "," << item.v2;
            break;
        case 'F':
            cout << 'F';
            break; 
    } // switch
} // Printer::flush_name

void Printer::flush_truck(Item item) {                              // what to print if item is a truck
    switch(item.state) {
        case 'S':
            cout << "S";
            break;
        case 'P':
            cout << "P" << item.v1;
            break;
        case 'd':
            cout << "d" << item.v1 << "," << item.v2;
            break;
        case 'U':
            cout << "U" << item.v1 << "," << item.v2;
            break;
        case 'D':
            cout << "D" << item.v1 << "," << item.v2;
            break;
        case 'W':
            cout << 'W';
            break; 
        case 'F':
            cout << 'F';
            break; 
    } // switch
} // Printer::flush_truck

void Printer::flush_plant(Item item) {                              // what to print if item is a bottling plant
    switch(item.state) {
        case 'S':
            cout << "S";
            break;
        case 'G':
            cout << "G" << item.v1;
            break;
        case 'P':
            cout << 'P';
            break; 
        case 'F':
            cout << 'F';
            break; 
    } // switch
} // Printer::flush_plant

void Printer::flush_student(Item item) {                            // what to print if item is a student
    switch(item.state) {
        case 'S':
            cout << "S" << item.v1 << "," << item.v2;
            break;
        case 'V':
            cout << "V" << item.v1;
            break;
        case 'G':
            cout << "G" << item.v1 << "," << item.v2;
            break;
        case 'B':
            cout << "B" << item.v1 << "," << item.v2;
            break;
        case 'a':
            cout << "a" << item.v1 << "," << item.v2;
            break;
        case 'A':
            cout << "A" << item.v1 << "," << item.v2;
            break;
        case 'X':
            cout << 'X';
            break; 
        case 'L':
            cout << 'L';
            break; 
        case 'F':
            cout << 'F';
            break; 
    } // switch
} // Printer::flush_student

void Printer::flush_vending(Item item) {                            // what to print if item is a vending machine
    switch(item.state) {
        case 'S':
            cout << "S" << item.v1;
            break;
        case 'r':
            cout << "r";
            break;
        case 'R':
            cout << "R";
            break;
        case 'A':
            cout << "A";
            break;
        case 'B':
            cout << "B" << item.v1 << "," << item.v2;
            break;
        case 'F':
            cout << 'F';
            break; 
    } // switch
} // Printer::flush_vending

void Printer::flush_courier(Item item) {                            // what to print if item is a courier
    switch(item.state) {
        case 'S':
            cout << "S";
            break;
        case 't':
            cout << "t" << item.v1 << "," << item.v2;
            break;
        case 'L':
            cout << "L" << item.v1;
            break;
        case 'T':
            cout << "T" << item.v1 << "," << item.v2;
            break;
        case 'F':
            cout << 'F';
            break; 
    } // switch
} // Printer::flush_courier

void Printer::flush() {
    for (unsigned int i = 0; i < numStudents+numVendingMachines+numCouriers+6; i+=1) {
        if (!buffer[i].is_empty) {                                  // only print if buffer item is not empty
            switch(buffer[i].kind) {                                // print according to specifications based on state and kind
                case Printer::Kind::Parent:
                    flush_parent(buffer[i]);
                    break;
                case Printer::Kind::Groupoff:
                    flush_groupoff(buffer[i]);
                    break;
                case Printer::Kind::WATCardOffice:
                    flush_office(buffer[i]);
                    break;
                case Printer::Kind::NameServer:
                    flush_name(buffer[i]);
                    break;
                case Printer::Kind::Truck:
                    flush_truck(buffer[i]);
                    break;
                case Printer::Kind::BottlingPlant:
                    flush_plant(buffer[i]);
                    break;
                case Printer::Kind::Student:
                    flush_student(buffer[i]);
                    break;
                case Printer::Kind::Vending:
                    flush_vending(buffer[i]);
                    break;
                case Printer::Kind::Courier:
                    flush_courier(buffer[i]);
                    break;
            } // switch
            buffer[i].is_empty = true;                              // slot is flushed - now empty
        } // if
        cout << '\t';

    } // for
    cout << endl;
} // Printer::flush

int Printer::return_id_for_kind(Kind kind) {                        // return id in buffer for Kinds with no IDs (ex. parent, etc)
    switch(kind) {
        case Printer::Kind::Parent:
            return 0;
        case Printer::Kind::Groupoff:
            return 1;
        case Printer::Kind::WATCardOffice:
            return 2;
        case Printer::Kind::NameServer:
            return 3;
        case Printer::Kind::Truck:
            return 4;
        case Printer::Kind::BottlingPlant:
            return 5;
        default:
            return -1;
    } // switch
} // Printer::return_id_for_kind
                                                                    // return id in buffer for Kinds with individual ids in its kind (ex. students, vending machines)
int Printer::return_id_for_kind_and_id(Kind kind, unsigned int lid) { 
    unsigned int id = 6+lid;
    if (kind == Printer::Kind::Vending) {
        id += numStudents;
    } else if (kind == Printer::Kind::Courier) {
        id += numStudents+numVendingMachines;
    } // if
    return id;
} // Printer::return_id_for_kind_and_id

void Printer::print( Kind kind, char state ) {
    int id = return_id_for_kind(kind);
    if (!buffer[id].is_empty) {                                     // if overwriting slot - flush first
        flush();
    } // if
    buffer[id].is_empty = false;                                    // set slot as occupied
    buffer[id].state = state;                                       // set state
} // Printer::print( Kind kind, char state )

void Printer::print( Kind kind, char state, unsigned int value1 ) {
    int id = return_id_for_kind(kind);
    if (!buffer[id].is_empty) {                                     // if overwriting slot - flush first
        flush();
    } // if
    buffer[id].is_empty = false;                                    // set slot as occupied
    buffer[id].state = state;                                       // set state
    buffer[id].v1 = value1;
} // Printer::print( Kind kind, char state, unsigned int value1 )

void Printer::print( Kind kind, char state, unsigned int value1, unsigned int value2 ) {
    int id = return_id_for_kind(kind);
    if (!buffer[id].is_empty) {                                     // if overwriting slot - flush first
        Printer::flush();
    } // if
    buffer[id].is_empty = false;                                    // set slot as occupied
    buffer[id].state = state;                                       // set state
    buffer[id].v1 = value1;
    buffer[id].v2 = value2;
} // Printer::print( Kind kind, char state, unsigned int value1, unsigned int value2 )

void Printer::print( Kind kind, unsigned int lid, char state ) {
    int id = return_id_for_kind_and_id(kind, lid);
    if (!buffer[id].is_empty) {                                     // if overwriting slot - flush first
        Printer::flush();
    } // if
    buffer[id].is_empty = false;                                    // set slot as occupied
    buffer[id].state = state;                                       // set state
} // Printer::print( Kind kind, unsigned int lid, char state )

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1 ) {
    int id = return_id_for_kind_and_id(kind, lid);
    if (!buffer[id].is_empty) {                                     // if overwriting slot - flush first
        Printer::flush();
    } // if
    buffer[id].is_empty = false;                                    // set slot as occupied
    buffer[id].state = state;                                       // set state
    buffer[id].v1 = value1;
} // Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1 )

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 ) {
    int id = return_id_for_kind_and_id(kind, lid);
    if (!buffer[id].is_empty) {                                     // if overwriting slot - flush first
        Printer::flush();
    } // if
    buffer[id].is_empty = false;                                    // set slot as occupied
    buffer[id].state = state;                                       // set state
    buffer[id].v1 = value1;
    buffer[id].v2 = value2;
} // Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 )
