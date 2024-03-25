/******************************************************
** Program: flight.cpp
** Author: Kaelee Duong
** Date: 2/22/2024
** Description: declares the functions of the Manager class
** Input: N/A
** Output: N/A
******************************************************/
#include "flight.h"

using namespace std;

/*********************************************************************
** Function: Flight()
** Description: default constructor for the Flight class
** Parameters: N/A
** Pre-Conditions: Flight class has been created
** Post-Conditions: member variables of the Flight object have been set
					to some default values
*********************************************************************/ 
Flight::Flight() {
	/*sets all member variables to some values*/
	this->flight_num = "";
	this->curr_loc = "";
	this->dest = "";
	this->num_pilots = 1;
	this->pilots = new string[this->num_pilots];
}

/*********************************************************************
** Function: Flight()
** Description: non-default constructor for the Flight class
** Parameters: strings for flight numbers, current locations, and destinations,
			   an integer from number of pilots, and a string* of pilot names
** Pre-Conditions: Flight class has been created
** Post-Conditions: member variables of the Flight object have been set
					to user specified values
*********************************************************************/ 
Flight::Flight(string f_num, string loc, string des, int p_num, string* p) {
	/*sets all member variables to values given*/
	this->flight_num = f_num;
	this->curr_loc = loc;
	this->dest = des;
	this->num_pilots = p_num;
	this->pilots = new string[this->num_pilots];

	/*makes a deep copy of the array given*/
	for (int i = 0; i < num_pilots; i++) {
		this->pilots[i] = p[i];
	}
}

/*********************************************************************
** Function: operator=()
** Description: assignment overload operator for Flight class
** Parameters: the reference to a Flight object
** Pre-Conditions: The Flight object being assigned has values in its
				   member variables
** Post-Conditions: member variables of the Flight object have been set
					to some values
*********************************************************************/ 
Flight& Flight::operator=(const Flight& f) {
	this->flight_num = f.flight_num;
	this->curr_loc = f.curr_loc;
	this->dest = f.dest;
	this->num_pilots = f.num_pilots;

	/*checks if the pilots pointer is pointing to something*/
	if (this->pilots != nullptr) {
		delete [] this->pilots;
	}

	/*creates a deep copy of the pilots array from the other flight*/
	this->pilots = new string[this->num_pilots];
	for(int i = 0; i < this->num_pilots; i++) {
		this->pilots[i] = f.pilots[i];
	}

	return *this;
}

/*********************************************************************
** Function: Flight()
** Description: copy constructor for Flight class
** Parameters: the reference to a Flight object
** Pre-Conditions: The Flight object being assigned has values in its
				   member variables
** Post-Conditions: member variables of the new Flight object have been set
					to some values
*********************************************************************/ 
Flight::Flight(const Flight& f) {
	this->flight_num = f.flight_num;
	this->curr_loc = f.curr_loc;
	this->dest = f.dest;
	this->num_pilots = f.num_pilots;

	/*creates a deep copy of the pilots array from the other flight*/
	this->pilots = new string[this->num_pilots];
	for(int i = 0; i < this->num_pilots; i++) {
		this->pilots[i] = f.pilots[i];
	}
}

/*********************************************************************
** Function: ~Flight()
** Description: destructor for Flight class
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: dynamic memory (if any) as been deleted
*********************************************************************/ 
Flight::~Flight(){
	/*deletes dynamic memory*/
	if (pilots != nullptr) {
		delete [] pilots;
		pilots = nullptr;
	}
}

/*********************************************************************
** Function: get_flight_num()
** Description: returns this Flights's flight number
** Parameters: N/A
** Pre-Conditions: flight number has been assigned
** Post-Conditions: flight number returned
*********************************************************************/ 
string Flight::get_flight_num() const{
	return this->flight_num;
}

/*********************************************************************
** Function: get_curr_loc()
** Description: returns this Flights's current location
** Parameters: N/A
** Pre-Conditions: current location has been assigned
** Post-Conditions: current location returned
*********************************************************************/ 
string Flight::get_curr_loc() const {
	return this->curr_loc;
}

/*********************************************************************
** Function: get_dest()
** Description: returns this Flights's destination
** Parameters: N/A
** Pre-Conditions: destination has been assigned
** Post-Conditions: destination returned
*********************************************************************/ 
string Flight::get_dest() const {
	return this->dest;
}

/*********************************************************************
** Function: get_num_pilots()
** Description: returns this Flights's number of pilots
** Parameters: N/A
** Pre-Conditions: number of pilots has been assigned
** Post-Conditions: number of pilots returned
*********************************************************************/ 
int Flight::get_num_pilots() const {
	return this->num_pilots;
}

/*********************************************************************
** Function: set_flight_num()
** Description: sets this Flights's flight number as another
** Parameters: string - new flight number
** Pre-Conditions: N/A
** Post-Conditions: flight number is set to new value
*********************************************************************/ 
void Flight::set_flight_num(const string num) {
	this->flight_num = num;
}

/*********************************************************************
** Function: set_curr_loc()
** Description: sets this Flights's current location as another
** Parameters: string - new current location
** Pre-Conditions: N/A
** Post-Conditions: current location is set to new value
*********************************************************************/ 
void Flight::set_curr_loc(const string loc) {
	this->curr_loc = loc;
}

/*********************************************************************
** Function: set_dest()
** Description: sets this Flights's destination as another
** Parameters: string - new destination
** Pre-Conditions: N/A
** Post-Conditions: destination is set to new value
*********************************************************************/ 
void Flight::set_dest(const string new_dest) {
	this->dest = new_dest;
}

/*********************************************************************
** Function: set_num_pilots()
** Description: sets this Flights's number of pilots as another
** Parameters: int - new number of pilots
** Pre-Conditions: N/A
** Post-Conditions: number of pilots is set to new value
*********************************************************************/ 
void Flight::set_num_pilots(const int p) {
	this->num_pilots = p;
}

/*********************************************************************
** Function: set_pilots()
** Description: sets this Flights's pilot array as another
** Parameters: string* - new pilot array
** Pre-Conditions: N/A
** Post-Conditions: pilot array is set to new values
*********************************************************************/ 
void Flight::set_pilots(string* arr) {
	this->pilots = new string[num_pilots];

	for(int i = 0; i < num_pilots; i++) {
		pilots[i] = arr[i];
	}
}

/*********************************************************************
** Function: populate_flight()
** Description: populates the Flight with information from a file
** Parameters: ifstream& - input file
** Pre-Conditions: file has been opened for reading
** Post-Conditions: Flight member variables are set
*********************************************************************/ 
void Flight::populate_flight(ifstream& fin) {
	//Your code goes here:
	fin >> this->flight_num;
	fin >> this->curr_loc;
	fin >> this->dest;
	fin >> this->num_pilots;

	/*checks if the pilots pointer is pointing to something*/
	if (this->pilots != nullptr) {
		delete [] this->pilots;
	}

	/*populate the pilot array with the pilot names from file*/
	this->pilots = new string[this->num_pilots];
	for(int i = 0; i < this->num_pilots; i++) {
		fin >> this->pilots[i];
	}
}

/*********************************************************************
** Function: print_flight()
** Description: prints a flight to the terminal
** Parameters: N/A
** Pre-Conditions: flight variables have been intialized
** Post-Conditions: flight is printed to screen
*********************************************************************/ 
void Flight::print_flight() {
	cout << "Flight #: " << this->flight_num << endl;
	cout << "Current at: " << this->curr_loc << endl;
	cout << "Destination: " << this->dest << endl;

	/*loop through pilot array to print all pilot names*/
	for (int i = 0; i < this->num_pilots; i++) {
		cout << "Pilot " << i+1 << ": " << pilots[i] << endl;
	}

}

/*********************************************************************
** Function: print_pilot()
** Description: returns the pilot name at a certain index
** Parameters: int - index of Flight in Flight array
** Pre-Conditions: N/A
** Post-Conditions: returns the string of the pilot name
*********************************************************************/ 
string Flight::print_pilot(int idx) {
	return pilots[idx];
}




