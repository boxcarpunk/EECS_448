#include "Events.h"

Events::Events()
{
	// initialize variables to "" for strings, 0 for ints, false for bools
	name = "";
	month = 0; 
	day = 0; 
	year = 0; 
	s_time = 0; 
	e_time = 0; 

	for (int i = 0; i < 72; i++)
	{
		timeSlots[i] = false;
	}
}

Events::Events(std::string n, int m, int d, int y, int s_t, int e_t)
{
	name = n;
	month = m;
	day = d;
	year = y;
	s_time = s_t;
	e_time = e_t;
	
	for (int i = 0; i < 72; i++)
	{
		timeSlots[i] = false;
	}
}

Events::Events(const Events& object)
{
	name = object.name; // copy event name
	month = object.month; // copy month of event
	day = object.day; // copy day of event
    year = object.year; // copy year of event
	s_time = object.s_time; // copy start time of event
	e_time = object.e_time; // copy end time of event

	// copy time slots' boolean values
	for (int i = 0; i < 72; i++)
	{
		timeSlots[i] = object.timeSlots[i];
	}
}

void Events::operator=(const Events& rhs)
{
	name = rhs.name; // copy event name
	month = rhs.month; // copy month of event
	day = rhs.day; // copy day of event
	year = rhs.year; // copy year of event
	s_time = rhs.s_time; // copy start time of event
	e_time = rhs.e_time; // copy end time of event

	// copy time slots' boolean values
	for (int i = 0; i < 72; i++)
	{
		timeSlots[i] = rhs.timeSlots[i];
	}
}

bool Events::operator>(const Events& rhs) const
{
	return 0;
}

bool Events::operator<(const Events& rhs) const
{
	return 0;
}

bool Events::operator==(const Events& newEvent) const
{
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

void Events::setS_Time(int s_t)
{
	s_time = s_t;
}

void Events::setE_Time(int e_t)
{
	e_time = e_t;
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

int Events::getS_Time() const
{
	return s_time;
}

int Events::getE_Time() const
{
	return e_time;
}

void Events::getInfo()
{
	std::cout << "\n" << name << " is occuring on " << month << "/" << day << "/" << year << " from " << s_time << " to " << e_time << ".\n";
}







