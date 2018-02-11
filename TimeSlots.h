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
		/* TimeSlots Default Constructor instantiates values for m_numOfAtt = 0 and m_TimeSlots = 0*/
		TimeSlots();
		/* TimeSlots Destructor*/
		~TimeSlots();
		/* TimeSlots Parameterized Constructor instantiates values for m_numOfAtt and m_TimeSlots with num and time parameters, respectively*/
		TimeSlots(int num, int time);
		/* setNum sets m_numOfAtt variable
		@post m_numOfAtt = num
		@param num the number of attendants for a certain timeslot in an event**/
		void setNum(int num);
		/* setTimeslot sets m_Timeslot variable
		@post m_Timeslot = time
		@param time the timeslot for an event**/
		void setTimeslot(int time);
		/* Get method for number of attendantsfor a time slot
		@return m_numOfAtt**/
		int getNum();
		/* Get method for the timeslot of an event
		@return m_numOfAtt**/
		int getTimeslot();

	private:
		int m_numOfAtt;  // the number of attendants for a certain timeslot in an event
		int m_TimeSlot;  // the timeslot for an event

};
