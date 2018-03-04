#include "TimeSlots.h"

TimeSlots::TimeSlots()
{
	m_numOfAtt = 0; //sets the number of attendees to zero
	m_TimeSlot = 0; //sets the time slot to zero
}

TimeSlots::TimeSlots(int num, int time)
{
	m_numOfAtt = num; //sets the number of attendees to what was passed in
	m_TimeSlot = time; //sets the time slot to what was passed in
}

void TimeSlots::increaseAtt()
{
	m_numOfAtt += 1; //increases the number of attendees by one
}

void TimeSlots::setNum(int num)
{
	m_numOfAtt = num; //sets the number of attendees to what was passed in
}

void TimeSlots::setTimeSlot(int time)
{
	m_TimeSlot = time; //sets the time slot to what was passed in
}

void TimeSlots::addAttendee(std::string name)
{
	m_attendees.push_back(name);
}

int TimeSlots::getNum()
{
	return m_numOfAtt; //returns the number of attendees
}

int TimeSlots::getTimeSlot()
{
	return m_TimeSlot; //returns the time slot
}

std::vector<std::string> TimeSlots::getAttendees()
{
	return m_attendees;
}

/*TimeSlots::~TimeSlots()
{
	//Destructor for good coding practice
}*/

bool TimeSlots::operator==(const TimeSlots& rhs) const
{
	return((m_TimeSlot == rhs.m_TimeSlot) && (m_numOfAtt == rhs.m_numOfAtt)); //true if the time slot and number of attendees are the same, false otherwise
}

bool TimeSlots::operator>(const TimeSlots& rhs) const
{
	return(m_TimeSlot > rhs.m_TimeSlot); //true if the current time slot is after the one passed in, false otherwise
}
