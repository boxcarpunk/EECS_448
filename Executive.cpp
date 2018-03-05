#include "Executive.h"

Executive::Executive()
{
	std::ifstream inFile; //creates the object to read from file
	std::string name = ""; //creates a placeholder variable for a name of an event
	std::string month = ""; //creates a placeholder variable for a month of an event
	std::string day = ""; //creates a placeholder variable for a day of an event
	std::string year = ""; //creates a placeholder variable for a year of an event

	inFile.open("eventslist.txt"); //opens the file
	eventList = new LinkedList<Events, std::string>(); //creates the linked list of events
	while(inFile) //while not at end of file
	{
		std::getline(inFile, name, ','); //gets the name of an event
		if (inFile.eof()) //if the end of file character was reached
		{
			break; //breaks out of the while loop
		}
		if (name[0] == '\n') //if the first character in the name is a new line
		{
			name.erase(0,1); //deletes the new line character
		}
		std::getline(inFile, month, ','); //gets the month of the event
		std::getline(inFile, day, ','); //gets the day of the event
		std::getline(inFile, year, ','); //gets the year of the event
		std::string strMonth, strDay, strYear;
		strMonth = month;
		strDay = day;
		strYear = year;
		//TODO: Add numOfDays to constructor
		Events event(name,  0, 0); //creates a new event with the given name, month, day, and year
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
		eventList -> sort(); //sorts the list
	}
	inFile.close(); //close the file

}

Executive::~Executive()
{
<<<<<<< HEAD
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


		if (choice == 1) //if an admin logs in
		{
			std::cout<<"Which time mode would you like to use?\n  (1) 12-hour\n  (2) 24-hour\n\n Choice: ";
			std::cin.ignore(); //wipes cin
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
		else if (choice == 2) //if a user logs in
		{
			std::cout<<"Which time mode?\n  (1) 12-hour\n  (2) 24-hour\n\n Choice: ";
			std::cin.ignore(); //wipes cin
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
				std::cout << "\n--------- User Mode Starting ---------\n";
				programStatus = userFunc(true); //goes into user mode with a 12-hr format
			}
			else //if 24hr mode
			{
				std::cout << "\n--------- User Mode Starting ---------\n";
				programStatus = userFunc(false); //goes into user mode with a 24-hr format
			}
		}
		else if(choice == 3) //if exiting the program
		{
			std::cout << "Thank you for using cal448!\n";
			break; //breaks out of the while loop
		}
		else //if not 1-3
		{
			std::cout<<"\nInvalid input. Try again: \n";
		}
	}
=======
>>>>>>> Event/Availability
	outFile.open("eventslist.txt"); //opens the file
	for (int i = 1; i <= eventList->getLength(); i++) //goes through the event list
	{
		Events temp = eventList->getEntry(i); //stores an event in a temp variable
		outFile << temp.getName() << ",";
		for (int j = 0; j < temp.getDates().size(); j++)
		{
			outFile << temp.getDates()[i]; //writes the event info to file
		}
		if (!temp.getTimeSlots()->isEmpty()) //if there are time slots for the event
		{
			for (int j = 1; j <= temp.getTimeSlots()->getLength(); j++) //goes through the time slots
			{
				outFile << "." << temp.getTimeSlots()->getEntry(j).getTimeSlot() << "," << temp.getTimeSlots()->getEntry(j).getNum() << ","; //writes the time slot info to file
			}
		}
	}
	outFile.close(); //closes the file
}

void Executive::setCurrentUser(std::string name)
{
	m_currentUser = name; //set the current user to the name passed in
}

bool Executive::addEvent(std::string name, int numOfDays, std::vector<std::string> dates)
{
	eventList->addBack(Event(name, numOfDays, dates)); //creates a new event with the parameters passed in and stores them in the back of the event list
	eventList->sort(); //sorts the event list
}

std::vector<Events> Executive::getEventList()
{
<<<<<<< HEAD
	std::string name = ""; //creates a placeholder variable for a name of an event
	int month = 0; //creates a placeholder variable for a month of an event
	int day = 0; //creates a placeholder variable for a day of an event
	int year = 0; //creates a placeholder variable for a year of an event
	std::string AMPM ="";
	std::cout << "\nWhat is the name of your event?\n";
	std::cin.ignore(); //wipes cin
	std::getline(std::cin, name); //gets the name of the event
	if (validEventName(name,17) == true) {//checks if event name entered is >0 and less than 17 characters
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
			for (int i = 0; i < 12; i++)
			{
				std::cout << "  (" << i + 1 << ")" << " " << m_months[i] << std::endl;
			}
			std::cin.ignore(); //wipes cin
			std::cin >> month; //takes in the month
			while (std::cin.fail()) //fail bit code to recover from bad input
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Invalid input, please select '1'-'12'\n";
				std::cin >> month;
			}
			std::cout << "\nWhat day will your event take place?\n";
			std::cin.ignore(); //wipes cin
			std::cin >> day; //takes in the day
			while (std::cin.fail()) //fail bit code to recover from bad input
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Invalid input, please enter a day\n";
				std::cin >> day;
			}

			if (dateCheck(year, month, day) == true) //if the date is valid
			{
				break; //break out of the while loop
			}
			else //if the date is invalid
			{
				std::cout << "\nThis date is invalid, please enter a valid date\n"; //notify the user that the date is invalid
			}
		}
	}
	else
	{
		std::cout << "\nInvalid name. Please enter a valid name. (The event name needs to be less than 17 characters.)";
		addEvent(mode12);
	}

	if(mode12) //if 12-hr mode
	{
		std::cout << "\nWhat time will your event start? \n";

		int hourMin = 0; //an int that stores the time of the event
		std::string AMPM = ""; //a string that stores whether the time is am or pm

		std::cout<<"Start Time (format like 1000 for 10:00): ";
		std::cin.ignore(); //wipes cin
		std::cin>>hourMin; //takes in and stores starting the time
		while (std::cin.fail()) //fail bit code to recover from bad input
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input, please enter a time\n";
			std::cin >> hourMin;
		}
		while(AMPM!="AM" && AMPM!="PM" &&  AMPM != "p.m." && AMPM != "a.m." && AMPM != "pm" && AMPM != "am" && AMPM != "P.M." && AMPM != "A.M."){
			std::cout<<"\nIs this AM or PM (enter AM or PM): ";
			std::cin.ignore(); //wipes cin
			std::cin >> AMPM; //takes in whether the time is am or pm
//		std::cout << AMPM;
		}
		if(AMPM == "PM" || AMPM == "p.m." || AMPM == "pm" || AMPM == "P.M.") //if the time is pm
		{
			hourMin = hourMin + 1200; //add 12 hours to the time
		}

		m_stime = std::to_string(hourMin);

		std::cout<<"\nEnd Time (format like 1000 for 10:00): ";
		std::cin.ignore(); //wipes cin
		std::cin>>hourMin;
		AMPM = "";//resets the AMPM string
		while(AMPM!="AM" && AMPM!="PM" &&  AMPM != "p.m." && AMPM != "a.m." && AMPM != "pm" && AMPM != "am" && AMPM != "P.M." && AMPM != "A.M."){
		{
			std::cout<<"\nIs this AM or PM (enter AM or PM): ";
			std::cin.ignore(); //wipes cin
			std::cin>>AMPM;
		}
		if(AMPM == "PM" || AMPM == "p.m." || AMPM == "pm" || AMPM == "P.M.") //if the time is pm
			hourMin = hourMin + 1200;
		}

		m_etime = std::to_string(hourMin);
	} else {
		std::cout << "\nWhat time will your event start?\n";
		std::cin.ignore(); //wipes cin
		std::cin >> m_stime;
		while(std::stoi(m_stime) >= 2359 || std::stoi(m_stime) < 500 || (std::stoi(m_stime) >= 1201 && std::stoi(m_stime) <= 1259))
		{
			std::cout <<"Invalid Time input! Try Again!\n";
			std::cin.ignore(); //wipes cin
			std::cin >> m_stime;
		}
		std::cout << "\nWhat time will your event end?\n";
		std::cin.ignore(); //wipes cin
		std::cin >> m_etime;
		while(std::stoi(m_etime) >= 2359 || std::stoi(m_etime) < 500 || (std::stoi(m_etime) >= 1201 && std::stoi(m_etime) <= 1259))
		{
			std::cout <<"Invalid Time input! Try Again!\n";
			std::cin.ignore(); //wipes cin
			std::cin >> m_etime;
		}
	}

	Events event1(name, month, day, year);

	m_intSTime = stoi(m_stime);
	m_intETime = stoi(m_etime);
	double numTs = ceil(((std::stod(m_etime) - std::stod(m_stime))/100) * 3);
	std::cout << numTs << "\n";
	int tsup = ceil(m_intSTime);
	for (int i = 0; i < numTs; i ++)
=======
	std::vector<Events> temp; //creates the temp vector that will be returned

	for (int i = 0; i < eventList->getLength(); i++) //iterates through the event list
>>>>>>> Event/Availability
	{
		temp.push_back(eventList->getEntry(i+1)); //adds the event at index i+1 to the vector
	}

	return(temp); //returns the vector
}

bool Executive::dateCheck(int y, int m, int d)
{
<<<<<<< HEAD
	// if the day is less than 1, then it can't possibly be a valid day
=======
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int curY = (1900 + ltm->tm_year);
	if (y < curY)
	{
		std::cout << "The year needs to be this year or later, you cannot create a past event!\n";
		return false;
		if (m <= ltm->tm_mon)
		{
			std::cout << "The month needs to be this month or later, you cannot create a past event!\n";
			return false;
			if (d <= ltm->tm_mday)
			{
				std::cout << "The day needs to be this day or later, you cannot create a past event!\n";
				return false;
			}
		}

	}
>>>>>>> Event/Availability
	if (d < 1)
	{
		std::cout << "\nThe day must be 1 or higher.\n";
		return false;
	}

	// Check if day is greater than the max amount of days of the month
	//        Jan       March     May       July      August    October    December
	else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		if (d > 31)
		{
			std::cout << "\nYou have selected a day outside the range of this month.\n";
			return false;
		}
	}
	//       April     June      September November
	else if (m == 4 || m == 6 || m == 9 || m == 11)
	{
		if (d > 30)
		{
			std::cout << "\nYou have selected a day outside the range of this month.\n";
			return false;
		}
	}

	// Check if the day is greater than the amount of days in February
	//       February
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

<<<<<<< HEAD
	//check if the day is in the past
	const int monthIndex = 0;
	const int dayIndex = 1;
	const int yearIndex = 2;

	time_t now = time(0);
	tm* ltm = localtime(&now);
	char currentDate[32];
	std::strftime(currentDate, 32, "%m/%d/%Y", ltm);
	std::vector<std::string> currentDateVector = split(currentDate, '/');
	if ( y < std::stoi(currentDateVector[yearIndex])) {
		std::cout <<"The year needs to be this year or later, you cannot create a past event!\n";
		return false;
	}
	else if (y == std::stoi(currentDateVector[yearIndex]) && m < std::stoi(currentDateVector[monthIndex])){
		std::cout << "The month needs to be this month or later, you cannot create a past event!\n";
		return false;
	}
	else if (y == std::stoi(currentDateVector[yearIndex]) && m == std::stoi(currentDateVector[monthIndex]) && d < std::stoi(currentDateVector[dayIndex])) {
		std::cout << "The day needs to be this day or later, you cannot create a past event!\n";
		return false;
	}


	// check if event date is on a holiday
	int size = sizeof(holidays) / sizeof(holidays[0]);
	for (int i = 0; i < size; i++) {
		std::vector<std::string> holiday = split(holidays[i], '/');
		if (std::stoi(holiday[monthIndex]) == m && std::stoi(holiday[dayIndex]) == d) {
			std::cout << "The event cannot be on a holiday!\n";
=======
	const std::string Events::holidays[3] = { "01/01", "07/4","12/25" };
	int size = sizeof(holidays);

	//check if holiday (uses holiday size)
	for (int i = 0; i < size; i++) {
		std::istringstream issholiday(holidays[i]);
		std::string f;
		std::vector<std::string> holiday;
		while (std::getline(issholiday, f, '/')) {
			holiday.push_back(f);
		}
		if (std::stoi(holiday[0]) == m && std::stoi(holiday[1]) == d) {
>>>>>>> Event/Availability
			return false;
		}
	}
	return true;
}
<<<<<<< HEAD
bool Executive::validEventName(std::string name, unsigned int value) {
	if (name.length() == 0 || name.length()>(value-1))
		return false;
	else
		return true;
}
//seperates a string by the delimiting character
std::vector<std::string> Executive::split(std::string mainString, char seperatingChar) {
	std::istringstream issMainString(mainString);
	std::string f;
	std::vector<std::string> returnString;
	while (std::getline(issMainString, f, seperatingChar)) {
		returnString.push_back(f);
	}
	return returnString;
}
=======
>>>>>>> Event/Availability
