//EECS448 Project 1 Kleyn
#include "Executive.h"
#include "Events.h"
#include "LinkedList.h"

Executive::Executive()
{
	infile.open(eventslist.txt)
	std::string name = "";
	std::string month = "";
	int day = 0;
	int s_time = 0;
	int e_time = 0;
	eventList = new LinkedList<Events>();
	while(1>0)
	{
		std::getline(inFile, name, ',');
		if (inFile.eof()) break;
		std::getline(inFile, month, ',');
		std::getline(inFile, day, ',');
		std::getline(inFile, s_time, ',');
		std::getline(inFile, e_time, ',');
		Events event(name, month, day, s_time, e_time);
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

	while (program_status == true)			//main program loop condition
	{
		std::cout << "\nWelcome to Cal448! Are you the admin or the user? ";
		std::cin >> admin;
		if (admin == "user" || admin == "USER" || admin == "User")			//runs if user logs in
		{
			std::cout << "You have specified that you are a user\nNumber of events currently planned: " << eventList->getLength() << "\n\n";
				
		}
		else if (admin == "admin" || admin == "ADMIN" || admin == "Admin")		//runs if admin logs in
		{
			std::cout << "You have specified that you are an admin\n\n";
		}
	}
}
