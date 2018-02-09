//EECS448 Project 1 Kleyn
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
		while (inFile.peek() == "'");
		{
			std::getline(inFile, m_time, ',');
			std::getline(inFile, m_attNum, ',');
			event.addTimeSlots(m_time, m_attNum);
		}	
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
	std::getline (std::cin,name);
	std::cout << "\nWhat year will your event take place?\n";
	std::cin >> year;
	std::cout << "\nWhat month will your event take place?\n";
	std::cin >> month;
	if (month.length() > 2)		
	{
		month = monthConv(month);								//Converts month string to integer
	}
	else if (month.at(1) == 0)
	{
		month = month.at(1);									//Converts single 0x inputs to single integers
	}
	std::cout << "\nWhat day will your event take place?\n";
	std::cin >> day;
	std::cout << "\nWhat time will your event start?\n";
	std::cin >> s_time;
	std::cout << "\nWhat time will your event end?\n";
	std::cin >> e_time;
	Events event(name, stoi(month), stoi(day), stoi(year));
	for (int i = s_time; i <= e_time; i += 20)
	{
		event.addTimeSlots(time, attNum);
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



