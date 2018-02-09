#include "TimeSlots.h"

TimeSlots::TimeSlots()
{
		bool available = true;
		std::string nameOfEvent = "";
		int time = 0;
		size = 10;
		availableNames = new std::string[size];
}

TimeSlots::TimeSlots(std::string n, int t)
{
	nameOfEvent = n;
	time = t;
	for (int i=0; i<size; i++)
	{
		availableNames[i] = "";
	}
}

int TimeSlots::getTime()
{
	return time;
}

std::string TimeSlots::getNameOfEvent()
{
	return nameOfEvent;
}

void TimeSlots::setAvailability(std::string name)
{
	for (int i=0; i<size; i++)
	{
		if (availableNames[i] == "")
		{
			availableNames[i] = name;
			break;
		}
	}
}
