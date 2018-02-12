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
	Executive(); 								//Opens a file and creates a list of events that have already been created
	~Executive();
	void run(); 								//Main run function
	void printEvents();							//Prints info on all the events in the event list

	private:
	std::ifstream inFile;
	LinkedList<Events>* eventList; 				//List which holds the event objects
	bool adminFunc(bool mode12); 							//Function which handles admin menu and options
	bool userFunc(bool mode12);							//Function which handles user menu and options
	bool addEvent(bool mode12);							//Prompts the admin to create an event and it to the list
	std::string m_name = "";                    // placeholder variable for a name of an event, to be passed to Events class as an argument
	std::string m_month = "";                   // placeholder variable for a month of an event, to be passed to Events class as an argument
	std::string m_day = "";						// placeholder variable for a day of an event, to be passed to Events class as an argument
	std::string m_year = "";                    // placeholder variable for a year of an event, to be passed to Events class as an argument

	int m_intMonth = 0;
	int m_intDay = 0;
	int m_intYear = 0;

	int m_intSTime = 0;
	int m_intETime = 0;

	std::string m_time = "";                    // placeholder variable for a time of an event, to be passed to Events class as an argument
	std::string m_attNum = "";                  // placeholder variable for an attendance number of an event, to be passed to Event class as an argument
	std::string m_stime = "";                   // variable for a start time of an event, used in for loop to determine how many time slots need to be created for an event
	std::string m_etime = "";                   // variable for a end time of an event, used in for loop to determine how many time slots need to be created for an event
	std::string m_months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
};
