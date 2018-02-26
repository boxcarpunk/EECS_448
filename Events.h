#pragma once
#include <sstream>
#include <string>
#include "LinkedList.h"
#include "TimeSlots.h"

class Events
{
public:

	/**
	*	Creates an event with default values
	*	@pre None
	*	@post Assigns member variables a default value and creates an event
	*	@param None
	*	@return None
	*/
	Events();

	/**
	*	Creates an event with default values
	*	@pre None
	*	@post Assigns member variables the corresponding value passed in and creates an event
	*	@param String for name and integers for month, day, and year
	*	@return None
	*/
	Events (std::string name, int motnh, int day, int year);

	/**
	*	Empty destructor
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
	~Events();

	static const std::string holidays[3];

	/**
	*	Private member variable is assigned correct value
	*	@pre The name is valid
	*	@post The private member variable is set to match the parameter
	*	@param String representing the name of an event
	*	@return None
	*/
	void setName(std::string name);

	/**
	*	Private member variable is assigned correct value
	*	@pre Int representing the month of an event
	*	@post The private member variable is set to match the parameter
	*	@param Int representing the month of an event
	*	@return None
	*/
	void setMonth(int month);

	/**
	*	Private member variable is assigned correct value
	*	@pre The day is valid
	*	@post The private member variable is set to match the parameter
	*	@param Int representing the day of an event
	*	@return None
	*/
	void setDay(int day);

	/**
	*	Private member variable is assigned correct value
	*	@pre The year is valid
	*	@post The private member variable is set to match the parameter
	*	@param Int representing the year of an event
	*	@return None
	*/
	void setYear(int year);

	/**
	*	The name of the event being accessed is returned to the program
	*	@pre None
	*	@post The name of an event it returned
	*	@param None
	*	@return A string representing the name of the event
	*/
	std::string getName() const;

	/**
	*	The month of the event being accessed is returned to the program
	*	@pre None
	*	@post The month of an event it returned
	*	@param None
	*	@return An int representing the month of the event
	*/
	int getMonth() const;

	/**
	*	The day of the event being accessed is returned to the program
	*	@pre None
	*	@post The day of an event it returned
	*	@param None
	*	@return An int representing the day of the event
	*/
	int getDay() const;

	/**
	*	The year of the event being accessed is returned to the program
	*	@pre None
	*	@post The year of an event it returned
	*	@param None
	*	@return An int representing the year of the event
	*/
	int getYear() const;

	/**
	*	The list of time slots for the event being accessed is returned to the program
	*	@pre None
	*	@post The list of time slots for an event it returned
	*	@param None
	*	@return Head pointer to m_TimeSlot. Specifically created for >, <, == operator overloads
	*/
	LinkedList<TimeSlots, TimeSlots>* getTimeSlots() const;

	/**
	*	The information for an event is printed out so that the user can see it
	*	@pre None
	*	@post The info for an event is printed
	*	@param None
	*	@return None
	*/
	void getInfo();

	/**
	*	Adds time slot for event. Executive.cpp controls how many time slots are filled for an event.
	*	@pre None
	*	@post New TimeSlots object added to m_TimeSlot list for an event
	*	@param numOfAtt the number of attendants for a certain event
	*	@return None
	*/
	void addTimeSlots(int s_t, int numOfAtt);


	/**
	*	Operator overload for == between two events, checks the name and dates of the events
	*	@pre None
	*	@post None
	*	@param The event to be compared to this one
	*	@return True if the name and date of the events are the same, false otherwise
	*/
	bool operator==(const Events& rhs) const;

	/**
	*	Operator overload for == between an event and a string, checks the string against the event's name
	*	@pre None
	*	@post None
	*	@param A string to be compared to the event's name
	*	@return True if the string is equal to the name of the event, false otherwise
	*/
	bool operator==(const std::string& rhs) const;

	/**
	*	Operator overload for > between two events, checks the dates of the events
	*	@pre None
	*	@post None
	*	@param The event to be compared to this one
	*	@return True if the date of the current event is after the event passed in, false otherwise
	*/
	bool operator>(const Events& rhs) const;


private:
	std::string m_name; /**< event name */
	int m_month; /**< month of event */
	int m_day; /**< day of event */
	int m_year; /**< year of event */
	LinkedList<TimeSlots, TimeSlots>* m_TimeSlot; /**< pointer to list of time slots for this event */
};
