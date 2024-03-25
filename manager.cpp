/******************************************************
** Program: manager.cpp
** Author: Kaelee Duong
** Date: 2/22/2024
** Description: declares the functions of the Manager class
** Input: N/A
** Output: N/A
******************************************************/
#include "manager.h"

using namespace std;

/*********************************************************************
** Function: Manager()
** Description: default constructor for the Manager class
** Parameters: N/A
** Pre-Conditions: Manager class has been created
** Post-Conditions: member variables of the Manager object have been set
					to some default values
*********************************************************************/ 
Manager::Manager(){
	this->num_airports = 0;
}

/*********************************************************************
** Function: ~Manager()
** Description: destructor for Manager class
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: dynamic memory (if any) as been deleted
*********************************************************************/ 
Manager::~Manager() {
	/*deletes dynamic memory*/
	if (a_arr != nullptr) {
		delete [] a_arr;
		a_arr = nullptr;
	}
}

/*********************************************************************
** Function: populate()
** Description: populates the manager, all airports, and flights 
				with information from a file
** Parameters: ifstream& - input file
** Pre-Conditions: file has been opened for reading
** Post-Conditions: All information has been populated
*********************************************************************/ 
void Manager::populate(ifstream& fin) {
	//Your code goes here:
	fin >> this->num_airports;

	/*populates every airport which in turn populates every flight*/
	this-> a_arr = new Airport[this->num_airports];
	for (int i = 0; i < this->num_airports; i++) {
		this->a_arr[i].populate_airport(fin);
	}
	
	return; 
}

/*********************************************************************
** Function: init()
** Description: open airport file and populate all information
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: all information has been intialized from file
*********************************************************************/ 
int Manager::init(){
	ifstream fin("airport.txt");
	//Error opening file?:
	if(!fin.is_open()){
		cout << "Error loading file." << endl;
		cout << endl;
		return 0;
	}

	/*since file is open, populate manager*/
	Manager::populate(fin);
	return 1;
}

/*********************************************************************
** Function: print_menu()
** Description: populates the Airport with information from a file
** Parameters: ifstream& - input file
** Pre-Conditions: file has been opened for reading
** Post-Conditions: Airport member variables are set
*********************************************************************/ 
void Manager::print_menu(){
	cout << endl;
	cout << "1. View all Airports & Flights info" << endl;
	cout << "2. Check flight info" << endl;
	cout << "3. Add a new flight" << endl;
	cout << "4. Cancel a flight" << endl;
	cout << "5. Take off a flight" << endl;
	cout << "6. Print airport stats" << endl;
	cout << "7. Quit" << endl;

	cout << endl;
	cout << "Your choice: ";
}

/*********************************************************************
** Function: print_menu()
** Description: populates the Airport with information from a file
** Parameters: ifstream& - input file
** Pre-Conditions: file has been opened for reading
** Post-Conditions: Airport member variables are set
*********************************************************************/ 
int Manager::get_menu_choice() {
	int choice = 0;
	Manager::print_menu();
	cin >> choice;

	/*if not a valid choice:*/
	while (choice < 1 || choice > 7) {
		cout << "Invalid input. Your choice: ";
		cin >> choice;
	}
	
	return choice;
}

/*********************************************************************
** Function: collect_flight_info()
** Description: collects flight information from user for the purpose 
				of adding a flight to an airport
** Parameters: string& - reference to variable to hold flight number
			   string& - reference to variable to hold destination
			   int& - reference to variable to hold number of pilots
** Pre-Conditions: N/A
** Post-Conditions: returns a string array of pilot names
*********************************************************************/ 
string* Manager::collect_flight_info(string& f, string& d, int& num) {
	cout << "Enter flight number: ";
	cin >> f;
	cout << "Enter destination: ";
	cin >> d;

	/*checks if the airport exists*/
	while(Manager::check_valid_airport(d) == 1) {
		cout << "Enter a valid airport: ";
		cin >> d;
	}

	cout << "Enter the number of pilots: ";
	cin >> num;

	/*checks if pilots is not 0 or negative*/
	while (num < 1) {
		cout << "Please enter a valid number of pilots: ";
		cin >> num;
	}

	string* p = new string[num];

	for (int i = 0; i < num; i++) {
		cout << "Enter name for pilot " << i+1 << ": ";
		cin >> p[i];
	}

	return p;
}

/*********************************************************************
** Function: collect_airport_choice()
** Description: collects the airport that the user wants to add, remove
				or take a flight off from
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: returns the index of the desired airport
*********************************************************************/ 
int Manager::collect_airport_choice() {
	int a;

	cout << endl;

	/*prints every airport*/
	for (int i = 1; i <= num_airports; i++) {
		cout << i << ": Airport " << a_arr[i-1].get_name() << endl;
	}

	cout << endl;
	cout << "Choose an airport (by number on the left): ";
	cin >> a;

	/*makes sure the user is entering a valid airport*/
	while (a > num_airports) {
		cout << "Invalid input. Choose an airport: ";
		cin >> a;
	}
	
	/*decrements user input to get index*/
	a--;

	cout << endl; 
	
	return a;
}

/*********************************************************************
** Function: check_dest_cap()
** Description: checks if the destination airport is at capacity
** Parameters: int - index of current location in airport array
			   int - index of flight in flight array
** Pre-Conditions: N/A
** Post-Conditions: if at cap, print message to screen, if not at cap, 
					return the index of the destination airport, and
					return -1 if else
*********************************************************************/ 
int Manager::check_dest_cap(int curr, int flight) {
	string des = a_arr[curr].get_flight_des(flight);

	/*checks if the destination is at capacity, if not return index of
	 destination airport, else -1*/
	for (int i = 0; i < num_airports; i++) {
		if (des == a_arr[i].get_name()) {
			if(a_arr[i].get_cap() == a_arr[i].get_num_flights()) {
				cout << "Destination airport full, cannot take off." << endl;
				cout << endl;
				return -1;
			}
			return i;
		}
	}

	return -1;
}

/*********************************************************************
** Function: check_valid_airport()
** Description: checks if an airport exists in the manager database
** Parameters: string - name of airport
** Pre-Conditions: airport array has been initialized
** Post-Conditions: returns 0 if the airport is valid and 1 otherwise
*********************************************************************/ 
int Manager::check_valid_airport(string airport) {
	for(int i = 0; i < num_airports; i++) {
		if (a_arr[i].get_name() == airport) {
			return 0;
		}
	}

	return 1;
}

/*********************************************************************
** Function: update_file()
** Description: updates the airport file to the newest version after
				manipulations done in the program
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: original airport file is updated with current info
*********************************************************************/ 
void Manager::update_file() {
	ofstream fout("airport.txt", ios::trunc);

	fout << num_airports << endl;

	/*prints all airports to file*/
	for (int i = 0; i < num_airports; i++) {
		fout << a_arr[i].get_name() << " ";
		fout << a_arr[i].get_num_flights() << " ";
		fout << a_arr[i].get_cap() << endl;

		for (int j = 0; j < a_arr[i].get_num_flights(); j++) {
			a_arr[i].print_flight_to_file(j, fout);
		}
	}



}

/*********************************************************************
** Function: print_all()
** Description: prints all airport and flight information to screen
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: all airport and flight information is printed to screen
*********************************************************************/ 
void Manager::print_all(){
	/*prints every airport*/
	for (int i = 0; i < num_airports; i++) {
		a_arr[i].print_airport();
		cout << endl;
	}
	
	return; 
}

/*********************************************************************
** Function: check_flight_control()
** Description: prints a flight's information based on a user-inputted
				flight number
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: Flight with desired flight number is printed to screen
*********************************************************************/ 
void Manager::check_flight_control() {
	//Your code goes here:
	string search_num;

	cout << "Enter the flight number: ";
	cin >> search_num;

	cout << endl;

	/*checks each airport for the flight*/
	for(int i = 0; i < num_airports; i++) {
		int con = a_arr[i].search_flight_num(search_num);

		/*if flight is found, con should be 1*/
		if (con == 1) {
			return;
		}
	}

	cout << "Flight not found." << endl;
	cout << endl;

	return; 
}

/*********************************************************************
** Function: add_flight_control()
** Description: adds a flight to a desired airport if it is not at capacity
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: Flight is added to the end of the airport's flight array
*********************************************************************/ 
void Manager::add_flight_control() {

	int airport = Manager::collect_airport_choice();
	
	/*check if the destination airport is full*/
	if (a_arr[airport].get_num_flights() == a_arr[airport].get_cap()){
		cout << "Airport full, cannot add flight."<< endl;
		return;
	}

	string f_num;
	string des;
	int num_p;
	string* p;

	/*set all variables to user input*/
	p = Manager::collect_flight_info(f_num, des, num_p);

	Flight f = Flight(f_num, a_arr[airport].get_name(), des, num_p, p);

	a_arr[airport].add_a_flight(f);

	/*delete memory from placeholder array*/
	delete [] p;
	p = nullptr;

	cout << endl;
	cout << "Flight added!" << endl;
	cout << endl;
	return;
}

/*********************************************************************
** Function: cancel_flight_control()
** Description: cancels a flight at a desired airport
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: Flight is removed from the airport's flight array
*********************************************************************/ 
void Manager::cancel_flight_control() {

	int flight;
	int airport = Manager::collect_airport_choice();

	cout << endl;

	a_arr[airport].print_airport();

	cout << "Choose a flight: ";
	cin >> flight;

	/*if flight isn't found print error message*/
	if (flight < 1 || flight > a_arr[airport].get_num_flights()) {
		cout << endl;
		cout << "Flight not found, cannot remove." << endl;
		cout << endl;
		return;
	}

	/*decrement flight input from user to get index*/
	flight--;

	Flight removed = a_arr[airport].remove_a_flight(flight);

	cout << "the following flight has been cancelled:" << endl;
	cout << "----------------------" << endl; 
	removed.print_flight();
	cout << "----------------------" << endl;
	cout << endl;
	
	return;
}

/*********************************************************************
** Function: take_off_control()
** Description: takes a flight off from an airport as long as the flight
				exists and the destination is not at capacity
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: Flight is removed from current airport and added
					to the destination airport
*********************************************************************/
void Manager::take_off_control() {
	//Your code goes here:
	int flight;
	int curr = Manager::collect_airport_choice();

	cout << endl;

	a_arr[curr].print_airport();

	cout << "Choose a flight: ";
	cin >> flight;

	/*check if flight exists, if not print error message*/
	if (flight < 1 || flight > a_arr[curr].get_num_flights()) {
		cout << endl;
		cout << "Flight not found, cannot remove." << endl;
		cout << endl;
		return;
	}

	/*decrement flight input from user to get index*/
	flight--;

	int dest = Manager::check_dest_cap(curr, flight);

	/*if destination is at capacity, quit*/
	if (dest == -1) {
		return;
	}

	Flight take_off = a_arr[curr].remove_a_flight(flight);

	cout << "The following flight has taken off: " << endl;
	cout << "----------------------" << endl;
	take_off.print_flight();
	cout << "----------------------" << endl;
	cout << endl;

	/*change the current location of the flight that has taken off*/
	take_off.set_curr_loc(a_arr[dest].get_name());

	/*add the flight to destination airport*/
	a_arr[dest].add_a_flight(take_off);
	
	return; 
}

/*********************************************************************
** Function: stats_control()
** Description: prints all airport's capacity and the number of flights
				that have the airport listed as a destination
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: information is printed to screen
*********************************************************************/
void Manager::stats_control() {

	for (int i = 0; i < num_airports; i++) {
		cout << endl;
		cout << "Airport " << a_arr[i].get_name() << endl;
		cout << "capacity: " << a_arr[i].get_cap() << endl;

		int flights = 0;
		
		/*check all airports for flights with airport as destination*/
		for (int j = 0; j < num_airports; j++) {
			flights += a_arr[j].flights_with_dest(a_arr[i].get_name());
		}

		cout << "listed as destination: " << flights << " flights" << endl;
		cout << endl;
	}

	
	return; 
}

/*********************************************************************
** Function: choice_loop()
** Description: loop that runs as long as the user does not want to quit
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: all information is changed and saved
*********************************************************************/
void Manager::choice_loop() {
	int choice = -1;
	while (choice != 7)
	{
		choice = Manager::get_menu_choice();

		//print all
		if (choice == 1) 
			Manager::print_all();

		//flight info
		else if (choice == 2){
			Manager::check_flight_control();
		}
		//add a new flight
		else if (choice == 3) {
			Manager::add_flight_control();
		}
		//cancel a flight
		else if (choice == 4) {
			Manager::cancel_flight_control();
		}
		//take off a flight
		if (choice == 5){
			Manager::take_off_control();
		}
		//airport stats
		else if (choice == 6) {
			Manager::stats_control();
		}
	}
}

/*********************************************************************
** Function: run()
** Description: runs the program and updates file when over
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: all information is updated in the original airport
					file
*********************************************************************/
void Manager::run() {
	cout << endl;
	cout << "Welcome to Flight Manager!!" << endl;

	/*opens file and populates all variables*/
	if (Manager::init() != 1) {
		return;
	}

	/*runs choice loop*/
	Manager::choice_loop();
	
	cout << "Bye!" << endl << endl;

	/*updates the file after the user is done*/
	Manager::update_file();

	return;
}