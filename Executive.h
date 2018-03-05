#pragma once
#include "LinkedList.h"
#include "Events.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <ctime>

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
	*	Sets the name of the current user of the program
	*	@pre None
	*	@post The name of the current user is set to the name passed in
	*	@param A string representing the name of the current user
	*	@return None
	*/
	void setCurrentUser(std::string name);

	/**
	*	Creates an event and adds it to the event list
	*	@pre None
	*	@post An event is added to the list of events
	*	@param A string representing the name, an int representing the number of days, and a vector of dates for the event
	*	@return True if the event could be added, false otherwise
	*/
	bool addEvent(std::string name, int numOfDays, std::vector<std::string> dates);

	/**
	*	Returns the list of events
	*	@pre None
	*	@post None
	*	@param None
	*	@return The list of events
	*/
	std::vector<Events> getEventList();

	/**
	*	Wasn't included in documentation
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
	bool dateCheck(int y, int m, int d);

private:
	LinkedList<Events, std::string>* eventList; /**< List which holds the event objects */
<<<<<<< HEAD

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

	/**
	* The program checks inputs to be greater than 0 and less than the value given to it
	* @pre None
	* @post None
	* @param String name of the event and the int value is the greatest amount of characters the event name can have
	* @return returns true if a valid name and false if invalid name
	*/
	bool validEventName(std::string name, unsigned int value);
	std::vector<std::string> split(std::string mainString, char seperatingChar);

	int m_intSTime = 0;
	int m_intETime = 0;

	std::string m_time = ""; // placeholder variable for a time of an event, to be passed to Events class as an argument
	std::string m_attNum = ""; // placeholder variable for an attendance number of an event, to be passed to Event class as an argument
	std::string m_stime = ""; // variable for a start time of an event, used in for loop to determine how many time slots need to be created for an event
	std::string m_etime = ""; // variable for a end time of an event, used in for loop to determine how many time slots need to be created for an event
	std::string m_months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	const std::string holidays[3] = { "01/01", "07/4","12/25" };

=======
	std::string m_currentUser; /**< The name of the current user */
>>>>>>> Event/Availability
};
