#pragma once
#include "LinkedList.h"
#include "Events.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <math.h>
#include <ctime>
#include <cctype>

class Executive
{
	public:
	/**
	*	The list of events is populated from a file and the member variables are initialized or set up to be used
	*	@pre None
	*	@post Private member variables are set and the list of events is populated
	*	@param None
	*	@return None
	*/
	Executive();

	/**
	*	Empty destructor
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
	~Executive();

	/**
	*	Splits the string passed in based on the delimiting character also passed in
	*	@pre None
	*	@post The string is split at the delimiting character
	*	@param The string to be split and the delimiting character
	*	@return A vector containing the parts of the string
	*/
	std::vector<std::string> split(std::string mainString, char seperatingChar);

	/**
	*	Checks if the length of the name passed in is between zero and the value passed in
	*	@pre None
	*	@post None
	*	@param The name to be checked and the size it cannot be longer than
	*	@return True if the name is of a valid length, false otherwise
	*/
	bool validEventName(std::string name, int value);


	/**
	*	The program begins and the user can interact with it
	*	@pre None
	*	@post Program begins
	*	@param None
	*	@return None
	*/
	void run();

	/**
	*	Prints all the events in the event list
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
	void printEvents();

	/**
	*	Checks the validity of the date passed in
	*	@pre None
	*	@post None
	*	@param Integers representing the day, month, and year of a potential event
	*	@return True is the date is valid, false otherwise
	*/
	bool dateCheck(int y, int m, int d);

	/**
	*	Adds the user's availability to the event passed in
	*	@pre None
	*	@post The user's availability is added to the event
	*	@param The event to add availability to
	*	@return None
	*/
	void AddAvailability(Events event);


	private:
	LinkedList<Events, std::string>* eventList; /**< List which holds the event objects */
	int timeMode; /**< Set to indicate whether the program should run in 12 or 24 hr mode */
	std::string currentUser = ""; /**< String containing the name of the current user */
	const std::string fileName; /**< The name of the file to be read from/written to */

	/**
	*	The program initializes the admin mode
	*	@pre None
	*	@post Admin mode begins
	*	@param Boolean checking whether the user has selected 12 or 24 hour mode
	*	@return Wasn't included in documentation
	*/
	bool adminFunc(bool mode12);

	/**
	*	The program initializes the user mode
	*	@pre None
	*	@post User mode begins
	*	@param Boolean checking whether the user has selected 12 or 24 hour mode
	*	@return Wasn't included in documentation
	*/
	bool userFunc(bool mode12);

	/**
	*	The program allows the user to add an event
	*	@pre None
	*	@post An event is added to the list of events
	*	@param Boolean checking whether the user has selected 12 or 24 hour mode
	*	@return Wasn't included in documentation
	*/
	bool addEvent(bool mode12);
};
