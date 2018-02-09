#include "TimeSlots.h"

TimeSlots::TimeSlots(std::string n, int t)
{
	nameOfEvent = n;
	time = t;
	for (int i=0; i<size; i++)
	{
		availableNames[i] = "";
	}
}

TimeSlots::getTime()
{
	return time;
}

TimeSlots::getNameOfEvent()
{
	return nameOfEvent;
}

TimeSlots::setAvailability(std::string name)
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