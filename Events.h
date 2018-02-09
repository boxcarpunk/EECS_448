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

	/* Operator greater/less than Overloads for comparing instances of class using name variable **/
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

	void getInfo();
	bool addTimeSlots(int s_t, int e_t);


private:
	LinkedList<TimeSlots>* m_TimeSlot;
	std::string name; // event name
	int month; // month of event
	int day; // day of event
	int year; // year of event
	int s_time;
	int e_time;
};

#endif