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
		Events event(name, month, day, year, s_time, e_time);
		eventList->addBack(event);
	}

}

Executive::~Executive()
{

}

void Executive::run()
{
	bool program_status = true;			
	std::string admin = "unspecified";
	listLength = eventList->getLength();


	std::cout << "\nWelcome to Cal448! ";
	while (program_status == true)			//main program loop condition
	{
		std::cout << "Are you the admin or the user? ";
		std::cin >> admin;
		if (admin == "user" || admin == "USER" || admin == "User")			//runs if user logs in
		{
			userFunc();
		}
		else if (admin == "admin" || admin == "ADMIN" || admin == "Admin")		//runs if admin logs in
		{
			adminFunc();
		}
		else
		{
			std::cout << "\nYour input was not recognized.\n\n";
		}
	}
}
void Executive::adminFunc()
{
	std::cout << "\nYou have specified that you are an admin\n\n";	
}

void Executive::userFunc()
{
	std::cout << "\nYou have specified that you are a user\n\nHow would you like to proceed?";
	std::cout << "Number of events currently planned: " << listLength << "\n\nEvent list:\n";
	for (int i=1; i<=listLength; i++)
	{
		eventList->getEntry(i).getInfo();
	}
	std::cout << "\n";
}
