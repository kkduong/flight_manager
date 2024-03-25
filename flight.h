#ifndef FLIGHT_H
#define FLIGHT_H 

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Flight
{
private: 
	string flight_num;		//flight number
	string curr_loc;		//current airport
	string dest;			//destination 
	int num_pilots;			//number of pilots
	string* pilots;			//pilot array

public:

	Flight();
	Flight(string, string, string, int, string*);

	Flight& operator=(const Flight&);
	Flight(const Flight&);
	~Flight();

	string get_flight_num() const;
	string get_curr_loc() const;
	string get_dest() const;
	int get_num_pilots() const;
	string* get_pilots() const;

	void set_flight_num(const string);
	void set_curr_loc(const string);
	void set_dest(const string);
	void set_num_pilots(const int);
	void set_pilots(string*);

	void populate_flight(ifstream&);
	void print_flight();
	string print_pilot(int);



	
	
};

#endif
