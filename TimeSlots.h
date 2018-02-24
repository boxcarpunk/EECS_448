#pragma once
#include <iostream>

class TimeSlots
{
public:
	/**
	*	A new time slot is created with default values
	*	@pre None
	*	@post Private member variables are set to defaults and a time slot is created
	*	@param None
	*	@return None
	*/
	TimeSlots();
	
	/**
	*	Empty destructor
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
	~TimeSlots();

	/**
	*	A new time slot is created with default values
	*	@pre Valid number of attendees and valid time
	*	@post Private member variables are set and a time slot is created
	*	@param Integers representing time and attendees
	*	@return None
	*/
	TimeSlots(int num, int time);

	/**
	*	The number of attendees is set
	*	@pre Valid number of attendees
	*	@post Private member variable m_numOfAtt is set to passed in value
	*	@param Integer representing number of attendees
	*	@return None
	*/
	void setNum(int num);

	/**
	*	The time slot for an attendee is set
	*	@pre Valid time
	*	@post Private member variable m_TimeSlot is set to passed in value
	*	@param Integer representing time
	*	@return None
	*/
	void setTimeSlot(int time);

	/**
	*	The number of attendees is returned to the program
	*	@pre None
	*	@post None
	*	@param None
	*	@return An int representing the number of attendees
	*/
	int getNum();

	/**
	*	The time slot for an attendee is returned to the program
	*	@pre None
	*	@post None
	*	@param None
	*	@return An int representing the timeslot
	*/
	int getTimeSlot();

	/**
	*	Increases the number of attendees by one
	*	@pre None
	*	@post The value of m_numOfAtt is increased by one
	*	@param None
	*	@return None
	*/
	void increaseAtt();

	/**
	*	Operator overload for == between two time slots
	*	@pre None
	*	@post None
	*	@param A TimeSlot to be compared to this one
	*	@return True if m_TimeSlot and m_numOfAtt are equal, false otherwise
	*/
	bool operator==(const TimeSlots& rhs) const;

	/**
	*	Operator overload for > between two time slots
	*	@pre None
	*	@post None
	*	@param A TimeSlot to be compared to this one
	*	@return True if the current m_TimeSlot is later than the m_TimeSlot passed in, false otherwise
	*/
	bool operator>(const TimeSlots& rhs) const;

private:
	int m_numOfAtt;  /**< the number of attendants for a certain timeslot in an event */
	int m_TimeSlot;  /**< the timeslot for an event */

};
