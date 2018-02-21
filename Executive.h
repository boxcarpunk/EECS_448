/**
* @author Leon Kleyn
* @cal448
* @date 12 February 2017
* @brief Executive class that runs UI and implements other classes of cal448 program
* @file Executives.h **/

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
	*	Empty destructor
	*	@pre None
	*	@post None
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

	private:
	std::ifstream inFile;
	LinkedList<Events>* eventList; //List which holds the event objects

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

	int m_intSTime = 0;
	int m_intETime = 0;

	std::string m_time = ""; // placeholder variable for a time of an event, to be passed to Events class as an argument
	std::string m_attNum = ""; // placeholder variable for an attendance number of an event, to be passed to Event class as an argument
	std::string m_stime = ""; // variable for a start time of an event, used in for loop to determine how many time slots need to be created for an event
	std::string m_etime = ""; // variable for a end time of an event, used in for loop to determine how many time slots need to be created for an event
	std::string m_months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
};
