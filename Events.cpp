/**
* @author Robert Goss
* @cal448
* @date 12 February 2017
* @brief Events class implementation
* @file Events.cpp **/

#include "Events.h"

Events::Events()
{
	// initialize variables to "" for strings, 0 for ints
	//timeSlots = new TimeSlots[72];
	m_name = "";
	m_month = 0;
	m_day = 0;
	m_year = 0;
	m_TimeSlot = new LinkedList<TimeSlots>();
}

Events::Events(std::string name, int month, int day, int year)
{
	m_name = name;
	m_month = month;
	m_day = day;
	m_year = year;
	m_TimeSlot = new LinkedList<TimeSlots>();
}

Events::~Events()
{
	; // empty destructor
}

bool Events::operator>(const Events& rhs) const
{
	// if year on left is greater, then left event starts later. return true
	if (m_year > rhs.getYear())
	{
		return true;
	}
	// if year on left is less than, then right event starts later. return false
	else if (m_year < rhs.getYear())
	{
		return false;
	}
	// else, both events occur in the same year.  Start next set of if-else statements to test for months
	else
	{
		// if month on left is greater, then left event starts later. return true
		if (m_month > rhs.getMonth())
		{
			return true;
		}
		// if month on left is less than, then right event starts later. return false
		else if (m_month < rhs.getMonth())
		{
			return false;
		}
		// else, both events occur in the same month. Start next set of if-else statements to test for days
		else
		{
			// if day on left is greater, then left event starts later. return true
			if (m_day > rhs.getDay())
			{
				return true;
			}
			// if day on right is greater, then right event starts later. return false
			else if (m_day < rhs.getDay())
			{
				return false;
			}
			// else, both events occur on the same day. Start next set of if-else statements to test for timeslots
			else
			{
				// compare the start time of the event on the left side to the start time of the event on the right side.
				// If the start time on the left is greater than the start time on the right, then it is the later event,
				// and thus the > operation is true
				/*if ((m_TimeSlot->getEntry(1)->getTimeSlot()) > (rhs->getTimeSlots()->getEntry(1)->getTimeslot()))
				{
					return true;
				}
				// If the start time on the left is less than the start time on the right, then it is not the later event,
				// and thus the > operation is false
				else if ((m_Timeslot->getEntry(1)->getTimeslot()) < (rhs->getTimeSlots()->getEntry(1)->getTimeslot()))
				{
					return false;
				}
				// else, these events start at the same time. return false for now, need to discuss this with group before moving forward
				else
				{
					return false;
				}*/
			}
		}
	}
}

bool Events::operator<(const Events& rhs) const
{
	// if year on left is less than, then right event starts later. return true
	if (m_year < rhs.getYear())
	{
		return true;
	}
	// if year on left is greater, then left event starts later. return false
	else if (m_year > rhs.getYear())
	{
		return false;
	}
	// else, both events occur in the same year.  Start next set of if-else statements to test for months
	else
	{
		// if month on left is less than, then right event starts later. return true
		if (m_month < rhs.getMonth())
		{
			return true;
		}
		// if month on left is greater, then left event starts later. return false
		else if (m_month > rhs.getMonth())
		{
			return false;
		}
		// else, both events occur in the same month. Start next set of if-else statements to test for days
		else
		{
			// if day on left is less than, then right event starts later. return true
			if (m_day < rhs.getDay())
			{
				return true;
			}
			// if day on left is greater, then left event starts later. return false
			else if (m_day > rhs.getDay())
			{
				return false;
			}
			// else, both events occur on the same day. Start next set of if-else statements to test for timeslots
			else
			{
				// compare the start time of the event on the left side to the start time of the event on the right side.
				// If the start time on the left is less than to the start time on the right, then the right is the later event,
				// and thus the < operation is true
				/*if ((m_Timeslot->getEntry(1)->getTimeslot()) < (rhs->getTimeSlots()->getEntry(1)->getTimeslot()))
				{
					return true;
				}
				// If the start time on the left is greater than the start time on the right, then it is the later event,
				// and thus the < operation is false
				else if ((m_Timeslot->getEntry(1)->getTimeslot()) > (rhs->getTimeSlots()->getEntry(1)->getTimeslot()))
				{
					return false;
				}
				// else, these events start at the same time. return false for now, need to discuss this with group before moving forward
				else
				{
					return false;
				}*/
			}
		}
	}
}

bool Events::operator==(const Events& rhs) const
{
	// test to see if years are equal
	if (m_year == rhs.getYear())
	{
		// if years are equal, test for months
		if (m_month == rhs.getMonth())
		{
			// if months are equal, test for days
			if (m_day == rhs.getDay())
			{
				// if days are equal, test for start times
				/*if ((m_Timeslot->getEntry(1)->getTimeslot()) == (rhs->getTimeSlots()->getEntry(1)->getTimeslot()))
				{
					// start times are equal, return true
					return true;
				}
				else
				{
					// start times are not equal, return false
					return false;
				}*/
			}
			// days are not equal, return false
			else
			{
				return false;
			}
		}
		// months are not equal, return false
		else
		{
			return false;
		}
	}
	// years are not equal, return false
	else
	{
		return false;
	}
}

void Events::setName(std::string name)
{
	m_name = name; // set name
}

void Events::setMonth(int month)
{
	m_month = month; //set month
}

void Events::setDay(int day)
{
	m_day = day; // set day
}

void Events::setYear(int year)
{
	m_year = year; // set year
}

std::string Events::getName() const
{
	return m_name; // return name of event
}

int Events::getMonth() const
{
	return m_month; ///return month
}

int Events::getDay() const
{
	return m_day; //return day
}

int Events::getYear() const
{
	return m_year; // return year
}

LinkedList<TimeSlots>* Events::getTimeSlots() const
{
	return m_TimeSlot; // return m_TimeSlot
}

void Events::getInfo()
{
	// output info for this event to std::cout
	std::cout << "\n" << m_name << " is occuring on " << m_month << "/" << m_day << "/" << m_year << ".\n";
	for (int i=0; i<m_TimeSlot()->getLength(); i++)
	{
		std::cout << "There are " << m_TimeSlot->getEntry(i)->getNum() << " people available at " << m_TimeSlot()->getEntry(i)->getTimeSlot() << ".\n";
	}
}

void Events::addTimeSlots(int s_t, int numOfAtt)
{
	TimeSlots newSlot(numOfAtt, s_t); // instantiate new time slot
	m_TimeSlot->addBack(newSlot); // add new time slot to end of linked list
	m_TimeSlot->sortListTime(); // call sort list method to ensure that list is sorted after insertion of new time slot
}
