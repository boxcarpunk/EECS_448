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
		TimeSlots();
		TimeSlots(std::string n, int t);
		std::string getNameOfEvent();
		int getTime();
		void setAvailability(std::string name);
		bool isAvailable();

	
	private:
		bool available = false;
		std::string nameOfEvent = "";
		int time = 0;
		std::string* availableNames;
		int size;
		

};

