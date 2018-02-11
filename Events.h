/**
* @author Robert Goss
* @cal448
* @date 10 February 2017
* @brief Events class that represents an event in the cal448 program
* @file Events.h **/

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
	Events (std::string name, int motnh, int day, int year);

	/*Destructor*/
	~Events();

	/* Operator greater/less than overloads for comparing instances of class using name variable **/
	bool operator>(const Events& rhs) const;
	bool operator<(const Events& rhs) const;

	/* Operator equal to overload for comparing keys**/
	bool operator==(const Events& newEvent) const;

	/* set methods set private variables
	@post respective instance variables set equal to argument passed to set methods
	@param new values for respective instance variables **/
	void setName(std::string name);
	void setMonth(int month);
	void setDay(int day);
	void setYear(int year);

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
	std::string m_name; // event name
	int m_month; // month of event
	int m_day; // day of event
	int m_year; // year of event
	int s_time;
	int e_time;
	LinkedList<TimeSlots>* m_TimeSlot; // pointer to list of timeslots for this event
};
