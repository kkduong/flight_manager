/******************************************************
** Program: airport.cpp
** Author: Kaelee Duong
** Date: 2/22/2024
** Description: declares the functions of the Airport class
** Input: N/A
** Output: N/A
******************************************************/
#include "airport.h"

using namespace std;

/*********************************************************************
** Function: Airport()
** Description: default constructor for the Airport class
** Parameters: N/A
** Pre-Conditions: Airport class has been created
** Post-Conditions: member variables of the Airport object have been set
					to some default values
*********************************************************************/ 
Airport::Airport() {
	/*sets all member variables to some values*/
	this->name = "";
	this->num_flights = 0;
	this->cap = 1;
}

/*********************************************************************
** Function: ~Airport()
** Description: destructor for Airport class
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: dynamic memory (if any) as been deleted
*********************************************************************/ 
Airport::~Airport() {
	/*deletes dynamic memory*/
	if (f_arr != nullptr) {
		delete [] f_arr;
		f_arr = nullptr;
	}
}

/*********************************************************************
** Function: get_name()
** Description: returns this Airport's name
** Parameters: N/A
** Pre-Conditions: name has been assigned
** Post-Conditions: name returned
*********************************************************************/ 
string Airport::get_name() const {
	return this->name;
}

/*********************************************************************
** Function: get_num_flights()
** Description: returns this Airport's number of flights
** Parameters: N/A
** Pre-Conditions: number of flights has been assigned
** Post-Conditions: number of flights returned
*********************************************************************/ 
int Airport::get_num_flights() const {
	return this->num_flights;
}

/*********************************************************************
** Function: get_cap()
** Description: returns this Airport's capacity
** Parameters: N/A
** Pre-Conditions: capacity has been assigned
** Post-Conditions: capacity returned
*********************************************************************/ 
int Airport::get_cap() const {
	return this->cap;
}

/*********************************************************************
** Function: populate_airport()
** Description: populates the Airport with information from a file
** Parameters: ifstream& - input file
** Pre-Conditions: file has been opened for reading
** Post-Conditions: Airport member variables are set
*********************************************************************/ 
void Airport::populate_airport(ifstream& fin){
	fin >> this->name;
	fin >> this->num_flights;
	fin >> this->cap;

	/*populate the flight array with each flight*/
	this->f_arr = new Flight[this->cap];
	for (int i = 0; i < this->num_flights; i++) {
		this->f_arr[i].populate_flight(fin);
	}

	return;
}

/*********************************************************************
** Function: print_flight_to_file()
** Description: prints a flight to the a file in a certain format
** Parameters: int - index of flight in flight array
			   ofstream& - output file
** Pre-Conditions: flight variables have been intialized and ofstream
				   object has been opened
** Post-Conditions: flight is printed to file in a correct format
*********************************************************************/ 
void Airport::print_flight_to_file(int idx, ofstream& file) {
	
	file << f_arr[idx].get_flight_num() << " ";
	file << f_arr[idx].get_curr_loc() << " ";
	file << f_arr[idx].get_dest() << " ";
	file << f_arr[idx].get_num_pilots() << " ";

	/*loops through each flight and prints each pilot to file*/
	for (int i = 0; i < f_arr[idx].get_num_pilots(); i++) {
		if (i == f_arr[idx].get_num_pilots()-1) {
			file << f_arr[idx].print_pilot(i) << endl;
		}
		else {
		file << f_arr[idx].print_pilot(i) << " ";
		}
	}
}

/*********************************************************************
** Function: add_flight()
** Description: adds a Flight to an Airport
** Parameters: Flight& - new Flight object
** Pre-Conditions: the new Flight has been constructed
** Post-Conditions: flight is added to the end of the flight array
					and number of flights is increased
*********************************************************************/ 
void Airport::add_a_flight(Flight& p){
	/*adds flight given to the end of the flight array*/
	this->f_arr[num_flights] = p;
	num_flights++;
	
	return;
}

/*********************************************************************
** Function: remove_flight()
** Description: removes a Flight from an Airport
** Parameters: int - index of the Flight being removed
** Pre-Conditions: N/A
** Post-Conditions: flight is removed from the flight array, all other
					flights are shifted to the left, and number of flights
					is decreased
*********************************************************************/ 
Flight Airport::remove_a_flight(int idx){
	/*saves the flight before removing it for returning*/
	Flight f = f_arr[idx];

	/*move all flights to the left from the index of the flight removed*/
	for(int i = idx+1; i < this->num_flights; i++) {

		f_arr[i-1] = f_arr[i];
	}

	num_flights--;
	
	return f;
}

/*********************************************************************
** Function: search_flight_num()
** Description: searches flight array of this Airport for a flight
				with the flight number provided
** Parameters: string - desired flight number
** Pre-Conditions: N/A
** Post-Conditions: if the flight is found, print it to screen, and return 1,
					else return 0
*********************************************************************/ 
int Airport::search_flight_num(string num) {
	/*checks each flight to see if it has the same flight number*/
	for(int i = 0; i < num_flights; i++) {
		/*if found print the flight*/
		if (f_arr[i].get_flight_num() == num) {
			cout << "Flight Found!" << endl;
			cout << "----------------------" << endl;
			f_arr[i].print_flight();
			cout << "----------------------" << endl;
			cout << endl;
			return 1;
		}
	}

	return 0;
}

/*********************************************************************
** Function: get_flight_des()
** Description: gets the destination of a flight
** Parameters: int - index of the flight desired
** Pre-Conditions: N/A
** Post-Conditions: returns the destination of the flight
*********************************************************************/ 
string Airport::get_flight_des(int f_idx) {
	return f_arr[f_idx].get_dest();
}

/*********************************************************************
** Function: flights_with_dest()
** Description: calculates the number of flights in the flight array
				that have a certain airport as a destination
** Parameters: string - destination airport
** Pre-Conditions: N/A
** Post-Conditions: returns number of flights with said destination
*********************************************************************/ 
int Airport::flights_with_dest(string name) {
	int num = 0;

	/*loop through all flights, if the flight has the destination, increment num*/
	for (int i = 0; i < num_flights; i++) {
		if (f_arr[i].get_dest() == name) {
			num++;
		}
	}

	return num;
}

/*********************************************************************
** Function: print_airport()
** Description: prints an airport to the terminal
** Parameters: N/A
** Pre-Conditions: airport variables have been intialized
** Post-Conditions: airport is printed to screen
*********************************************************************/ 
void Airport::print_airport() {
	//Your code goes here:
	cout << "**********************************" << endl;
	cout << "******Airport Name: " << this->name << "******" << endl;
	cout << "Capacity: " << this->cap << endl;

	/*loops through to print out each flight*/
	for(int i = 0; i < num_flights; i++) {
		cout << "Flight " << i+1 << ":" << endl;
		cout << "----------------------" << endl;
		f_arr[i].print_flight();
		cout << "----------------------" << endl;

	}

	cout << endl;

	return; 
}

