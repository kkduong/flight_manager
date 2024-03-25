#ifndef MANAGER_H
#define MANAGER_H 

#include "airport.h"
#include <iostream>
#include <fstream>

using namespace std;

class Manager
{
private:
	int num_airports;	//number of airports
	Airport* a_arr;		//airport array

public:

	Manager();
	~Manager();

	void populate(ifstream& fin);
	int init();

	void print_menu();
	int get_menu_choice();
	string* collect_flight_info(string&, string&, int&);
	int collect_airport_choice();

	int check_dest_cap(int, int);
	int check_valid_airport(string);
	void update_file();
	
	void print_all();
	void check_flight_control();
	void add_flight_control();
	void cancel_flight_control();
	void take_off_control();
	void stats_control();

	void choice_loop();
	void run();

	
	
};
#endif