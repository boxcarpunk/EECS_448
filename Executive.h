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

	std::vector<std::string> split(std::string mainString, char seperatingChar);

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
	*	Wasn't included in documentation
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
	void printEvents();

	/**
	*	Wasn't included in documentation
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
	bool dateCheck(int y, int m, int d);

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
