/******************************************************
** Program: flight_manager.cpp
** Author: Kaelee Duong
** Date: 2/22/2024
** Description: simulates the basic functionalities of air traffic
				control systems, allowing user to interact with multiple
				flights across multiple airports
** Input: text file called airport.txt hardcoded into file,
		  integer for user's choice, flight details when
		  adding a flight
** Output: When changes are made, print details to terminal, amd
		   when the user decides to quit, update the original
		   airport file
******************************************************/

#include <iostream>
#include "manager.h"


using namespace std;

/*********************************************************************
** Function: main
** Description: runs the program
** Parameters: N/A
** Pre-Conditions: all classes and functions have been defined
** Post-Conditions: program exits smoothly
*********************************************************************/ 
int main()
{
	Manager m;
	m.run();
	return 0;

}