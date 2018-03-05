#include "TimeSlots.h"

TimeSlots::TimeSlots()
{
	m_numOfAtt = 0; //sets the number of attendees to zero
	m_Index = 0; //sets the time slot to zero
}

TimeSlots::TimeSlots(int index)
{
	m_numOfAtt = 0; //sets the number of attendees to zero

	if ((index < 54) && (index >= 0)) //if the index is valid
	{
		m_Index = index; //sets the index of the time slot to the index passed in
	}
}

void TimeSlots::increaseAtt()
{
	m_numOfAtt += 1; //increases the number of attendees by one
}

int TimeSlots::getTimeSlot()
{
	return m_TimeSlot; //returns the time slot
}

void TimeSlots::setIndex(int index)
{
	if ((index < 54) && (index >= 0)) //if the index is valid
	{
		m_Index = index; //sets the index of the time slot to the index passed in
	}
}

int TimeSlots::getNum()
{
	return m_numOfAtt; //returns the number of attendees
}

int TimeSlots::getIndex()
{
	return m_Index; //returns the time slot
}

std::vector<std::string> TimeSlots::getAttendees()
{
	return m_attendees; //returns the vector of attendee names
}

void TimeSlots::addAttendee(std::string name)
{
	for(int i = 0; i < m_attendees.size(); i++) //runs through the attendee vector
	{
		if(name == m_attendees[i]) //if the person being added is already in the list
		{
			return; //you shouldn't add an attendee twice
		}
	}
	
	m_attendees.push_back(name); //if the attendee is not already in the time slot then add them
	m_numOfAtt++; //increment the number of attendees
}

bool TimeSlots::operator==(const TimeSlots& rhs) const
{
	return((m_Index == rhs.m_Index) && (m_numOfAtt == rhs.m_numOfAtt)); //true if the index and number of attendees are the same, false otherwise
}

TimeSlots& TimeSlots::operator=(const TimeSlots& rhs)
{
	m_numOfAtt = rhs.m_numOfAtt; //makes the number of attendees equal
	m_Index = rhs.m_Index; //makes the indices equal
	m_attendees = rhs.m_attendees; //makes the list of attendee names equal

	return(*this); //returns this object
}

bool TimeSlots::operator>(const TimeSlots& rhs) const
{
	return(m_Index > rhs.m_Index); //true if the current index is after the one passed in, false otherwise
}
