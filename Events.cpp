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

// For right now we don't need a copy constructor for Events.cpp, but I will leave its unfinished implementation
// here in case we need it for some reason later on
/*
Events::Events(const Events& object)
{
name = object.name; // copy event name
month = object.month; // copy month of event
day = object.day; // copy day of event
year = object.year; // copy year of event
m_TimeSlot = new LinkedList<TimeSlots>();

// copy time slots' values
for (int i = s_t; i <= e_t; i += 20)
{
TimeSlots newSlot(0, i);
m_TimeSlot->addBack(newSlot);
}

m_TimeSlot->sortListTime();
} */

Events::~Events()
{
	// delete m_TimeSlot;
	// m_TimeSlot = nullptr;
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
	return 0;
}

void Events::setName(std::string n)
{
	name = n;
}

void Events::setMonth(int m)
{
	month = m;
}

void Events::setDay(int d)
{
	day = d;
}

void Events::setYear(int y)
{
	year = y;
}

std::string Events::getName() const
{
	return name;
}

int Events::getMonth() const
{
	return month;
}

int Events::getDay() const
{
	return day;
}

int Events::getYear() const
{
	return year;
}

void Events::getInfo()
{
	std::cout << "\n" << name << " is occuring on " << month << "/" << day << "/" << year << " from " << s_time << " to " << e_time << ".\n";
}

void Events::addTimeSlots(int s_t, int e_t)
{
	s_time = s_t;
	e_time = e_t;
	for (int i = s_t; i <= e_t; i += 20)
	{
		TimeSlots newSlot(0, i);
		m_TimeSlot->addBack(newSlot);
	}

	m_TimeSlot->sortListTime();
}