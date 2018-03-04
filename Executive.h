#pragma once
#include "LinkedList.h"
#include "Events.h"
#include <fstream>
#include <vector>
#include <iostream>

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
	*	Writes the program information to file in order to save it
	*	@pre None
	*	@post The object is destroyed and the info is stored in a file called "eventslist.txt"
	*	@param None
	*	@return None
	*/
	~Executive();

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

	/**
	*	Wasn't included in documentation
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
	void AddAvailability(Events event);

	/**
	*	Sets the name of the current user of the program
	*	@pre None
	*	@post The name of the current user is set to the name passed in
	*	@param A string representing the name of the current user
	*	@return None
	*/
	void setCurrentUser(std::string name);

private:
	LinkedList<Events, std::string>* eventList; /**< List which holds the event objects */
	std::string m_attNum = ""; /**< placeholder variable for an attendance number of an event, to be passed to Event class as an argument */
	std::string m_months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" }; /**< Variable Description */
	std::string m_currentUser = ""; /**< The name of the current user */

	//std::vector<Events> eventList;

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


	int timeMode;

	/**
	* The program checks inputs to be greater than 0 and less than the value given to it
	* @pre None
	* @post None
	* @param String name of the event and the int value is the greatest amount of characters the event name can have
	* @return returns true if a valid name and false if invalid name
	*/
	bool validEventName(std::string name, unsigned int value);
};
