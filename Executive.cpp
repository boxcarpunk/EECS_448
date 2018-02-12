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
#include <math.h>

Executive::Executive()
{
	std::ifstream inFile;
	inFile.open("eventslist.txt");
	eventList = new LinkedList<Events>();
	while(inFile)
	{
		std::string newline = "";
		while (inFile.peek() == '\n')
		{
			std::getline(inFile, newline, ',');
		}
		std::getline(inFile, m_name, ',');
		if (inFile.eof()) break;
		if (m_name(0) == ',')
		{
			m_name.erase(0,1);
		}
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
		for (int i=1; i<=event.getTimeSlots()->getLength(); i++)
		{
			std::cout << "There are " << event.getTimeSlots()->getEntry(i).getNum() << " people available at " << event.getTimeSlots()->getEntry(i).getTimeSlot() << ".\n";
		}
		eventList->addBack(event);
		eventList -> sortListEvent();
	}
	inFile.close();

}

Executive::~Executive()
{
	
}

void Executive::run()
{
	bool programStatus = true;
	std::string admin = "unspecified";
	int mode = 0;
	std::ofstream outFile;
	int timeChoice = 0;
	bool time12 = false;


	std::cout << "\n-------------------------\nWelcome to cal448!\n-------------------------\n\n";
	while (programStatus == true)			//main program loop condition
	{
		std::cout << "Are you an admin or a user?\n  (1) Admin\n  (2) User\n  (3) Quit\n\n  Choice: ";
		std::cin >> mode;

		if (mode == 1)		//runs if admin logs in
		{
			std::cout<<"Which time mode?\n  (1) 12-hour\n  (2) 24-hour\n\n Choice: ";
			std::cin>>timeChoice;

			if(timeChoice == 1) {
				time12 = true;
			}
			else {
				time12 = false;				//in case user changes choice when going back to main menu
			}
			std::cout<<"\n--------- Admin Mode Starting ---------\n";
			programStatus = adminFunc(time12);
		}
		else if (mode == 2)			//runs if user logs in
		{
			std::cout<<"Which time mode?\n  (1) 12-hour\n  (2) 24-hour\n\n Choice: ";
			std::cin>>timeChoice;

			if(timeChoice == 1) {
				time12 = true;
			}
			else {
				time12 = false;				//in case user changes choice when going back to main menu
			}
			std::cout<<"\n--------- User Mode Starting ---------\n";
			programStatus = userFunc(time12);
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
	outFile.open("eventslist.txt");
	for (int i=1; i<=eventList->getLength(); i++)
	{
		Events temp = eventList->getEntry(i);
		outFile << "\n," << temp.getName() << "," << temp.getMonth() << "," << temp.getDay() << "," << temp.getYear() << ",";
		if (!temp.getTimeSlots()->isEmpty())
		{
			for (int j=1; j<=temp.getTimeSlots()->getLength(); j++)
			{
				outFile << "." << temp.getTimeSlots()->getEntry(j).getTimeSlot() << "," << temp.getTimeSlots()->getEntry(j).getNum() << ",";
			}
		}
	}
	outFile.close();
}

bool Executive::adminFunc(bool mode12)
{
	int adminChoice = 0;
	while (1)
	{
		std::cout << "\nCurrently logged in as admin... How would you like to proceed?\n\n";
		std::cout << "(1) Add an event\n(2) Print all events\n(3) Find a specific event\n(4) Main Menu\n(5) Quit\n\n  Choice: ";
		std::cin >> adminChoice;
		if (adminChoice == 1)
		{
			if (addEvent(mode12) == true)
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
			std::cin.ignore();
			std::getline(std::cin, nameToSearch);
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
bool Executive::userFunc(bool mode12)
{
	int userChoice = 0;
	while(1)
	{
		std::cout << "\nCurrently logged in as user... How would you like to proceed?\n";
		std::cout << "(1) Print all events\n(2) Find a specific event\n(3) Main Menu\n(4) Quit\n\n  Choice: ";
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
				int attChoice = 0;
				std::cout << "\nThe event was found: " << nameToSearch << "\n";
				std::cout <<"Would you like to attend this event?\n";
				std::cout <<"(1) Yes\n(2) No\n\n";
				std::cin >> attChoice;
				while(attChoice != 1 && attChoice != 2)
				{
					std::cout <<"Not a Valid Input, Try Again....\n";
					std::cin >> attChoice;
				}
				if(attChoice == 1)
				{
					std::cout <<"Which Time Slots are you available for?\n";
					Events temp = eventList -> search(nameToSearch);
					for(int i = 1; i <= temp.getTimeSlots() -> getLength(); i++)
					{
						std::cout <<"(" << i << ") " << temp.getTimeSlots() -> getEntry(i).getTimeSlot() << "\n";
					}
					std::string userStart;
					std::string userEnd;
					std::cout <<"Insert the first number next to the time for which you are available: ";
					std::cin >> userStart;
					std::cout <<"Insert the last number next to the time for which you stop being available: ";
					std::cin >> userEnd;
					int userStart1 = std::stoi(userStart);
					int userEnd1 = std::stoi(userEnd);
					for (int i = userStart1; i <= userEnd1; i ++)
					{
						temp.getTimeSlots() -> getEntry(i).increaseAtt();
					}
					std::cout <<"You have been added to the list. Thank You!\n\n";
				}
				else{
					std::cout << "Thank You! You will not be added to the Attendee list!\n\n";
				}
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

bool Executive::addEvent(bool mode12)
{
	std::cout << "\nWhat is the name of your event?\n";
	std::cin.ignore();
	std::getline (std::cin, m_name);
	while (1)
	{
		std::cout << "\nWhat year will your event take place?\n";
		std::cin >> m_year;
		std::cout << "\nWhat month will your event take place?\n";
		for(int i = 0; i < 12; i++) {
			std::cout<<"  ("<<i+1<<")"<<" "<<m_months[i]<<std::endl;
		}
		std::cin >> m_month;
		std::cout << "\nWhat day will your event take place?\n";
		std::cin >> m_day;
		m_intMonth = std::stoi(m_month);
		m_intDay = std::stoi(m_day);
		m_intYear = std::stoi(m_year);

		if (dateCheck(m_intYear, m_intMonth, m_intDay) == true)
		{
			break;
		}
		else
		{
			std::cout << "\nThis date is invalid, please enter a valid date\n";
		}
	}

	if(mode12) {
		std::cout << "\nWhat time will your event start? \n";

		int hourMin = 0;
		std::string AMPM = "";

		std::cout<<"Start Time (format like 1000 for 10:00): ";
		std::cin>>hourMin;

		std::cout<<"\nIs this AM or PM (enter AM or PM): ";
		std::cin>>AMPM;

		if(AMPM == "PM") {
			hourMin = hourMin + 1200;
		}

		m_stime = std::to_string(hourMin);

		std::cout<<"\nEnd Time (format like 1000 for 10:00): ";
		std::cin>>hourMin;

		std::cout<<"\nIs this AM or PM (enter AM or PM): ";
		std::cin>>AMPM;

		if(AMPM == "PM") {
			hourMin = hourMin + 1200;
		}

		m_etime = std::to_string(hourMin);
	} else {
		std::cout << "\nWhat time will your event start?\n";
		std::cin >> m_stime;
		std::cout << "\nWhat time will your event end?\n";
		std::cin >> m_etime;
	}

	Events event1(m_name, m_intMonth, m_intDay, m_intYear);

	m_intSTime = stoi(m_stime);
	m_intETime = stoi(m_etime);
	double numTs = ceil(((std::stod(m_etime) - std::stod(m_stime))/100) * 3);
	std::cout << numTs << "\n";
	int tsup = ceil(m_intSTime);
	for (int i = 0; i < numTs; i ++)
	{
		if(tsup % 100 == 60)
		{
			tsup = tsup + 40;
		}
		event1.addTimeSlots(tsup, 1);
		tsup += 20;

	}
	eventList->addBack(event1);
	eventList->sortListEvent();
        std::cout << "\n The length of timeslots is " << event1.getTimeSlots()->getLength() << "\n";
	event1.getInfo();
	for (int i=1; i <= event1.getTimeSlots()->getLength(); i++)
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

bool Executive::dateCheck(int y, int m, int d)
{
	if (d < 1)
	{
		std::cout << "\nThe day must be 1 or higher.\n";
		return false;
	}
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		if (d > 31)
		{
			std::cout << "\nYou have selected a day outside the range of this month.\n";
			return false;
		}
	}
	else if (m == 4 || m == 6 || m == 9 || m == 11)
	{
		if (d > 30)
		{
			std::cout << "\nYou have selected a day outside the range of this month.\n";
			return false;
		}
	}
	else if (m == 2)
	{
		if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))			//Leep year conditions: cite "crazzyguy101 - cplusplus.com"
		{
			if (d > 29)
			{
				std::cout << "\nYou have selected a day outside the range of this month.\n";
				return false;
			}
		}
		else
		{
			if (d > 28)
			{
				std::cout << "\nYou have selected a day outside the range of this month.\n";
				return false;
			}
		}
	}
	return true;
}
