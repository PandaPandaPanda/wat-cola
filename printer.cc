#include <iostream>
#include "printer.h"

using namespace std;

Printer::Printer(unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers) 
    : numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {
    buffer = new Printer::Item[numStudents+numVendingMachines+numCouriers+6];  // create buffer
    buffer[0].Kind = Printer::Kind::Parent;
    buffer[1].Kind = Printer::Kind::Groupoff;
    buffer[2].Kind = Printer::Kind::WATCardOffice;
    buffer[3].Kind = Printer::Kind::NameServer;
    buffer[4].Kind = Printer::Kind::Truck;
    buffer[5].Kind = Printer::Kind::BottlingPlant;
    for (unsigned int i = 6; i < 6+numStudents; i+=1) {
        buffer[i].Kind = Printer::Kind::Student
    }
    for (unsigned int i = 6+numStudents; i < 6+numStudents+numVendingMachines; i+=1) {
        buffer[i].Kind = Printer::Kind::Vending
    }
    for (unsigned int i = 6+numStudents+numVendingMachines; i < numStudents+numVendingMachines+numCouriers+6; i+=1) {
        buffer[i].Kind = Printer::Kind::Courier
    }
    PRINT({
        cout << "Parent\tGroupoff\tWATOff\tNames\tTruck\tTruck\tPlant\t";
        for (unsigned int i = 0; i < numStudents; i += 1) {  // print beginning vector labels
            cout << "Stud" << i << "\t";
        }  // for
        for (unsigned int i = 0; i < numVendingMachines; i += 1) {  // print beginning vector labels
            cout << "Mach" << i << "\t";
        }  // for
        for (unsigned int i = 0; i < numCouriers; i += 1) {  // print beginning vector labels
            cout << "Cour" << i << "\t";
        }  // for
        cout << endl;
        for (unsigned int i = 0; i < numStudents+numVendingMachines+numCouriers+6; i += 1) {
            cout << "*******"
                 << "\t";
        }  // for
        cout << endl;
    })

}  // Printer

Printer::~Printer() {
    PRINT({
        Printer::flush();                                           // flush buffer before ending
        std::cout << "*****************" << std::endl;              // print ending lines
    })

    delete[] buffer;
} // ~Printer

void Printer::flush_parent(Item item) {
    switch(buffer[i].state) {
        case 'S':
            cout << "S";
            break;
        case 'D':
            cout << "D" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'F':
            cout << 'F';
            break; 
    }
}
void Printer::flush_groupoff(Item item) {
    switch(buffer[i].state) {
        case 'S':
            cout << "S";
            break;
        case 'D':
            cout << "D" << buffer[i].v1;
            break;
        case 'F':
            cout << 'F';
            break; 
    }
};
void Printer::flush_office(Item item) {
    switch(buffer[i].state) {
        case 'S':
            cout << "S";
            break;
        case 'W':
            cout << "W";
            break;
        case 'C':
            cout << "C" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'T':
            cout << "T" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'F':
            cout << 'F';
            break; 
    }
}
void Printer::flush_name(Item item) {
    switch(buffer[i].state) {
        case 'S':
            cout << "S";
            break;
        case 'R':
            cout << "R" << buffer[i].v1;
            break;
        case 'N':
            cout << "N" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'F':
            cout << 'F';
            break; 
    }
}
void Printer::flush_truck(Item item) {
    switch(buffer[i].state) {
        case 'S':
            cout << "S";
            break;
        case 'P':
            cout << "P" << buffer[i].v1;
            break;
        case 'd':
            cout << "d" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'U':
            cout << "U" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'D':
            cout << "D" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'W':
            cout << 'W';
            break; 
        case 'F':
            cout << 'F';
            break; 
    }
}
void Printer::flush_plant(Item item) {
    switch(buffer[i].state) {
        case 'S':
            cout << "S";
            break;
        case 'G':
            cout << "G" << buffer[i].v1;
            break;
        case 'P':
            cout << 'P';
            break; 
        case 'F':
            cout << 'F';
            break; 
    }
}
void Printer::flush_student(Item item) {
    switch(buffer[i].state) {
        case 'S':
            cout << "S" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'V':
            cout << "V" << buffer[i].v1;
            break;
        case 'G':
            cout << "G" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'B':
            cout << "B" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'a':
            cout << "a" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'A':
            cout << "A" << buffer[i].v1 << "," << buffer[i].v2;
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
    }
}
void Printer::flush_vending(Item item) {
    switch(buffer[i].state) {
        case 'S':
            cout << "S" << buffer[i].v1;
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
            cout << "B" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'F':
            cout << 'F';
            break; 
    }
}
void Printer::flush_courier(Item item) {
    switch(buffer[i].state) {
        case 'S':
            cout << "S";
            break;
        case 't':
            cout << "t" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'L':
            cout << "L" << buffer[i].v1;
            break;
        case 'T':
            cout << "T" << buffer[i].v1 << "," << buffer[i].v2;
            break;
        case 'F':
            cout << 'F';
            break; 
    }
}

void Printer::flush() {
    for (unsigned int i = 0; i < voters; i+=1) {
        if (!buffer[i].is_empty) {                                  // only print if buffer item is not empty
            switch(buffer[i].Kind) {                               // print according to specifications based on state
                case Printer::Kind::Parent:
                    flush_parent(buffer[i]);
                case Printer::Kind::Groupoff:
                    flush_groupoff(buffer[i]);
                case Printer::Kind::WATCardOffice:
                    flush_office(buffer[i]);
                case Printer::Kind::NameServer:
                    flush_name(buffer[i]);
                case Printer::Kind::Truck:
                    flush_truck(buffer[i]);
                case Printer::Kind::BottlingPlant:
                    flush_plant(buffer[i]);
                case Printer::Kind::Student:
                    flush_student(buffer[i]);
                case Printer::Kind::Vending:
                    flush_vending(buffer[i]);
                case Printer::Kind::Courier;
                    flush_courier(buffer[i]);
            } // switch
            buffer[i].is_empty = true;                              // slot is flushed - now empty
        } // if
        cout << '\t';

    } // for
    cout << endl;
} // Printer::flush
int Printer::return_id_for_kind(Kind kind) {
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
    }
}

int Printer::return_id_for_kind_and_id(Kind kind, unsigned int lid) {
    id = 6+lid;
    if (kind == Printer::Kind::Vending) {
        id += numStudents;
    } else if (kind == Printer::Kind::Courier) {
        id += numStudents+numVendingMachines;
    }
    return id;
}

void Printer::print( Kind kind, char state ) {
    int id = return_id_for_kind(kind);
    if (!buffer[id].is_empty) {                                     // if overwriting slot - flush first
        Printer::flush();
    } // if
    buffer[id].is_empty = false;                                    // set slot as occupied
    buffer[id].state = state;                                       // set state
}
void Printer::print( Kind kind, char state, unsigned int value1 ) {
    int id = return_id_for_kind(kind);
    if (!buffer[id].is_empty) {                                     // if overwriting slot - flush first
        Printer::flush();
    } // if
    buffer[id].is_empty = false;                                    // set slot as occupied
    buffer[id].state = state;                                       // set state
    buffer[id].v1 = value1;
}
void Printer::print( Kind kind, char state, unsigned int value1, unsigned int value2 ) {
    int id = return_id_for_kind(kind);
    if (!buffer[id].is_empty) {                                     // if overwriting slot - flush first
        Printer::flush();
    } // if
    buffer[id].is_empty = false;                                    // set slot as occupied
    buffer[id].state = state;                                       // set state
    buffer[id].v1 = value1;
    buffer[id].v2 = value2;
}
void Printer::print( Kind kind, unsigned int lid, char state ) {
    int id = return_id_for_kind_and_id(kind, lid);
    if (!buffer[id].is_empty) {                                     // if overwriting slot - flush first
        Printer::flush();
    } // if
    buffer[id].is_empty = false;                                    // set slot as occupied
    buffer[id].state = state;                                       // set state
}
void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1 ) {
    int id = return_id_for_kind_and_id(kind, lid);
    if (!buffer[id].is_empty) {                                     // if overwriting slot - flush first
        Printer::flush();
    } // if
    buffer[id].is_empty = false;                                    // set slot as occupied
    buffer[id].state = state;                                       // set state
    buffer[id].v1 = value1;
}
void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 ) {
    int id = return_id_for_kind_and_id(kind, lid);
    if (!buffer[id].is_empty) {                                     // if overwriting slot - flush first
        Printer::flush();
    } // if
    buffer[id].is_empty = false;                                    // set slot as occupied
    buffer[id].state = state;                                       // set state
    buffer[id].v1 = value1;
    buffer[id].v2 = value2;
}
