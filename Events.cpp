/**
* @author Robert Goss
* @cal448
* @date 12 February 2017
* @brief Events class implementation
* @file Events.cpp **/

#include "Events.h"

Events::Events()
{
	m_name = ""; //sets the name to the empty string
	m_month = 0; //sets the month to 0
	m_day = 0; //sets the day to 0
	m_year = 0; //sets the year to 0
	m_TimeSlot = new LinkedList<TimeSlots>(); //creates a linked list of time slots
}

Events::Events(std::string name, int month, int day, int year)
{
	m_name = name; //sets the name to what was passed in
	m_month = month; //sets the month to what was passed in
	m_day = day; //sets the day to what was passed in
	m_year = year; //sets the year to what was passed in
	m_TimeSlot = new LinkedList<TimeSlots>(); //creates a linked list of time slots
}

Events::~Events()
{
	//empty destructor
}

void Events::setName(std::string name)
{
	m_name = name; //sets the name to what was passed in
}

void Events::setMonth(int month)
{
	m_month = month; //sets the month to what was passed in
}

void Events::setDay(int day)
{
	m_day = day; //sets the day to what was passed in
}

void Events::setYear(int year)
{
	m_year = year; //sets the year to what was passed in
}

std::string Events::getName() const
{
	return m_name; //returns the name of the event
}

int Events::getMonth() const
{
	return m_month; //returns the month of the event
}

int Events::getDay() const
{
	return m_day; //returns the day of the event
}

int Events::getYear() const
{
	return m_year; //returns the year of the event
}

LinkedList<TimeSlots>* Events::getTimeSlots() const
{
	return m_TimeSlot; //returns the linked list of time slots
}

void Events::getInfo()
{
	std::cout << "\n" << m_name << " is occuring on " << m_month << "/" << m_day << "/" << m_year << ".\n"; //prints the name and date of the event
	for (int i=1; i == m_TimeSlot->getLength(); i++) //goes through the linked list of time slots
	{
		std::cout << "There are " << m_TimeSlot->getEntry(i).getNum() << " people available at " << m_TimeSlot->getEntry(i).getTimeSlot() << ".\n"; //prints the number of attendees for each relevant time slot
	}
}

void Events::addTimeSlots(int s_t, int numOfAtt)
{
	TimeSlots newSlot(numOfAtt, s_t); // instantiate new time slot
	m_TimeSlot->addBack(newSlot); // add new time slot to end of linked list
	m_TimeSlot->sortListTime(); // call sort list method to ensure that list is sorted after insertion of new time slot
}
