/**
* @author Robert Goss
* @cal448
* @date 12 February 2017
* @brief Events class implementation
* @file Events.cpp **/

#include "Events.h"

Events::Events()
{
	// initialize variables to "" for strings, 0 for ints
	//timeSlots = new TimeSlots[72];
	m_name = "";
	m_month = 0;
	m_day = 0;
	m_year = 0;
	m_TimeSlot = new LinkedList<TimeSlots>();
}

Events::Events(std::string name, int month, int day, int year)
{
	m_name = name;
	m_month = month;
	m_day = day;
	m_year = year;
	m_TimeSlot = new LinkedList<TimeSlots>();
}

Events::~Events()
{
	; // empty destructor
}

void Events::setName(std::string name)
{
	m_name = name; // set name
}

void Events::setMonth(int month)
{
	m_month = month; //set month
}

void Events::setDay(int day)
{
	m_day = day; // set day
}

void Events::setYear(int year)
{
	m_year = year; // set year
}

std::string Events::getName() const
{
	return m_name; // return name of event
}

int Events::getMonth() const
{
	return m_month; ///return month
}

int Events::getDay() const
{
	return m_day; //return day
}

int Events::getYear() const
{
	return m_year; // return year
}

LinkedList<TimeSlots>* Events::getTimeSlots() const
{
	return m_TimeSlot; // return m_TimeSlot
}

void Events::getInfo()
{
	// output info for this event to std::cout
	std::cout << "\n" << m_name << " is occuring on " << m_month << "/" << m_day << "/" << m_year << ".\n";
	for (int i=1; i == m_TimeSlot->getLength(); i++)
	{
		std::cout << "There are " << m_TimeSlot->getEntry(i).getNum() << " people available at " << m_TimeSlot->getEntry(i).getTimeSlot() << ".\n";
	}
}

void Events::addTimeSlots(int s_t, int numOfAtt)
{
	TimeSlots newSlot(numOfAtt, s_t); // instantiate new time slot
	m_TimeSlot->addBack(newSlot); // add new time slot to end of linked list
	m_TimeSlot->sortListTime(); // call sort list method to ensure that list is sorted after insertion of new time slot
}
