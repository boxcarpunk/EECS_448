#pragma once
#include "Events.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <ctime>
#include <sstream>

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
	*	Gets the name of the current user
	*	@pre None
	*	@post None
	*	@param None
	*	@return A string representing the name of the current user
	*/
	std::string getCurrentUser() const;

	/**
	*	Creates an event and adds it to the event list
	*	@pre None
	*	@post An event is added to the list of events
	*	@param Two strings representing the name of the event and the admin, an int representing the number of days, and a vector of dates for the event
	*	@return The newly created event
	*/
	Events& addEvent(std::string eventName, std::string adminName, int numOfDays, std::vector<std::string> dates);

	/**
	*	Returns the list of events
	*	@pre None
	*	@post None
	*	@param None
	*	@return The vector list of events
	*/
	std::vector<Events> getEventList() const;

	/**
	* Checks if the date is valid or not
	*	@pre None
	*	@post None
	*	@param Integer values representing the year, month and day are taken in
	*	@return True if the date is valid. False if the date is invalid.
	*/
	bool dateCheck(int y, int m, int d);

	std::vector<std::string> split(std::string baseString, char splitChar);

private:
	std::vector<Events> m_eventList; /**< List which holds the event objects */
	std::string m_currentUser; /**< The name of the current user */
};
