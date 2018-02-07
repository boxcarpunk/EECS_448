#include "Events.h"

Events::Events()
{
	// initialize variables to "" for strings, 0 for ints, false for bools
	eventName = "";
	
	numOfUsers = 0;

	startOfEvent.tm_sec = 0;
	startOfEvent.tm_min = 0;
	startOfEvent.tm_hour = 0;
	startOfEvent.tm_mday = 0;
	startOfEvent.tm_mon = 0;
	startOfEvent.tm_year = 0;
	startOfEvent.tm_wday = 0;
	startOfEvent.tm_yday = 0;
	startOfEvent.tm_isdst = 0;

	endOfEvent.tm_sec = 0;
	endOfEvent.tm_min = 0;
	endOfEvent.tm_hour = 0;
	endOfEvent.tm_mday = 0;
	endOfEvent.tm_mon = 0;
	endOfEvent.tm_year = 0;
	endOfEvent.tm_wday = 0;
	endOfEvent.tm_yday = 0;
	endOfEvent.tm_isdst = 0;

	for (int i = 0; i < 72; i++)
	{
		timeSlots[i] = false;
	}
}

Events::Events(const Events& object)
{
	// copy event name
	eventName = object.eventName;

	// copy numOffUsers
	numOfUsers = object.numOfUsers;

	// copy time variables
	startOfEvent.tm_sec = object.startOfEvent.tm_sec;
	startOfEvent.tm_min = object.startOfEvent.tm_min;
	startOfEvent.tm_hour = object.startOfEvent.tm_hour;
	startOfEvent.tm_mday = object.startOfEvent.tm_mday;
	startOfEvent.tm_mon = object.startOfEvent.tm_mon;
	startOfEvent.tm_year = object.startOfEvent.tm_year;
	startOfEvent.tm_wday = object.startOfEvent.tm_wday;
	startOfEvent.tm_yday = object.startOfEvent.tm_yday;
	startOfEvent.tm_isdst = object.startOfEvent.tm_isdst;

	endOfEvent.tm_sec = object.endOfEvent.tm_sec;
	endOfEvent.tm_min = object.endOfEvent.tm_min;
	endOfEvent.tm_hour = object.endOfEvent.tm_hour;
	endOfEvent.tm_mday = object.endOfEvent.tm_mday;
	endOfEvent.tm_mon = object.endOfEvent.tm_mon;
	endOfEvent.tm_year = object.endOfEvent.tm_year;
	endOfEvent.tm_wday = object.endOfEvent.tm_wday;
	endOfEvent.tm_yday = object.endOfEvent.tm_yday;
	endOfEvent.tm_isdst = object.endOfEvent.tm_isdst;

	// copy time slots
	for (int i = 0; i < 72; i++)
	{
		timeSlots[i] = object.timeSlots[i];
	}
}

void Events::operator=(const Events& rhs)
{
	// copy event name
	eventName = rhs.eventName;

	// copy numOffUsers
	numOfUsers = rhs.numOfUsers;

	// copy time variables
	startOfEvent.tm_sec = rhs.startOfEvent.tm_sec;
	startOfEvent.tm_min = rhs.startOfEvent.tm_min;
	startOfEvent.tm_hour = rhs.startOfEvent.tm_hour;
	startOfEvent.tm_mday = rhs.startOfEvent.tm_mday;
	startOfEvent.tm_mon = rhs.startOfEvent.tm_mon;
	startOfEvent.tm_year = rhs.startOfEvent.tm_year;
	startOfEvent.tm_wday = rhs.startOfEvent.tm_wday;
	startOfEvent.tm_yday = rhs.startOfEvent.tm_yday;
	startOfEvent.tm_isdst = rhs.startOfEvent.tm_isdst;

	endOfEvent.tm_sec = rhs.endOfEvent.tm_sec;
	endOfEvent.tm_min = rhs.endOfEvent.tm_min;
	endOfEvent.tm_hour = rhs.endOfEvent.tm_hour;
	endOfEvent.tm_mday = rhs.endOfEvent.tm_mday;
	endOfEvent.tm_mon = rhs.endOfEvent.tm_mon;
	endOfEvent.tm_year = rhs.endOfEvent.tm_year;
	endOfEvent.tm_wday = rhs.endOfEvent.tm_wday;
	endOfEvent.tm_yday = rhs.endOfEvent.tm_yday;
	endOfEvent.tm_isdst = rhs.endOfEvent.tm_isdst;

	// copy time slots
	for (int i = 0; i < 72; i++)
	{
		timeSlots[i] = rhs.timeSlots[i];
	}
}

bool Events::operator>(const Events& rhs) const
{
	if (startOfEvent.tm_year > rhs.startOfEvent.tm_year)
	{
		;
	}
	return 0;
}

bool Events::operator<(const Events& rhs) const
{
	return 0;
}

bool Events::operator==(const Events& newEvent) const
{
	return((eventName == newEvent.eventName) && (numOfUsers == newEvent.numOfUsers) && (startOfEvent.tm_sec == newEvent.startOfEvent.tm_sec)
		&& (startOfEvent.tm_min == newEvent.startOfEvent.tm_min) && (startOfEvent.tm_hour == newEvent.startOfEvent.tm_hour) && (startOfEvent.tm_mday == newEvent.startOfEvent.tm_mday)
		&& (startOfEvent.tm_mon == newEvent.startOfEvent.tm_mon) && (startOfEvent.tm_year == newEvent.startOfEvent.tm_year) && (startOfEvent.tm_wday == newEvent.startOfEvent.tm_wday)
		&& (startOfEvent.tm_yday == newEvent.startOfEvent.tm_yday) && (startOfEvent.tm_isdst == newEvent.startOfEvent.tm_isdst));
}

void Events::setEventName(std::string n)
{
	eventName = n;
}

void Events::setNumOfUsers(int n)
{
	numOfUsers = n;
}

void Events::setStartTime(int hours, int minutes, int seconds, int month, int day, int year)
{
	startOfEvent.tm_sec = seconds;
	startOfEvent.tm_min = minutes;
	startOfEvent.tm_hour = hours;
	startOfEvent.tm_mday = day;
	startOfEvent.tm_mon = month;
	startOfEvent.tm_year = year;
}

void Events::setEndTime(int hours, int minutes, int seconds, int month, int day, int year)
{
	endOfEvent.tm_sec = seconds;
	endOfEvent.tm_min = minutes;
	endOfEvent.tm_hour = hours;
	endOfEvent.tm_mday = day;
	endOfEvent.tm_mon = month;
	endOfEvent.tm_year = year;
}

std::string Events::getEventName() const
{
	return eventName;
}

int Events::getNumOfUsers() const
{
	return numOfUsers;
}

int Events::getStartHours() const
{
	return startOfEvent.tm_hour;
}

int Events::getStartMinutes() const
{
	return startOfEvent.tm_min;
}

int Events::getStartSeconds() const
{
	return startOfEvent.tm_sec;
}

int Events::getStartMonth() const
{
	return startOfEvent.tm_mon;
}

int Events::getStartDay() const
{
	return startOfEvent.tm_mday;
}

int Events::getStartYear() const
{
	return startOfEvent.tm_year;
}

int Events::getEndHours() const
{
	return endOfEvent.tm_hour;
}

int Events::getEndMinutes() const
{
	return endOfEvent.tm_min;
}

int Events::getEndSeconds() const
{
	return endOfEvent.tm_sec;
}

int Events::getEndMonth() const
{
	return endOfEvent.tm_mon;
}

int Events::getEndDay() const
{
	return endOfEvent.tm_mday;
}

int Events::getEndYear() const
{
	return endOfEvent.tm_year;
}
