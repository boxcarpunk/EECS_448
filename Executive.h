/**
* @author Leon Kleyn
* @cal448
* @date 10 February 2017
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
	bool adminFunc(); 							//Function which handles admin menu and options
	bool userFunc();							//Function which handles user menu and options
	bool addEvent();							//Prompts the admin to create an event and it to the list
	std::string monthConv(std::string month);
	int listLength = 0;							//Length of the list of events
	std::string m_name = "";
	std::string m_month = "";
	std::string m_day = "";						//Event variables
	std::string m_year = "";
	std::string m_time = "";
	std::string m_attNum = "";
	std::string m_stime = "";
	std::string m_etime = "";

};
