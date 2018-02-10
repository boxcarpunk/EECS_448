#include "Events.h"
#include "LinkedList.h"

Events::Events()
{
	// initialize variables to "" for strings, 0 for ints
	//timeSlots = new TimeSlots[72];
	name = "";
	month = 0;
	day = 0;
	year = 0;
	m_TimeSlot = new LinkedList<TimeSlots>();
	s_time = 0;
	e_time = 0;
}

Events::Events(std::string n, int m, int d, int y)
{
	name = n;
	month = m;
	day = d;
	year = y;
	m_TimeSlot = new LinkedList<TimeSlots>();
	s_time = 0;
	e_time = 0;
}

bool Events::operator>(const Events& rhs) const
{
	if (year > rhs.getYear())
	{
		return true;
	}
	else if (year < rhs.getYear())
	{
		return false;
	}
	else
	{
		if (month > rhs.getMonth())
		{
			return true;
		}
		else if (month < rhs.getMonth())
		{
			return false;
		}
		else
		{
			if (day > rhs.getDay())
			{
				return true;
			}
			else
			{
				// TODO need to compare timeslots
				return false;
			}
		}
	}
}

bool Events::operator<(const Events& rhs) const
{
	if (year < rhs.getYear())
	{
		return true;
	}
	else if (year > rhs.getYear())
	{
		return false;
	}
	else
	{
		if (month < rhs.getMonth())
		{
			return true;
		}
		else if (month > rhs.getMonth())
		{
			return false;
		}
		else
		{
			if (day < rhs.getDay())
			{
				return true;
			}
			else
			{
				// TODO need to compare timeslots
				return false;
			}
		}
	}
}

bool Events::operator==(const Events& rhs) const
{
	if (year == rhs.getYear())
	{
		if (month == rhs.getMonth())
		{
			if (day == rhs.getDay())
			{
				// TODO need to compare time slots;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void Events::setName(std::string n)
{
	name = n; // set name
}

void Events::setMonth(int m)
{
	month = m; //set month
}

void Events::setDay(int d)
{
	day = d; // set day
}

void Events::setYear(int y)
{
	year = y; // set year
}

std::string Events::getName() const
{
	return name; // return name of event
}

int Events::getMonth() const
{
	return month; ///return month
}

int Events::getDay() const
{
	return day; //return day
}

int Events::getYear() const
{
	return year; // return year
}

void Events::getInfo()
{
	// output info for this event to std::cout
	std::cout << "\n" << name << " is occuring on " << month << "/" << day << "/" << year << " from " << s_time << " to " << e_time << ".\n";
}

void Events::addTimeSlots(int s_t, int numOfAtt)
{
	TimeSlots newSlot(numOfAtt, s_t); // instantiate new time slot
	m_TimeSlot->addBack(newSlot); // add new time slot to end of linked list
	m_TimeSlot->sortListTime(); // call sort list method to ensure that list is sorted after insertion of new time slot
}