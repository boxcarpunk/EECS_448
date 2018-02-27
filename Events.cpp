#include "Events.h"

const std::string Events::holidays[3] = { "01/01", "07/4","12/25" };

Events::Events()
{
	m_name = ""; //sets the name to the empty string
	m_month = 0; //sets the month to 0
	m_day = 0; //sets the day to 0
	m_year = 0; //sets the year to 0
	m_TimeSlot = new LinkedList<TimeSlots, TimeSlots>(); //creates a linked list of time slots
	m_Task = new LinkedList<Task, Task>(); //creates a linked list of tasks
}

Events::Events(std::string name, int month, int day, int year)
{
	m_name = name; //sets the name to what was passed in
	m_month = month; //sets the month to what was passed in
	m_day = day; //sets the day to what was passed in
	m_year = year; //sets the year to what was passed in
	m_TimeSlot = new LinkedList<TimeSlots, TimeSlots>(); //creates a linked list of time slots
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

void Events::setMonth(int month)
{
	m_month = month; //sets the month to what was passed in
}

void Events::setDay(int day)
{
	m_day = day; //sets the day to what was passed in
}

void Events::setYear(int year)
{
	m_year = year; //sets the year to what was passed in
}

std::string Events::getName() const
{
	return m_name; //returns the name of the event
}

int Events::getMonth() const
{
	return m_month; //returns the month of the event
}

int Events::getDay() const
{
	return m_day; //returns the day of the event
}

int Events::getYear() const
{
	return m_year; //returns the year of the event
}

LinkedList<TimeSlots, TimeSlots>* Events::getTimeSlots() const
{
	return m_TimeSlot; //returns the linked list of time slots
}

void Events::getInfo()
{
	std::cout << "\n" << m_name << " is occuring on " << m_month << "/" << m_day << "/" << m_year << ".\n"; //prints the name and date of the event
	for (int i=1; i == m_TimeSlot->getLength(); i++) //goes through the linked list of time slots
	{
		std::cout << "There are " << m_TimeSlot->getEntry(i).getNum() << " people available at " << m_TimeSlot->getEntry(i).getTimeSlot() << ".\n"; //prints the number of attendees for each relevant time slot
	}
}

void Events::addTimeSlots(int s_t, int numOfAtt)
{
	TimeSlots newSlot(numOfAtt, s_t); // instantiate new time slot
	m_TimeSlot->addBack(newSlot); // add new time slot to end of linked list
	m_TimeSlot->sort(); //sort the list
}

void Events::addTask(std::string name)
{
	m_Task->addFront(new Task(name)); //makes a new task with the given name and adds it to the front of the list
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
	return((m_name == rhs.m_name) && (m_year == rhs.m_year) && (m_month == rhs.m_month) && (m_day == rhs.m_day)); //returns true if the name, year, month, and day are the same
}

bool Events::operator==(const std::string& rhs) const
{
	return(m_name == rhs); //returns true of the string is equal to the name of the event
}

bool Events::operator>(const Events& rhs) const
{
	if (m_year > rhs.m_year) //if the current event is at a later year
	{
		return(true); //returns true because the current event is after the event passed in
	}
	else if (m_year == rhs.m_year) //if they occur on the same year
	{
		if (m_month > rhs.m_month) //if the current event is at a later month in the same year
		{
			return(true); //returns true because the current event is after the event passed in
		}
		else if (m_month == rhs.m_month) //if they occur on the same month and year
		{
			if (m_day > rhs.m_day) //if the current event is at a later day in the same month
			{
				return(true); //returns true because the current event is after the event passed in
			}
		}
	}

	return(false); //returns false if not one of the cases covered above
}
