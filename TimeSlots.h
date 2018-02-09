#pragma once
#include <iostream>
/**
*	@file TimeSlots.h
*	@author Robert Goss
*	@date 2-12-18
*	@brief Header file for TimeSlots class, a class that holds time slots that an event occupies
*/

class TimeSlots
{
	public:
		TimeSlots(std::string n, int t);
		getNameOfEvent();
		getTime();
		setAvailablity(std::string name);

	
	private:
		std::string nameOfEvent = "";
		int time = 0;
		int size = 10;
		std::string availableNames[size];
		

};

