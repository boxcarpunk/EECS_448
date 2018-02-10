#pragma once
#include <iostream>
#include <sstream>
#include "LinkedList.h"
#include "TimeSlots.h"

class Events
{
public:

	/* Constructor instantiates all global instance variables **/
	Events();

	/* Parameterized Constructor **/
	Events (std::string n, int m, int d, int y);

	/* Operator greater/less than overloads for comparing instances of class using name variable **/
	bool operator>(const Events& rhs) const;
	bool operator<(const Events& rhs) const;

	/* Operator equal to overload for comparing keys**/
	bool operator==(const Events& newEvent) const;

	/* set methods set private variables
	@post respective instance variables set equal to argument passed to set methods
	@param new values for respective instance variables **/
	void setName(std::string n);
	void setMonth(int m);
	void setDay(int d);
	void setYear(int y);

	/* get methods return their respective instance variables
	@return repective instance variables**/
	std::string getName() const;
	int getMonth() const;
	int getDay() const;
	int getYear() const;

	/* getInfo prints info abour event to the screen. Does not actually return any value.*/
	void getInfo();

	/* Adds time slot for event. Executive.cpp controls how many time slots are filled for an event.
	@post new TimeSlots object added to m_TimeSlot list for an event
	@param s_t the start time of a time slot
	@param numOfAtt the number of attendants for a certain event**/
	void addTimeSlots(int s_t, int numOfAtt);


private:
	std::string name; // event name
	int month; // month of event
	int day; // day of event
	int year; // year of event
	int s_time; 
	int e_time;
	LinkedList<TimeSlots>* m_TimeSlot; // pointer to list of timeslots for this event
};
