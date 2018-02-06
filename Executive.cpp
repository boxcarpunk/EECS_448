//EECS448 Project 1 Kleyn
#include "Executive.h"
#include "Events.h"
#include "LinkedList.h"

Executive::Executive()
{
	
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
			std::cout << "You have specified that you are a user\n\n";	
		}
		else if (admin == "admin" || admin == "ADMIN" || admin == "Admin")		//runs if admin logs in
		{
			std::cout << "You have specified that you are an admin\n\n";
		}
	}
}
