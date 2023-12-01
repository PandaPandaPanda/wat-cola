#ifndef PRINTER_H
#define PRINTER_H

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
  	~Printer();                                                                       // added public dtor
  private:
	unsigned int numStudents, numVendingMachines, numCouriers;                      // number of voters
	struct Item {                                                                   // contains info to print messages correctly
		bool is_empty = true;                                                       // indicates if the buffer item has data to print.
		Kind kind;
        char state;
        BottlingPlant::Flavours f;
        unsigned int v1, v2;
	};
	Item* buffer;                                                                   // buffer array - dynamically allocated
	void flush();
	int return_id_for_kind(Kind kind);
	int return_id_for_kind_and_id(Kind kind, lid);
	void flush_parent(Item item);
	void flush_groupoff(Item item);
	void flush_office(Item item);
	void flush_name(Item item);
	void flush_truck(Item item);
	void flush_plant(Item item);
	void flush_student(Item item);
	void flush_vending(Item item);
	void flush_courier(Item item);

};

#endif
