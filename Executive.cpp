//EECS448 Project 1 Kleyn
#include "Executive.h"
#include "Events.h"
#include "LinkedList.h"

Executive::Executive()
{
	inFile.open("eventslist.txt");
	std::string name = "";
	std::string month = "";
	std::string day = "";										//Event variables
	std::string year = "";
	std::string s_time = "";
	std::string e_time = "";
	eventList = new LinkedList<Events>();
while(1>0)
	{
		std::getline(inFile, name, ',');
		if (inFile.eof()) break;
		std::getline(inFile, month, ',');
		std::getline(inFile, day, ',');
		std::getline(inFile, year, ',');							//Creating list of events from "storage"
		std::getline(inFile, s_time, ',');
		std::getline(inFile, e_time);
		Events event(name, stoi(month), stoi(day), stoi(year), stoi(s_time), stoi(e_time));
		eventList->addBack(event);
	}
}

Executive::~Executive()
{

}

void Executive::run()
{
	bool programStatus = true;			
	std::string admin = "unspecified";
	listLength = eventList->getLength();


	std::cout << "\nWelcome to Cal448! ";
	while (programStatus == true)			//main program loop condition
	{
		std::cout << "Are you the admin or the user? ";
		std::cin >> admin;
		if (admin == "admin" || admin == "ADMIN" || admin == "Admin")		//runs if admin logs in
		{
			programStatus = adminFunc();
		}
		else if (admin == "user" || admin == "USER" || admin == "User")			//runs if user logs in
		{
			programStatus = userFunc();
		}
		else
		{
			std::cout << "\nYour input was not recognized.\n\n";
		}
	}
}

bool Executive::adminFunc()
{
	int adminChoice = 0;
	std::cout << "\nWelcome admin... How would you like to proceed?\n\n";
	std::cout << "1) Add an event\n2) Print all events\n3) Find a specific event\n4) Quit\n\nChoice: ";
	std::cin >> adminChoice;
	if (adminChoice == 1)
	{
		std::cout << "\nYou have chosen to add an event\n";
		return true;
	}
	else if (adminChoice == 2)
	{
		std::cout << "\nYou have chosen to print all events\n";
		return true;
	}
	else if (adminChoice == 3)
	{
		std::cout << "\nYou have chosen to find a specific event\n";
		return true;
	}
	else if (adminChoice == 4)
	{
		return false;
	}
	else 
	{
		std::cout << "\nPlease enter a valid choice\n";
		return true;
	}	
}

bool Executive::userFunc()
{
	std::cout << "\nYou have specified that you are a user\n\nHow would you like to proceed?\n";
	std::cout << "Number of events currently planned: " << listLength << "\nEvent list:\n";
	for (int i=1; i<=listLength; i++)
	{
		eventList->getEntry(i).getInfo();
	}
	std::cout << "\n";
	return true;
}
