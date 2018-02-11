/**
* @author Sahil Hirani
* @cal448
* @date 12 February 2017
* @brief TimeSlots class implementation
* @file TimeSlots.cpp **/

#include "TimeSlots.h"

TimeSlots::TimeSlots()
{
	m_numOfAtt = 0;
	m_TimeSlot = 0;
}

TimeSlots::TimeSlots(int num, int time)
{
	m_numOfAtt = num;
	m_TimeSlot = time;
}

void TimeSlots::setNum(int num)
{
	m_numOfAtt = num;
}

void TimeSlots::setTimeSlot(int time)
{
	m_TimeSlot = time;
}

int TimeSlots::getNum()
{
	return m_numOfAtt;
}

int TimeSlots::getTimeSlot()
{
	return m_TimeSlot;
}

TimeSlots::~TimeSlots()
{
	//Destructor for good coding practice
}
