#pragma once
#include <iostream>
/**
*	@file TimeSlots.h
*	@author Everyone
*	@date 2-12-18
*	@brief Header file for TimeSlots class, a class that holds time slots that an event occupies
*/

class TimeSlots
{
	public:
		TimeSlots();
		TimeSlots(int num, int time);
		void setNum(int num);
		void setTimeslot(int time);
		int getNum();
		int getTimeslot();

	private:
		int m_numOfAtt;
		int m_TimeSlot;

};
