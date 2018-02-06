//EECS448 Project 1 Kleyn
#include "Executive.h"
#include "Events.h"
#include "LinkedList.h"

Executive::Executive()
{
	inFile.open("eventslist.txt");
	std::string name = "";
	std::string month = "";
	std::string day = "";
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
		std::getline(inFile, year, ',');
		std::getline(inFile, s_time, ',');
		std::getline(inFile, e_time, ',');
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
	int length = eventList->getLength();

	while (program_status == true)			//main program loop condition
	{
		std::cout << "\nWelcome to Cal448! Are you the admin or the user? ";
		std::cin >> admin;
		if (admin == "user" || admin == "USER" || admin == "User")			//runs if user logs in
		{
			std::cout << "You have specified that you are a user\nNumber of events currently planned: " << length << "\n\nEvent list:\n";
			for (int i=0; i<length; i++)
			{
				eventList->getEntry(i).getInfo();
			}
				
		}
		else if (admin == "admin" || admin == "ADMIN" || admin == "Admin")		//runs if admin logs in
		{
			std::cout << "You have specified that you are an admin\n\n";
		}
	}
}
