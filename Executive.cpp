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
		std::cout << name << " name **** 1\n";
		std::getline(inFile, month, ',');
		std::cout << month << " month **** 1\n";
		std::getline(inFile, day, ',');
		std::cout << day << " day **** 1\n";
		std::getline(inFile, year, ',');
		std::cout << year << " year **** 1\n";
		std::getline(inFile, s_time, ',');
		std::cout << s_time << " s time **** 1\n";
		std::getline(inFile, e_time);
		std::cout << e_time << " e time**** 1\n";
		Events event(name, month, day, year, s_time, e_time);
		eventList->addFront(event);
		std::cout << "Front of list : "; eventList->getEntry(1).getInfo(); std::cout << "\n";
	}
	std::cout << "\n*********Test Output************\n";
	std::cout << "Front of list : "; eventList->getEntry(1).getInfo(); std::cout << "\n";
	std::cout << "Second of list : "; eventList->getEntry(2).getInfo(); std::cout << "\n";
	std::cout << "Third of list : "; eventList->getEntry(3).getInfo(); std::cout << "\n";
	std::cout << "Last of list : "; eventList->getEntry(4).getInfo(); std::cout << "\n";
	std::cout << "\n*********Test Output************\n";		
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
			/*Events event("Third test", "October", "31", "2019", "1300", "1320");
			eventList->addFront(event);
			std::cout << "\nTest length: " << length << "\n";
			eventList->getEntry(0).getInfo();
			eventList->getEntry(1).getInfo();
			eventList->getEntry(2).getInfo();*/	
			for (int i=1; i<=length; i++)
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
