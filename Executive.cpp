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
#include <ctime>

Executive::Executive()
{
	std::ifstream inFile; //creates the object to read from file
	std::string name = ""; //creates a placeholder variable for a name of an event
	std::string month = ""; //creates a placeholder variable for a month of an event
	std::string day = ""; //creates a placeholder variable for a day of an event
	std::string year = ""; //creates a placeholder variable for a year of an event

	inFile.open("eventslist.txt"); //opens the file
	eventList = new LinkedList<Events>(); //creates the linked list of events
	while(inFile) //while not at end of file
	{
		std::getline(inFile, name, ','); //gets the name of an event
		if (inFile.eof()) //if the end of file character was reached
		{
			break; //breaks out of the while loop
		}
		if (m_name[0] == '\n') //if the first character in the name is a new line
		{
			m_name.erase(0,1); //deletes the new line character
		}
		std::getline(inFile, month, ','); //gets the month of the event
		std::getline(inFile, day, ','); //gets the day of the event
		std::getline(inFile, year, ','); //gets the year of the event
		Events event(name, std::stoi(month), std::stoi(day), std::stoi(year)); //creates a new event with the given name, month, day, and year
		while (true) //runs infinitely
		{
			if (inFile.peek() == '.') //if the next character is a period
			{
				std::string time = ""; //creates a string to store the time
				std::string attendants = ""; //creates a string to store the attendants
				std::getline(inFile, time, ','); //gets the time
				time.erase(0,1); //deletes the first character of the time
				std::getline(inFile, attendants, ','); //gets the attendants
				event.addTimeSlots(stoi(time), stoi(attendants)); //adds the time and attendants to the event
			}
			else //if the next character is not a period
			{
				break; //break out of the while loop
			}
		}
		eventList->addBack(event); //adds the event to the back of the list
		eventList -> sortListEvent(); //sorts the list based on the event dates
	}
	inFile.close(); //close the file

}

Executive::~Executive()
{
}

void Executive::run()
{
	bool programStatus = true; //a flag to keep track of the state of the program
	int choice = 0; //an int that stores input from the user
	std::ofstream outFile; //the object used to write to file

	std::cout << "\n-------------------------\nWelcome to cal448!\n-------------------------\n\n";
	while (programStatus == true) //main program loop condition
	{
		std::cout << "Are you an admin or a user?\n  (1) Admin\n  (2) User\n  (3) Quit\n\n  Choice: ";
		std::cin >> choice; //takes in and stores the menu input
		while(std::cin.fail()) //fail bit code to recover bad input
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input, please select '1'-'3'\n";
			std::cin >> choice;
		}


		if (mode == 1) //if an admin logs in
		{
			std::cout<<"Which time mode would you like to use?\n  (1) 12-hour\n  (2) 24-hour\n\n Choice: ";
			std::cin>>choice; //takes in and stores the time input
			while(std::cin.fail()) //fail bit code to recover from bad input
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Invalid input, please select '1'-'2'\n";
				std::cin >> choice;
			}

			if(choice == 1) //if 12hr mode
			{
				std::cout << "\n--------- Admin Mode Starting ---------\n";
				programStatus = adminFunc(true); //goes into admin mode with a 12-hr format
			}
			else //if 24hr mode
			{
				std::cout << "\n--------- Admin Mode Starting ---------\n";
				programStatus = adminFunc(false); //goes into admin mode with a 24-hr format
			}
		}
		else if (mode == 2) //if a user logs in
		{
			std::cout<<"Which time mode?\n  (1) 12-hour\n  (2) 24-hour\n\n Choice: ";
			std::cin>>choice; //takes in and stores the time input
			while(std::cin.fail()) //fail bit code to recover from bad input
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Invalid input, please select '1'-'2'\n";
				std::cin >> choice;
			}
			if(timeChoice == 1) //if 12hr mode
			{
				std::cout << "\n--------- User Mode Starting ---------\n";
				programStatus = userFunc(true); //goes into user mode with a 12-hr format
			}
			else //if 24hr mode
			{
				std::cout << "\n--------- User Mode Starting ---------\n";
				programStatus = userFunc(false); //goes into user mode with a 24-hr format
			}
		}
		else if(mode == 3) //if exiting the program
		{
			std::cout << "Thank you for using cal448!\n";
			break; //breaks out of the while loop
		}
		else //if not 1-3
		{
			std::cout<<"\nInvalid input. Try again: \n";
		}
	}
	outFile.open("eventslist.txt"); //opens the file
	for (int i=1; i<=eventList->getLength(); i++) //goes through the event list
	{
		Events temp = eventList->getEntry(i); //stores an event in a temp variable
		outFile << temp.getName() << "," << temp.getMonth() << "," << temp.getDay() << "," << temp.getYear() << ","; //writes the event info to file
		if (!temp.getTimeSlots()->isEmpty()) //if there are time slots for the event
		{
			for (int j=1; j<=temp.getTimeSlots()->getLength(); j++) //goes through the time slots
			{
				outFile << "." << temp.getTimeSlots()->getEntry(j).getTimeSlot() << "," << temp.getTimeSlots()->getEntry(j).getNum() << ","; //writes the time slot info to file
			}
		}
	}
	outFile.close(); //closes the file
}

bool Executive::adminFunc(bool mode12)
{
	int adminChoice = 0; //an int that stores input from the user
	while (1) //runs infinitely
	{
		std::cout << "\nCurrently logged in as admin... How would you like to proceed?\n\n";
		std::cout << "  (1) Add an event\n  (2) Print all events\n  (3) Find a specific event\n  (4) Main Menu\n  (5) Quit\n\n  Choice: ";
		std::cin >> adminChoice; //takes in and stores the menu input
		while(std::cin.fail()) //fail bit code to recover from bad input
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input, please select '1'-'5'\n";
			std::cin >> adminChoice;
		}

		if (adminChoice == 1) //if add an event
		{
			if (addEvent(mode12)) //if the event could be added
			{
				std::cout << "\nYour event has been added!\n";
			}
			else //if the function could not add the event
			{
				std::cout << "There was an issue creating your event, please try again\n";
			}
		}
		else if (adminChoice == 2) //if print all events
		{
			printEvents(); //calls print events
		}
		else if (adminChoice == 3) //if find a specific event
		{
			std::string nameToSearch = ""; //creates a variable that stores the name of the event
			std::cout << "\nPlease enter the name of the event you would like to pull up: ";
			std::cin.ignore(); //wipes cin
			std::getline(std::cin, nameToSearch); //takes in the name of the event
			if (eventList->isFound(nameToSearch)) //if the event is in the list
			{
				std::cout << "\nThe event was found: " << nameToSearch << "\n\n"; //notifies the user that the event was found
				Events event = eventList->search(nameToSearch); //retrieves the event
				event.getInfo(); //prints the event info
				std::cout << "\nThere are " << event.getTimeSlots()->getLength() << " time slots in this event.\n"; //prints the amount of time slots for the event
				for (int i=1; i<=event.getTimeSlots()->getLength(); i++) //runs through the time slots
				{
					std::cout << "There are " << event.getTimeSlots()->getEntry(i).getNum() << " people available at " << event.getTimeSlots()->getEntry(i).getTimeSlot() << ".\n"; //prints the number of attendees at each time slot
				}
			}
			else //if the event is not in the list
			{
				std::cout << "\nThe event was not found\n"; //notify the user that the event was not found
			}
		}
		else if (adminChoice == 4) //if main menu
		{
			return true; //return true to run to go back to the main menu
		}
		else if (adminChoice == 5) //if quit
		{
			return false; //return false to run to quit the program
		}
		else //if not 1-5
		{
			std::cout << "\nPlease enter a valid choice\n";
		}
	}
}

bool Executive::userFunc(bool mode12)
{
	int userChoice = 0; //an int that stores input from the user
	while(1) //runs indefinitely
	{
		std::cout << "\nCurrently logged in as user... How would you like to proceed?\n";
		std::cout << "  (1) Print all events\n  (2) Find a specific event\n  (3) Main Menu\n  (4) Quit\n\n  Choice: ";
		std::cin >> userChoice; //takes in and stores the menu input
		while(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input, please select '1'-'4'\n";
			std::cin >> userChoice;
		}

		if (userChoice == 1) //if print all events
		{
			printEvents(); //prints the events
		}
		else if (userChoice == 2) //if find a specific event
		{
			std::string nameToSearch = ""; //creates a variable to store the name of the event
			std::cout << "\nPlease enter the name of the event you would like to pull up: ";
			std::cin.ignore(); //wipes cin
			std::getline(std::cin, nameToSearch); //takes in the name of the event
			if ((eventList->isFound(nameToSearch)) == true) //if the event is in the list
			{
				std::cout << "\nThe event was found: " << nameToSearch << "\n\n";
				std::cout <<"Would you like to attend this event?\n";
				std::cout <<"  (1) Yes\n  (2) No\n\n";
				std::cin >> userChoice; //takes in and stores the attend input
				while(std::cin.fail()) //fail bit code to recover from bad input
				{
					std::cin.clear();
					std::cin.ignore();
					std::cout << "Invalid input, please select '1'-'2'\n";
					std::cin >> userChoice;
				}

				while((userChoice != 1) && (userChoice != 2)) //while the input is not 1 or 2
				{
					std::cout <<"Not a Valid Input, Try Again....\n";
					std::cin >> userChoice; //takes in and stores the attend input
					while (std::cin.fail()) //fail bit code to recover from bad input
					{
						std::cin.clear();
						std::cin.ignore();
						std::cout << "Invalid input, please select '1'-'2'\n";
						std::cin >> userChoice;
					}

				}
				if(userChoice == 1) //if the user would like to attend the event
				{
					Events temp = eventList -> search(nameToSearch); //stores the event
					for(int i = 1; i <= temp.getTimeSlots() -> getLength(); i++) //runs through the time slots
					{
						std::cout <<"(" << i << ") " << temp.getTimeSlots() -> getEntry(i).getTimeSlot() << "\n"; //prints the time slot
						std::cout <<"Are you Available for this Time Slot?\n (1)Yes\n (2)No\n";
						std::cin >> userChoice; //takes in and stores the availability input
						while (std::cin.fail()) //fail bit code to recover from bad input
						{
							std::cin.clear();
							std::cin.ignore();
							std::cout << "Invalid input, please select '1'-'2'\n";
							std::cin >> userChoice;
						}
						while(userChoice != 1 && userChoice != 2) //while the input is not 1 or 2
						{
							std::cout <<"Invalid Input Try Again!\n";
							std::cin >> userChoice; //takes in and stores the availability input
							while (std::cin.fail()) //fail bit code to recover from bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input, please select '1'-'2'\n";
								std::cin >> userChoice;
							}
						}
						if(userChoice == 1) //if the user is available
						{
							temp.getTimeSlots() -> getEntry(i).increaseAtt(); //increases the attendees for that time slot
							std::cout <<"You have been added to the list. Thank You!\n\n";
						}
						else //if the user is not available
						{
							std::cout << "Thank You! You will not be added to the Attendee list!\n\n";
						}
					}
				}
			}
			else //if the event is not in the list
			{
				std::cout << "\nThe event was not found\n"; //notify the user that the event was not found
			}
		}
		else if (userChoice == 3) //if main menu
		{
			return true; //return true to run to keep the program running
		}
		else if (userChoice == 4) //if quit
		{
			return false; //return false to run to end the program
		}
		else //if not 1-4
		{
			std::cout << "\nPlease enter a valid choice\n";
		}
	}
}

bool Executive::addEvent(bool mode12)
{
	std::string name = ""; //creates a placeholder variable for a name of an event
	int month = 0; //creates a placeholder variable for a month of an event
	int day = 0; //creates a placeholder variable for a day of an event
	int year = 0; //creates a placeholder variable for a year of an event

	std::cout << "\nWhat is the name of your event?\n";
	std::cin.ignore(); //wipes cin
	std::getline (std::cin, name); //gets the name of the event
	while (1) //runs infinitely
	{
		std::cout << "\nWhat year will your event take place?\n";
		std::cin >> year; //takes in the year
		while (std::cin.fail()) //fail bit code to recover from bad input
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input, please enter a year\n";
			std::cin >> year;
		}
		std::cout << "\nWhat month will your event take place?\n";
		for(int i = 0; i < 12; i++)
		{
			std::cout<<"  ("<<i+1<<")"<<" "<<months[i]<<std::endl;
		}
		std::cin >> month; //takes in the month
		while (std::cin.fail()) //fail bit code to recover from bad input
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input, please select '1'-'12'\n";
			std::cin >> month;
		}
		std::cout << "\nWhat day will your event take place?\n";
		std::cin >> day; //takes in the day
		while (std::cin.fail()) //fail bit code to recover from bad input
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input, please enter a day\n";
			std::cin >> userChoice;
		}

		if (dateCheck(m_intYear, m_intMonth, m_intDay) == true) //if the date is valid
		{
			break; //break out of the while loop
		}
		else //if the date is invalid
		{
			std::cout << "\nThis date is invalid, please enter a valid date\n"; //notify the user that the date is invalid
		}
	}

	if(mode12) //if 12-hr mode
	{
		std::cout << "\nWhat time will your event start? \n";

		int hourMin = 0; //an int that stores the time of the event
		std::string AMPM = ""; //a string that stores whether the time is am or pm

		std::cout<<"Start Time (format like 1000 for 10:00): ";
		std::cin>>hourMin; //takes in and stores starting the time
		while (std::cin.fail()) //fail bit code to recover from bad input
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input, please enter a time\n";
			std::cin >> hourMin;
		}

		std::cout<<"\nIs this AM or PM (enter AM or PM): ";
		std::cin>>AMPM; //takes in whether the time is am or pm

		if(AMPM == "PM") //if the time is pm
		{
			hourMin = hourMin + 1200; //add 12 hours to the time
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
		while(std::stoi(m_stime) >= 2359 || std::stoi(m_stime) < 500 || (std::stoi(m_stime) >= 1201 && std::stoi(m_stime) <= 1259))
		{
			std::cout <<"Invalid Time input! Try Again!\n";
			std::cin >> m_stime;
		}
		std::cout << "\nWhat time will your event end?\n";
		std::cin >> m_etime;
		while(std::stoi(m_etime) >= 2359 || std::stoi(m_etime) < 500 || (std::stoi(m_etime) >= 1201 && std::stoi(m_etime) <= 1259))
		{
			std::cout <<"Invalid Time input! Try Again!\n";
			std::cin >> m_etime;
		}
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
}

bool Executive::dateCheck(int y, int m, int d)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int curY = (1900 + ltm->tm_year);
	if(y < curY)
	{
		std::cout <<"The year needs to be this year or later, you cannot create a past event!\n";
		return false;
		if(m <= ltm -> tm_mon)
		{
			std::cout <<"The month needs to be this month or later, you cannot create a past event!\n";
			return false;
			if(d <= ltm->tm_mday)
			{
				std::cout <<"The day needs to be this day or later, you cannot create a past event!\n";
				return false;
			}
		}

	}
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
