#pragma once

#ifndef EVENTS_H
#define EVENTS_H
#include <iostream>
#include <sstream>

class Events
{
public:

	/* Constructor instantiates all global instance variables **/
	Events();
	
	/* Parameterized Constructor **/
	Events (std::string n, int m, int d, int y, int s_t, int e_t);

	/* Copy Constructor **/
	Events(const Events& object);

	/* Operator = overload*/
	void operator=(const Events& rhs);

	/* Operator greater/less than Overloads for comparing instances of class using name variable **/
	bool operator>(const Events& rhs) const;
	bool operator<(const Events& rhs) const;

	/* Operator equal to overload for comparing keys**/
	bool operator==(const Events& newEvent) const;

	/* set methods set private variables
	@post respective instance variables set equal to argument passed to set methods
	@param new values for respective instance variables **/
	void setName(std::string n);
	int setMonth(int m);
	int setDay(int d);
	int setYear(int y);
	int setS_Time(int s_t);
	int setE_Time(int e_t);

	/* get methods return their respective instance variables
	@return repective instance variables**/
	int getName() const;
	int getMonth() const;
	int getDay() const;
	int getYear() const;
	int getS_Time() const;
	int getE_Time() const;


private:
	std::string name; // event name
	int month; // month of event
	int day; // day of event
	int year; // year of event
	int s_time; // start time of event
	int e_time; // end time of event
	bool timeSlots[72]; // slots for event openings

};
#endif