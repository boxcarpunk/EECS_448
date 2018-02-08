#pragma once

#ifndef EVENTS_H
#define EVENTS_H
#include <iostream>
#include <sstream>
#include <time.h> /* clock_t, clock, CLOCKS_PER_SEC */
#include <ctime>

class Events
{
public:

	/* Constructor instantiates all global instance variables **/
	Events();

	/* Copy Constructor **/
	Events(const Events& object);

	/* Operator = overload*/
	void operator=(const Events& rhs);

	/* Operator greater/less than Overloads for comparing instances of class using name variable **/
	bool operator>(const Events& rhs) const;
	bool operator<(const Events& rhs) const;

	/* Operator equal to overload for comparing keys**/
	bool operator==(const Events& newEvent) const;

	/* set methods set for private variables
	@post respective instance variables set equal to argument passed to set methods
	@param new values for respective instance variables **/
	void setEventName(std::string n);
	void setNumOfUsers(int n);
	void setStartTime(int hours, int minutes, int seconds, int month, int day, int year);
	void setEndTime(int hours, int minutes, int seconds, int month, int day, int year);


	/* get methods return their respective instance variables
	@return repective instance variables**/
	std::string getEventName() const;
	int getNumOfUsers() const;

	int getStartHours() const;
	int getStartMinutes() const;
	int getStartSeconds() const;
	int getStartMonth() const;
	int getStartDay() const;
	int getStartYear() const;

	int getEndHours() const;
	int getEndMinutes() const;
	int getEndSeconds() const;
	int getEndMonth() const;
	int getEndDay() const;
	int getEndYear() const;


private:
	std::string eventName;
	std::string stringMonth;
	int numOfUsers;
	std::tm startOfEvent;
	std::tm endOfEvent;
	bool timeSlots[72];

};
#endif