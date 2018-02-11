/**
* @author Sahil Hirani
* @cal448
* @date 12 February 2017
* @brief TimeSlots is a class that holds time slots that an event occupies
* @file TimeSlots.h **/

#pragma once
#include <iostream>

class TimeSlots
{
	public:
		TimeSlots();
		~TimeSlots();
		TimeSlots(int num, int time);
		void setNum(int num);
		void setTimeslot(int time);
		int getNum();
		int getTimeslot();

	private:
		int m_numOfAtt;
		int m_TimeSlot;

};
