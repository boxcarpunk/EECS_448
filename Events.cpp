#include "Events.h"

const std::string Events::holidays[3] = { "01/01", "07/4","12/25" };

Events::Events()
{
	m_name = ""; //sets the name to the empty string
	m_TimeSlot = new LinkedList<TimeSlots, TimeSlots>(); //creates a linked list of time slots
	m_Task = new LinkedList<Task, std::string>(); //creates a linked list of tasks
}

Events::Events(std::string name, int numOfDays, TimeSlots** times)
{
	//std::string date = month + "/" + day + "/" + year;

	m_TimeSlot = new LinkedList<TimeSlots, TimeSlots>(); //creates a linked list of time slots

	m_numOfDays = numOfDays;
	m_name = name;
	timeSlot = times;
	m_Task = new LinkedList<Task, std::string>(); //creates a linked list of tasks

}

Events::~Events()
{
	delete m_TimeSlot;
	delete m_Task;
}

void Events::setName(std::string name)
{
	m_name = name; //sets the name to what was passed in
}

void Events::setNumOfDays(int num)
{
	m_numOfDays = num;
}

void Events::setDates(std::string date)
{
	m_dates.push_back(date); //sets the month to what was passed in
}

std::string Events::getName() const
{
	return m_name; //returns the name of the event
}

int Events::getNumOfDays()
{
	return m_numOfDays;
}

std::vector<std::string> Events::getDates() const
{
	return m_dates; //returns the month of the event
}


LinkedList<TimeSlots, TimeSlots>* Events::getTimeSlots() const
{
	return m_TimeSlot; //returns the linked list of time slots
}

void Events::getInfo()
{
	std::string year, month, day;
	std::cout << "\n" << m_name << " is occuring on ";
	for (int i = 0; i < m_numOfDays; i++)
	{
		std::string date = m_dates[i];
		day = date.substr(0, 2);
		month = date.substr(3, 2);
		year = date.substr(6, 4);
		std::cout << month << "/" << day << "/" << year << ".\n"; //prints the name and date of the event

		for (int j = 0; j < 54; j++)
		{
			std::cout << timeSlot[i][j].getNum();
			if (timeSlot[i][j].getNum() != 0)
			{
				std::vector<std::string> names;
				for (int k = 0; k < timeSlot[i][j].getNum(); k++)
				{
					timeSlot[i][j].getAttendees();
					names = timeSlot[i][j].getAttendees();
					for (int l = 0; l < names.size(); l++)
					{
						std::cout << names[l];
					}
				}
			}
		}
	}
	//TODO change to include all dates AND users and their available times



	/*for (int i=1; i == m_TimeSlot->getLength(); i++) //goes through the linked list of time slots
	{
		std::cout << "There are " << m_TimeSlot->getEntry(i).getNum() << " people available at " << m_TimeSlot->getEntry(i).getTimeSlot() << ".\n"; //prints the number of attendees for each relevant time slot
	}*/
}

void Events::addTimeSlots(int s_t, int numOfAtt)
{
	TimeSlots newSlot(numOfAtt, s_t); // instantiate new time slot
	m_TimeSlot->addBack(newSlot); // add new time slot to end of linked list
	m_TimeSlot->sort(); //sort the list
}


void Events::setTimes(TimeSlots** times)
{
	for (int i = 0; i < m_numOfDays; i++)
	{
		for (int j = 0; j < 54; j++)
		{
			timeSlot[i][j] = times[i][j];
		}
	}
}

TimeSlots ** Events::getTimes()
{
	return timeSlot;
}

void Events::addTask(std::string name)
{
	m_Task->addFront(Task(name)); //makes a new task with the given name and adds it to the front of the list
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

LinkedList<Task, std::string>* Events::getTasks()
{
	return(m_Task); //returns the list of tasks
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

	return((m_name == rhs.m_name) && (year == rhsYear) && (month == rhsMonth) && (day == rhsDay)); //returns true if the name, year, month, and day are the same
}

bool Events::operator==(const std::string& rhs) const
{
	return(m_name == rhs); //returns true of the string is equal to the name of the event
}

bool Events::operator>(const Events& rhs) const
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
