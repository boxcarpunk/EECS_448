/**
* @author Leon Kleyn
* @cal448
* @date 12 February 2017
* @brief Executive class implementation
* @file Executive.cpp
Test comment**/

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
		Events event(m_name, std::stoi(m_month), std::stoi(m_day), std::stoi(m_year));
		while (true)
		{
			if (inFile.peek() == '.')
			{
				std::string time = "";
				std::string attendants = "";
				std::getline(inFile, time, ',');
				time.erase(0,1);
				std::getline(inFile, attendants, ',');
				event.addTimeSlots(stoi(time), stoi(attendants));
			}
			else
			{
				break;
			}
		}
		event.getInfo();
		std::cout << "\n The length of timeslots is " << event.getTimeSlots()->getLength() << "\n";
		/*for (int i=1; i==event.getTimeSlots()->getLength(); i++)
		{
			std::cout << "There are " << event.getTimeSlots()->getEntry(i).getNum() << " people available at " << event.getTimeSlots()->getEntry(i).getTimeSlot() << ".\n";
		}*/
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
	int mode = 0;


	std::cout << "\n-------------------------\nWelcome to cal448!\n-------------------------\n\n";
	while (programStatus == true)			//main program loop condition
	{
		std::cout << "Are you an admin or a user?\n  (1) Admin\n  (2) User\n  (3) Quit\n\n  Choice: ";
		std::cin >> mode;
		if (mode == 1)		//runs if admin logs in
		{
			std::cout<<"\n--------- Admin Mode Starting ---------\n";
			programStatus = adminFunc();
		}
		else if (mode == 2)			//runs if user logs in
		{
			std::cout<<"\n--------- User Mode Starting ---------\n";
			programStatus = userFunc();
		}
		else if(mode == 3)															//unrecognized input
		{
			std::cout << "Thank you for using cal448!\n";
			break;
		}
		else
		{
			std::cout<<"\nInvalid input. Try again: \n";
		}
	}
}

bool Executive::adminFunc()
{
	int adminChoice = 0;
	while (1)
	{
		std::cout << "\nCurrently logged in as admin... How would you like to proceed?\n\n";
		std::cout << "(1) Add an event\n(2) Print all events\n(3) Find a specific event\n(4) Main Menu\n(5) Quit\n\n  Choice: ";
		std::cin >> adminChoice;
		if (adminChoice == 1)
		{
			if (addEvent() == true)
			{
				std::cout << "\nYour event has been added!\n";
			}
			else
			{
				std::cout << "There was an issue creating your event, please try again\n";
			}
		}
		else if (adminChoice == 2)
		{
			printEvents();
		}
		else if (adminChoice == 3)
		{
			std::string nameToSearch = "";
			std::cout << "\nPlease enter the name of the event you would like to pull up: ";
			std::cin >> nameToSearch;
			if (eventList->isFound(nameToSearch) == true)
			{
				std::cout << "\nThe event was found: " << nameToSearch << "\n";
			}
			else
			{
				std::cout << "\nThe event was not found\n";
			}
		}
		else if (adminChoice == 4)
		{
			return true;
		}
		else if (adminChoice == 5)
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
// test
bool Executive::userFunc()
{
	int userChoice = 0;
	while(1)
	{
		std::cout << "\nCurrently logged in as user... How would you like to proceed?\n";
		std::cout << "(1) Print all events\n(2) Find a specific event\n(3) Main Menu(4) Quit\n\n  Choice: ";
		std::cin >> userChoice;

		if (userChoice == 1)
		{
			printEvents();
		}
		else if (userChoice == 2)
		{
			std::string nameToSearch = "";
			std::cout << "\nPlease enter the name of the event you would like to pull up: ";
			std::cin.ignore();
			std::getline(std::cin, nameToSearch);
			if ((eventList->isFound(nameToSearch)) == true)
			{
				std::cout << "\nThe event was found: " << nameToSearch << "\n";
			}
			else
			{
				std::cout << "\nThe event was not found\n";
			}
		}
		else if (userChoice == 3)
		{
			return true;
		}
		else if (userChoice == 4)
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
	for(int i = 0; i < 12; i++) {
		std::cout<<"  ("<<i+1<<")"<<" "<<m_months[i]<<std::endl;
	}
	std::cin >> m_month;

	std::cout << "\nWhat day will your event take place?\n";
	std::cin >> m_day;
	std::cout << "\nWhat time will your event start?\n";
	std::cin >> m_stime;
	std::cout << "\nWhat time will your event end?\n";
	std::cin >> m_etime;

	m_intMonth = std::stoi(m_month);
	m_intDay = std::stoi(m_day);
	m_intYear = std::stoi(m_year);

	Events event1(m_name, m_intMonth, m_intDay, m_intYear);

	m_intSTime = stoi(m_stime);
	m_intETime = stoi(m_etime);
	int numTs = (((m_intETime - m_intSTime)/100) * 3);

	for (int i = 0; i < numTs; i ++)
	{
		event1.addTimeSlots(i, 1);
	}
	eventList->addBack(event1);
	eventList->sortListEvent();
        std::cout << "\n The length of timeslots is " << event1.getTimeSlots()->getLength() << "\n";
	event1.getInfo();
	for (int i=1; i==event1.getTimeSlots()->getLength(); i++)
	{
		std::cout << "There are " << event1.getTimeSlots()->getEntry(i).getNum() << " people available at " << event1.getTimeSlots()->getEntry(i).getTimeSlot() << ".\n";
	}

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
