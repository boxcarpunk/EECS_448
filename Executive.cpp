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

bool Executive::addEvent(std::string eventName, std::string adminName, int numOfDays, std::vector<std::string> dates)
{
	Event newEvent = new Event(eventName, adminName, numOfDays, dates); //creates a new event with the parameters passed in
	eventList->addBack(Event(newEvent); //adds the event to the back of the event list
	eventList->sort(); //sorts the event list
	return(newEvent); //returns the newly created event
}

std::vector<Events> Executive::getEventList()
{
	std::vector<Events> temp; //creates the temp vector that will be returned

	for (int i = 0; i < eventList->getLength(); i++) //iterates through the event list
	{
		temp.push_back(eventList->getEntry(i+1)); //adds the event at index i+1 to the vector
	}

	return(temp); //returns the vector
}

bool Executive::dateCheck(int y, int m, int d)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int curY = (1900 + ltm->tm_year);
	if (y < curY)
	{
		//std::cout << "The year needs to be this year or later, you cannot create a past event!\n";
		return false;
		if (m <= ltm->tm_mon)
		{
			//std::cout << "The month needs to be this month or later, you cannot create a past event!\n";
			return false;
			if (d <= ltm->tm_mday)
			{
				//std::cout << "The day needs to be this day or later, you cannot create a past event!\n";
				return false;
			}
		}

	}
	if (d < 1)
	{
		//std::cout << "\nThe day must be 1 or higher.\n";
		return false;
	}
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		if (d > 31)
		{
			//std::cout << "\nYou have selected a day outside the range of this month.\n";
			return false;
		}
	}
	else if (m == 4 || m == 6 || m == 9 || m == 11)
	{
		if (d > 30)
		{
			//std::cout << "\nYou have selected a day outside the range of this month.\n";
			return false;
		}
	}
	else if (m == 2)
	{
		if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) //Leep year conditions: cite "crazzyguy101 - cplusplus.com"
		{
			if (d > 29)
			{
				//std::cout << "\nYou have selected a day outside the range of this month.\n";
				return false;
			}
		}
		else
		{
			if (d > 28)
			{
				//std::cout << "\nYou have selected a day outside the range of this month.\n";
				return false;
			}
		}
	}

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
			return false;
		}
	}
	return true;
}
