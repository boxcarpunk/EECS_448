/**
* @author Sahil Hirani
* @cal448
* @date 12 February 2017
* @brief TimeSlots class implementation
* @file TimeSlots.cpp **/

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

int TimeSlots::getNum()
{
	return m_numOfAtt; //returns the number of attendees
}

int TimeSlots::getTimeSlot()
{
	return m_TimeSlot; //returns the time slot
}

TimeSlots::~TimeSlots()
{
	//Destructor for good coding practice
}
