#include "Events.h"

Events::Events()
{
	m_eventName = "None"; //sets the name of the event to None
	m_adminName = "None"; //sets the name of the admin to None
	m_numOfDays = 0; //sets the number of days for the event to 0

	m_Task = new LinkedList<Task, std::string>(); //creates an empty task list for the event
}

Events::Events(std::string eventName, std::string adminName, int numOfDays, std::vector<std::string> dates)
{
	m_eventName = eventName; //sets the name of the event
	m_adminName = adminName; //sets the name of the admin
	m_numOfDays = numOfDays; //sets the number of days for the event
	m_dates = dates; //sets the dates that the event will occur

	m_Task = new LinkedList<Task, std::string>(); //creates an empty task list for the event
	timeSlot = new TimeSlots*[numOfDays]; //creates time slot ptrs for each day of the event

	for (int i = 0; i < numOfDays; i++) //iterates for every day of the event
	{
		timeSlot[i] = new TimeSlots[54]; //creates an array of TimeSlots that corresponds to each possible 20min slot

		for (int j = 0; j < 54; j++) //runs through the time slot array
		{
			timeSlot[i][j].setIndex(i); //gives each time slot its index
		}
	}
}

/*Events::~Events()
{
	delete m_TimeSlot;
	delete m_Task;
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

void Events::removeDate(int index)
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
}

void Events::addDate(std::string date)
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
}

TimeSlots** Events::getTimes() const
{
	return timeSlot; //returns the 2D array of time slots
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
	m_Task->addFront(Task(name)); //makes a new task with the given name and adds it to the front of the list
}

void Events::removeTask(int index)
{
	m_Task->removeAt(index); //removes the task at the given index
}

bool Events::signUpTask(std::string userName, std::string taskName)
{
	Task temp; //creates a temp task
	try
	{
		temp = m_Task->search(taskName); //searchs for the task with the given name and stores it in temp if found
	}
	catch (std::runtime_error) //if search threw an error
	{
		return(false); //return false because the taskName passed in is not the name of a task in the list
	}

	return(temp.signUp(userName)); //passes along the name of the user to the task and returns whether they were able to sign up or not
}

bool Events::cancelSignUpTask(std::string userName, std::string taskName)
{
	Task temp; //creates a temp task
	try
	{
		temp = m_Task->search(taskName); //searchs for the task with the given name and stores it in temp if found
	}
	catch (std::runtime_error) //if search threw an error
	{
		return(false); //return false because the taskName passed in is not the name of a task in the list
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
	std::vector<Task> temp; //creates the temp vector that will be returned

	for (int i = 0; i < m_Task->getLength(); i++) //iterates through the task list
	{
		temp.push_back(m_Task->getEntry(i+1)); //adds the task at index i+1 to the vector
	}

	return(temp); //returns the vector
}

bool Events::operator==(const Events& rhs) const
{
	if (m_eventName != rhs.m_eventName)
	{
		return(false); //returns false if the names of the events are not the same
	}
	
	if (m_adminName != rhs.m_adminName)
	{
		return(false); //returns false if the names of the admins are not the same
	}

	if (m_numOfDays != rhs.m_numOfDays)
	{
		return(false); //returns false if the events do not have the same number of days
	}

	for (int i = 0; i < m_numOfDays; i ++) //runs through the days of the event
	{
		if (m_dates[i] != rhs.m_dates[i])
		{
			return(false); //returns false if the events do not occur on the same dates
		}
	}

	return(true); //if name and dates are not different then return true
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
