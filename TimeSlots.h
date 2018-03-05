#pragma once
#include <vector>

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
	*	A new time slot is created with the values passed in
	*	@pre Index must be valid
	*	@post Index is set and other member variables are set to default values, time slot is created
	*	@param Int representing the index of the time slot within the time slot array
	*	@return None
	*/
	TimeSlots(int index);

	/**
	*	Sets the index that the time slot is at
	*	@pre This index passed in is valid
	*	@post Private member variable m_TimeSlot is set to passed in value
	*	@param Integer representing the index
	*	@return None
	*/
	void setIndex(int index);

	/**
	*	The number of attendees is returned
	*	@pre None
	*	@post None
	*	@param None
	*	@return An int representing the number of attendees
	*/
	int getNum();

	/**
	*	The index of the time slot is returned
	*	@pre None
	*	@post None
	*	@param None
	*	@return An int representing the index of the time slot
	*/
	int getIndex();


	/**
	*	Returns the vector containing the names of the attendees for the time slot
	*	@pre None
	*	@post None
	*	@param None
	*	@return A vector containing the list of names of the attendees
	*/
	std::vector<std::string> getAttendees();

	/**
	*	Operator overload for == between two time slots
	*	@pre None
	*	@post None
	*	@param A TimeSlot to be compared to this one
	*	@return True if m_Index and m_numOfAtt are equal, false otherwise
	*/
	bool operator==(const TimeSlots& rhs) const;

	/**
	*	Operator overload for = between two time slots
	*	@pre None
	*	@post None
	*	@param This time slot is made equal to the one passed in
	*	@return This time slot
	*/
	TimeSlots& operator=(const TimeSlots& rhs);

	/**
	*	Operator overload for > between two time slots
	*	@pre None
	*	@post None
	*	@param A TimeSlot to be compared to this one
	*	@return True if the current m_Index is later than the m_Index passed in, false otherwise
	*/
	bool operator>(const TimeSlots& rhs) const;

private:
	int m_numOfAtt;  /**< the number of attendants for this time slot */
	int m_Index;  /**< the index of the time slot */
	std::vector<std::string> m_attendees; /**< the list of users avaliable for this time slot */
};
