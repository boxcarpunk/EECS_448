#include "Executive.h"

Executive::Executive()
{
}

Executive::~Executive()
{
}

void Executive::setCurrentUser(std::string name)
{
	m_currentUser = name; //set the current user to the name passed in
}

std::string Executive::getCurrentUser() const
{
	return(m_currentUser); //returns the name of the current user
}

Events& Executive::addEvent(std::string eventName, std::string adminName, int numOfDays, std::vector<std::string> dates)
{
	Events* newEvent = new Events(eventName, adminName, numOfDays, dates); //creates a new event with the parameters passed in
	m_eventList.push_back(*newEvent); //adds the event to the back of the event list
	return(*newEvent); //returns the newly created event
}

std::vector<Events> Executive::getEventList() const
{
	return(m_eventList); //returns the vector
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
		if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) //Leap year conditions: cite "crazzyguy101 - cplusplus.com"
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

	const std::string holidays[3] = { "01/01", "07/4","12/25" };
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
