#pragma once
/**
*	@file TimeSlots.h
*	@author Robert Goss
*	@date 2-12-18
*	@brief Header file for TimeSlots class, a class that holds time slots that an event occupies
*/

#ifndef TIMESLOTS_H
#define TIMESLOTS_H

class TimeSlots
{
public:
	TimeSlots();
private:
	int timeSlots[72];
};

#endif