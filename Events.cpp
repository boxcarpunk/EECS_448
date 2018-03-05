#include "Events.h"
#include <iostream>

Events::Events()
{
	m_eventName = "None"; //sets the name of the event to None
	m_adminName = "None"; //sets the name of the admin to None
	m_numOfDays = 0; //sets the number of days for the event to 0
}

Events::Events(std::string name,std::string adminName, int numOfDays, TimeSlots** times)
{
	//std::string date = month + "/" + day + "/" + year;

	m_TimeSlot = new LinkedList<TimeSlots, TimeSlots>(); //creates a linked list of time slots
	m_numOfDays = numOfDays;
	m_eventName = name;
	timeSlot = times;
}



/*Events::~Events()
{
	delete m_TimeSlot;
}*/

void Events::setEventName(std::string name)
{
	m_eventName = name; //sets the name to what was passed in
}

std::string Events::getEventName() const
{
	return m_eventName; //returns the name of the event
}

std::string Events::getAdminName() const
{
	return m_adminName; //returns the name of the admin
}

int Events::getNumOfDays() const
{
	return m_numOfDays; //returns the number of days the event will occur
}

std::vector<std::string> Events::getDates() const
{
	return m_dates; //returns the list of days the event will occur on
}

LinkedList<TimeSlots, TimeSlots>* Events::getTimeSlots() const
{
	return m_TimeSlot; //returns the linked list of time slots
}

void Events::setDates(std::string date)
{
	m_dates.push_back(date); //sets the month to what was passed in
}

void Events::getInfo()
{
	std::string year, month, day;
	std::string myArray[54] = { "5:00 - 5:20 AM", "5:20 - 5:40 AM", "5:40 - 6:00 AM",  "6:00 - 6:20 AM", "6:20 - 6:40 AM", "6:40 - 7:00 AM",  "7:00 - 7:20 AM", "7:20 - 7:40 AM", "7:40 - 8:00 AM",  "8:00 - 8:20 AM", "8:20 - 8:40 AM", "8:40 - 9:00 AM",  "9:00 - 9:20 AM", "9:20 - 9:40 AM", "9:40 - 10:00 AM",  "10:00 - 10:20 AM", "10:20 - 10:40 AM", "10:40 - 11:00 AM",  "11:00 - 11:20 AM", "11:20 - 11:40 AM", "11:40 - 12:00 AM",  "1:00 - 1:20 PM", "1:20 - 1:40 PM", "1:40 - 2:00 PM",  "2:00 - 2:20 PM", "2:20 - 2:40 PM", "2:40 - 3:00 PM",  "3:00 - 3:20 PM", "3:20 - 3:40 PM", "3:40 - 4:00 PM",  "4:00 - 4:20 PM", "4:20 - 4:40 PM", "4:40 - 5:00 PM",  "5:00 - 5:20 PM", "5:20 - 5:40 PM", "5:40 - 6:00 PM",  "6:00 - 6:20 PM", "6:20 - 6:40 PM", "6:40 - 7:00 PM",  "7:00 - 7:20 PM", "7:20 - 7:40 PM", "7:40 - 8:00 PM",  "8:00 - 8:20 PM", "8:20 - 8:40 PM", "8:40 - 9:00 PM",  "9:00 - 9:20 PM", "9:20 - 9:40 PM", "9:40 - 10:00 PM",  "10:00 - 10:20 PM", "10:20 - 10:40 PM", "10:40 - 11:00 PM",  "11:00 - 11:20 PM", "11:20 - 11:40 PM", "11:40 PM - 12:00 AM" };
	std::cout << "\n" << m_eventName << " is occuring on ";
	for (int i = 0; i < m_numOfDays; i++)
	{
		std::string date = m_dates[i];
		day = date.substr(0, 2);
		month = date.substr(3, 2);
		year = date.substr(6, 4);
		std::cout << "\nDay #" << i+1 << " " << month << "/" << day << "/" << year; //prints the name and date of the event
		std::cout << "\n----------------\n" << std::endl; //prints the name and date of the event

		for (int j = 0; j < 54; j++)
		{
			if (timeSlot[i][j].getNum() != 0)
			{
				std::cout << "At " << myArray[j] << ", the following people are attending:";
				std::vector<std::string> names;

				names = timeSlot[i][j].getAttendees();
				for (int l = 0; l < names.size(); l++)
				{
					std::cout << names[l] <<", ";
				}
				std::cout << std::endl;
			}
		}
	}

	std::cout << "\nTasks\n";
	std::cout << "-----\n\n";
	for (int i = 0; i < m_Task.size(); i++)
	{
		std::cout << i+1 << ") " << m_Task[i].getTaskName() << " is being handled by " << m_Task[i].getPersonName() << std::endl;
	}
}

/*void Events::removeDate(int index)
{
	if((index >=0) && (index < m_dates.size())) //if the index is valid
	{
		m_dates.erase(m_dates.begin()+index); //erases the date at the given index
		m_numOfDays--; //decrements the number of days the event will occur
		TimeSlots** temp = new TimeSlots*[m_numOfDays]; //makes a new time slot 2D array of the new size
		
		for(int i = 0; i < m_numOfDays; i++) //iterates through the days of the event
		{
			temp[i] = new TimeSlots[54]; //makes the 20min time slots for the date
		
			if(i < index) //if the current date is less than the removed index
			{
				for(int j =0; j < 54; j++) //iterates through the time slots
				{
					temp[i][j] = timeSlot[i][j]; //makes the new time slot equal to the old one
				}
			}
			else //if the current date is equal to or greater than the removed index
			{
				for(int j =0; j < 54; j++) //iterates through the time slots
				{
					temp[i][j] = timeSlot[i+1][j]; //makes the new time slot equal to the old one accounting for the removed index
				}
			}
		}
		
		for(int i = 0; i < m_numOfDays+1; i++) //runs through the old dates
		{
			delete[] timeSlot[i]; //deletes the old time slots
		}
		
		delete[] timeSlot; //deletes the old dates
		
		timeSlot = temp; //makes the time slot 2D array equal to the temp one
	}
}*/

/*void Events::addDate(std::string date)
{
	m_dates.push_back(date); //adds the date to the back of the date vector
	m_numOfDays++; //increments the number of days the event will occur
	TimeSlots** temp = new TimeSlots*[m_numOfDays]; //makes a new time slot 2D array of the new size
		
		for(int i = 0; i < m_numOfDays; i++) //iterates through the days of the event
		{
			temp[i] = new TimeSlots[54]; //makes the 20min time slots for the date
		
			if(i < (m_numOfDays-1)) //if the current date is part of the old dates
			{
				for(int j =0; j < 54; j++) //iterates through the time slots
				{
					temp[i][j] = timeSlot[i][j]; //makes the new time slot equal to the old one
				}
			}
		}
		
		for(int i = 0; i < m_numOfDays-1; i++) //runs through the old dates
		{
			delete[] timeSlot[i]; //deletes the old time slots
		}
		
		delete[] timeSlot; //deletes the old dates
		
		timeSlot = temp; //makes the time slot 2D array equal to the temp one
}*/


std::string Events::getName() const
{
	return m_eventName; //returns the name of the event
}

TimeSlots ** Events::getTimes() const
{
	return timeSlot;
}

void Events::setTimes(TimeSlots** times)
{
	for (int i = 0; i < m_numOfDays; i++) //runs through the first index of the 2D array (the days of the event)
	{
		for (int j = 0; j < 54; j++) //runs through the second index of the 2D array (the 20min time slots for the given day)
		{
			timeSlot[i][j] = times[i][j]; //makes the time slots equal
		}
	}
}

void Events::addTask(std::string name)
{
	for(int i = 0; i < m_Task.size(); i++) //runs through the task list
	{
		if(m_Task[i] == name) //if the task is already in the list
		{
			return; //we don't want to add the same task twice
		}
	}

	Task* newTask = new Task(name);
	m_Task.push_back(*newTask); //makes a new task with the given name and adds it to the back of the list
}

void Events::removeTask(int index)
{
	if((index >=0) && (index < m_Task.size())) //if the index is valid
	{
		m_Task.erase(m_Task.begin()+index); //removes the task at the given index
	}
}

bool Events::signUpTask(std::string userName, std::string taskName)
{
	int temp; //creates a temp task
	bool found = false; //a flag to state whether the task was found or not

	for(int i = 0; i < m_Task.size(); i++) //runs through the task list
	{
		if(m_Task[i] == taskName) //if the task is found
		{
			temp = i; //stores the task in temp
			found = true; //set the flag to true since the task was found
		}
	}
	
	if(!found) //if the task was not found
	{
		return(false); //return false
	}

	return(m_Task[temp].signUp(userName)); //passes along the name of the user to the task and returns whether they were able to sign up or not
}

bool Events::cancelSignUpTask(std::string userName, std::string taskName)
{
	Task temp; //creates a temp task
	bool found = false; //a flag to state whether the task was found or not
	
	for(int i = 0; i < m_Task.size(); i++) //runs through the task list
	{
		if(m_Task[i] == taskName) //if the task is found
		{
			temp = m_Task[i]; //stores the task in temp
			found = true; //set the flag to true since the task was found
		}
	}
	
	if(!found) //if the task was not found
	{
		return(false); //return false
	}

	if (userName == temp.getPersonName()) //if the name of the user trying to un-sign up is the same as the user who is handling the task
	{
		return(temp.cancelSignUp()); //returns whether the user was able to un-sign up or not
	}
	else //if the user is not the person who is handling the task
	{
		return(false); //you can't un-sign up someone else from a task
	}
}

std::vector<Task> Events::getTasks()
{
	return(m_Task); //returns the vector
}

bool Events::operator==(const Events& rhs) const
{
	std::string rhsYear, rhsMonth, rhsDay, rhsDate;
	rhsDate = rhs.getDates()[0];
	rhsDay = rhsDate.substr(0, 2);
	rhsMonth = rhsDate.substr(3, 2);
	rhsYear = rhsDate.substr(6, 10);

	std::string year, month, day;
	std::string date = m_dates[0];
	day = date.substr(0, 2);
	month = date.substr(3, 2);
	year = date.substr(6, 10);

	return((m_eventName == rhs.m_eventName) && (year == rhsYear) && (month == rhsMonth) && (day == rhsDay)); //returns true if the name, year, month, and day are the same
}

Events& Events::operator<<(Events & rhs)
{
	return(rhs);
}

bool Events::operator==(const std::string& rhs) const
{
	return(m_eventName == rhs); //returns true of the string is equal to the name of the event
}

bool Events::operator>(const Events& rhs) const
{
	std::string rhsYear, rhsMonth, rhsDay, rhsDate; //creates variables to store the starting date of the event passed in
	rhsDate = rhs.getDates()[0]; //gets the starting date of the eveent passed in
	rhsMonth = rhsDate.substr(0, 2); //gets the month of the starting date of the event passed in
	rhsDay = rhsDate.substr(3, 2); //gets the day of the starting date of the event passed in
	rhsYear = rhsDate.substr(6, 4); //gets the year of the starting date of the event passed in

	std::string year, month, day; //creates variables to store the starting date of this event
	std::string date = m_dates[0]; //gets the starting date of this event
	month = date.substr(0, 2); //gets the starting month of this event
	day = date.substr(3, 2); //gets the starting day of this event
	year = date.substr(6, 4); //gets the starting year of this event

	if (year > rhsYear) //if the current event is at a later year
	{
		return(true); //returns true because the current event is after the event passed in
	}
	else if (year == rhsYear) //if they occur on the same year
	{
		if (month > rhsMonth) //if the current event is at a later month in the same year
		{
			return(true); //returns true because the current event is after the event passed in
		}
		else if (month == rhsMonth) //if they occur on the same month and year
		{
			if (day > rhsDay) //if the current event is at a later day in the same month
			{
				return(true); //returns true because the current event is after the event passed in
			}
		}
	}

	return(false); //returns false if not one of the cases covered above
}
