#include "Task.h"

Task::Task()
{
	m_taskName = "None"; //sets the name of the task to none
	m_personName = "None"; //sets the name of the person handling the task to none
	m_handled = false; //sets the task as not being handled
}

Task::Task(std::string name)
{
	m_taskName = name; //sets the name of the task to the name passed in
	m_personName = "None"; //sets the name of the person handling the task to none
	m_handled = false; //sets the task as not being handled
}

bool Task::signUp(std::string name)
{
	if (m_handled) //if the task is already being handled
	{
		return(false); //no one is allowed to sign up for a handled task
	}
	else //if the task is not being handled already
	{
		m_personName = name; //sets the name of the person handling the task to the name passed in
		m_handled = true; //sets the task as being handled
		return(true); //the person was able to sign up for the task
	}
}

bool Task::cancelSignUp()
{
	if (m_handled) //if the task is being handled already
	{
		m_personName = "None"; //sets the name of the person handling the task to none
		m_handled = false; //sets the task as not being handled
		return(true); //the person who was handling the task is no longer doing so
	}
	else //if the task is not being handled already
	{
		return(false); //you cannot un-sign up for a task that isn't being handled
	}
}

bool Task::isHandled()
{
	return(m_handled); //returns whether the task is being handled or not
}

std::string Task::getTaskName()
{
	return(m_taskName); //returns the name of the task
}

std::string Task::getPersonName()
{
	return(m_personName); //returns the name of the person handling the task
}

bool Task::operator==(const Task& rhs)
{
	return((m_taskName == rhs.m_taskName) && (m_personName == rhs.m_personName) && (m_handled == rhsm_handled)); //compares each member variable and returns them and-ed together
}

bool Task::operator>(const Task& rhs)
{
	return(m_taskName > rhs.m_taskName); //returns whether the current task's name is greater than that of the task passed in
}

bool Task::operator==(const std::string& rhs)
{
	return(m_taskName == rhs); //returns whether the task's name is equal to the string passed in
}