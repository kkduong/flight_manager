#ifndef AIRPORT_H
#define AIRPORT_H 

#include <iostream>
#include <string>
#include <fstream>

#include "flight.h"

using namespace std;

class Airport
{
private:
	string name;		//airport name
	int num_flights;	//number of flights
	int cap;			//capacity
	Flight *f_arr;		//flight array

public:

	Airport();
	~Airport();

	string get_name() const;
	int get_num_flights() const;
	int get_cap() const;
	Flight* get_f_arr() const;

	void set_name(const string);
	void set_num_flights(const int);
	void set_cap(const int);
	void set_f_arr(Flight*);

	void populate_airport(ifstream& fin);

	void add_a_flight(Flight& p);
	Flight remove_a_flight(int idx);
	int search_flight_num(string);
	string get_flight_des(int);
	int flights_with_dest(string);
	void print_flight_to_file(int, ofstream&);


	void print_airport();
	
	
};
#endif