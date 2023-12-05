#ifndef PRINTER_H
#define PRINTER_H

#ifdef NOOUTPUT
#define PRINT( stmt )
#else
#define PRINT( stmt ) stmt
#endif // NOOUTPUT

_Task BottlingPlant;

_Monitor Printer {
  public:
	enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
	Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
	void print( Kind kind, char state );
	void print( Kind kind, char state, unsigned int value1 );
	void print( Kind kind, char state, unsigned int value1, unsigned int value2 );
	void print( Kind kind, unsigned int lid, char state );
	void print( Kind kind, unsigned int lid, char state, unsigned int value1 );
	void print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 );
  	~Printer();                                                                     // added public dtor
  private:
	unsigned int numStudents, numVendingMachines, numCouriers;                      // number of voters
	struct Item {                                                                   // contains info to print messages correctly
		bool is_empty = true;                                                       // indicates if the buffer item has data to print.
		Kind kind;
        char state;
        unsigned int v1, v2;														// additional values to be printed next to state
	};
	Item* buffer;                                                                   // buffer array - dynamically allocated
	void flush();																	// flush buffer
	int return_id_for_kind(Kind kind);												// return id in buffer for Kinds with no IDs (ex. parent, etc)
	int return_id_for_kind_and_id(Kind kind, unsigned int lid);						// return id in buffer for Kinds with individual ids in its kind (ex. students, vending machines)
	void flush_parent(Item item);													// what to print if kind of element flushed is parent
	void flush_groupoff(Item item);													// what to print if kind of element flushed is groupoff
	void flush_office(Item item);													// what to print if kind of element flushed is watcard office
	void flush_name(Item item);														// what to print if kind of element flushed is name server
	void flush_truck(Item item);													// what to print if kind of element flushed is truck
	void flush_plant(Item item);													// what to print if kind of element flushed is plant
	void flush_student(Item item);													// what to print if kind of element flushed is student
	void flush_vending(Item item);													// what to print if kind of element flushed is vending machine
	void flush_courier(Item item);													// what to print if kind of element flushed is courier

};

#endif
