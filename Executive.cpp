/**
* @author Leon Kleyn
* @cal448
* @date 10 February 2017
* @brief Executive class implementation
* @file Executive.cpp **/

#include "Executive.h"
#include "Events.h"
#include "LinkedList.h"
#include <algorithm>
#include <string>

Executive::Executive()
{
	inFile.open("eventslist.txt");
	eventList = new LinkedList<Events>();
	while(inFile)
	{
		std::getline(inFile, m_name, ',');
		if (inFile.eof()) break;
		std::getline(inFile, m_month, ',');
		std::getline(inFile, m_day, ',');
		std::getline(inFile, m_year, ',');		//Creating list of events from "storage"
		Events event(m_name, stoi(m_month), stoi(m_day), stoi(m_year));
		/*while (inFile.peek() == "'");
		{
			std::getline(inFile, m_time, ',');
			std::getline(inFile, m_attNum, ',');
			event.addTimeSlots(m_time, m_attNum);
		}	*/
		eventList->addBack(event);
		eventList -> sortListEvent();
	}
}

Executive::~Executive()
{

}

void Executive::run()
{
	bool programStatus = true;
	std::string admin = "unspecified";


	std::cout << "\nWelcome to Cal448! ";
	while (programStatus == true)			//main program loop condition
	{
		std::cout << "Are you the admin or a user? ";
		std::cin >> admin;
		std::transform (admin.begin(), admin.end(), admin.begin(), ::tolower);
		if (admin == "admin")		//runs if admin logs in
		{
			programStatus = adminFunc();
		}
		else if (admin == "user")			//runs if user logs in
		{
			programStatus = userFunc();
		}
		else																//unrecognized input
		{
			std::cout << "\nYour input was not recognized.\n\n";
		}
	}
	std::cout << "\n\nThank you for using Cal448! Goodbye!\n";
}

bool Executive::adminFunc()
{
	int adminChoice = 0;
	while (1)
	{
		std::cout << "\nCurrently logged in as an admin... How would you like to proceed?\n\n";
		std::cout << "1) Add an event\n2) Print all events\n3) Find a specific event\n4) Quit\n\nChoice: ";
		std::cin >> adminChoice;
		if (adminChoice == 1)
		{
			if (addEvent() == true)
			{
				std::cout << "\nYour event has been added!\n";
			}
		}
		else if (adminChoice == 2)
		{
			printEvents();
		}
		else if (adminChoice == 3)
		{
			std::cout << "\nYou have chosen to find a specific event\n";
		}
		else if (adminChoice == 4)
		{
			return false;
		}
		else
		{
			std::cout << "\nPlease enter a valid choice\n";
		}
	}
	return true;
}

bool Executive::userFunc()
{
	int userChoice = 0;
	while(1)
	{
		std::cout << "\nCurrently logged in as user... How would you like to proceed?\n";
		std::cout << "1) Print all events\n2) Find a specific event\n3) Quit\n\nChoice: ";
		std::cin >> userChoice;

		if (userChoice == 1)
		{
			printEvents();
		}
		else if (userChoice == 2)
		{
			std::cout << "\nYou have chosen to find a specific event\n";

		}
		else if (userChoice == 3)
		{
			return false;
		}
		else
		{
			std::cout << "\nPlease enter a valid choice\n";
		}
	}
	return true;
}

bool Executive::addEvent()
{
	std::cout << "\nWhat is the name of your event?\n";
	std::cin.ignore();
	std::getline (std::cin, m_name);
	std::cout << "\nWhat year will your event take place?\n";
	std::cin >> m_year;
	std::cout << "\nWhat month will your event take place?\n";
	std::cin >> m_month;
	if (m_month.length() > 2)		
	{
		m_month = monthConv(m_month);								//Converts month string of letters to string of ints to be used in other functions
	}
	else if (m_month.at(1) == 0)
	{
		m_month = m_month.at(1);									//Converts single 0x inputs to single integers
	}
	std::cout << "\nWhat day will your event take place?\n";
	std::cin >> m_day;
	std::cout << "\nWhat time will your event start?\n";
	std::cin >> m_stime;
	std::cout << "\nWhat time will your event end?\n";
	std::cin >> m_etime;
	Events event(m_name, stoi(m_month), stoi(m_day), stoi(m_year));
	for (int i = stoi(m_stime); i <= stoi(m_etime); i += 20)
	{
		event.addTimeSlots(i, stoi(m_attNum));
	}
	eventList->addBack(event);
	return true;
}

void Executive::printEvents()
{
	std::cout << "Number of events currently planned: " << eventList->getLength() << "\nEvent list:\n";
	for (int i=1; i<=eventList->getLength(); i++)
	{
		eventList->getEntry(i).getInfo();
	}
	std::cout << "\n";
}

std::string Executive::monthConv(std::string month)
{
	return month;
}

