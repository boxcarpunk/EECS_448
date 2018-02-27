#include "Events.h"

Events::Events()
{
	m_name = ""; //sets the name to the empty string
	m_TimeSlot = new LinkedList<TimeSlots, TimeSlots>(); //creates a linked list of time slots
}

Events::Events(std::string name, std::string month, std::string day, std::string year, int numOfDays)
{
	std::string date = month + "/" + day + "/" + year;

	m_TimeSlot = new LinkedList<TimeSlots, TimeSlots>(); //creates a linked list of time slots
	m_numOfDays = numOfDays;
}

Events::~Events()
{
	//empty destructor
}

void Events::setName(std::string name)
{
	m_name = name; //sets the name to what was passed in
}

void Events::setNumOfDays(int num)
{
	m_numOfDays = num;
}

void Events::setDates(std::string date)
{
	m_dates.push_back(date); //sets the month to what was passed in
}

std::string Events::getName() const
{
	return m_name; //returns the name of the event
}

int Events::getNumOfDays()
{
	return m_numOfDays;
}

std::vector<std::string> Events::getDates() const
{
	return m_dates; //returns the month of the event
}


LinkedList<TimeSlots, TimeSlots>* Events::getTimeSlots() const
{
	return m_TimeSlot; //returns the linked list of time slots
}

void Events::getInfo()
{
	std::string year, month, day;
	std::string date = m_dates[0];
	day = date.substr(0, 2);
	month = date.substr(3, 2);
	year = date.substr(6, 10);

	//TODO change to include all dates
	std::cout << "\n" << m_name << " is occuring on " << month << "/" << day << "/" << year << ".\n"; //prints the name and date of the event
	for (int i=1; i == m_TimeSlot->getLength(); i++) //goes through the linked list of time slots
	{
		std::cout << "There are " << m_TimeSlot->getEntry(i).getNum() << " people available at " << m_TimeSlot->getEntry(i).getTimeSlot() << ".\n"; //prints the number of attendees for each relevant time slot
	}
}

void Events::addTimeSlots(int s_t, int numOfAtt)
{
	TimeSlots newSlot(numOfAtt, s_t); // instantiate new time slot
	m_TimeSlot->addBack(newSlot); // add new time slot to end of linked list
	m_TimeSlot->sort(); //sort the list
}

bool Events::operator==(const Events& rhs) const
{
	std::string rhsYear, rhsMonth, rhsDay, rhsDate;
	rhsDate = rhs.getDates()[0];
	rhsDay = rhsDate.substr(0, 2);
	rhsMonth = rhsDate.substr(3, 2);
	rhsYear = rhsDate.substr(6, 10);

	std::string year, month, day;
	std::string date = m_dates[0];
	day = date.substr(0, 2);
	month = date.substr(3, 2);
	year = date.substr(6, 10);

	return((m_name == rhs.m_name) && (year == rhsYear) && (month == rhsMonth) && (day == rhsDay)); //returns true if the name, year, month, and day are the same
}

bool Events::operator==(const std::string& rhs) const
{
	return(m_name == rhs); //returns true of the string is equal to the name of the event
}

bool Events::operator>(const Events& rhs) const
{
	std::string rhsYear, rhsMonth, rhsDay, rhsDate;
	rhsDate = rhs.getDates()[0];
	rhsDay = rhsDate.substr(0, 2);
	rhsMonth = rhsDate.substr(3, 2);
	rhsYear = rhsDate.substr(6, 10);

	std::string year, month, day;
	std::string date = m_dates[0];
	day = date.substr(0, 2);
	month = date.substr(3, 2);
	year = date.substr(6, 10);

	if (year > rhsYear) //if the current event is at a later year
	{
		return(true); //returns true because the current event is after the event passed in
	}
	else if (year == rhsYear) //if they occur on the same year
	{
		if (month > rhsMonth) //if the current event is at a later month in the same year
		{
			return(true); //returns true because the current event is after the event passed in
		}
		else if (month == rhsMonth) //if they occur on the same month and year
		{
			if (day > rhsDay) //if the current event is at a later day in the same month
			{
				return(true); //returns true because the current event is after the event passed in
			}
		}
	}

	return(false); //returns false if not one of the cases covered above
}
