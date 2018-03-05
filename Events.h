#pragma once
#include <string>
#include <vector>
#include "LinkedList.h"
#include "TimeSlots.h"
#include "Task.h"

class Events
{
public:

	/**
	*	Creates an event with default values. Note: Should never be used
	*	@pre None
	*	@post Assigns member variables a default value and creates an event
	*	@param None
	*	@return None
	*/
	Events();

	/**
	*	Creates an event with the values passed in
	*	@pre None
	*	@post Assigns member variables the corresponding values passed in and creates an event
	*	@param A string representing the name, an int representing the number of days, and a vector of dates for the event
	*	@return None
	*/
	Events(std::string name, int numOfDays, std::vector<std::string> dates);

	/**
	*	Destructor deletes the linked lists
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
<<<<<<< HEAD
	~Events();
=======
	//~Events();
>>>>>>> Event/Availability

	/**
	*	Sets the name of the event
	*	@pre None
	*	@post The name of the event is equal to the name passed in
	*	@param String representing the name of an event
	*	@return None
	*/
	void setName(std::string name);

	/**
	*	Returns the name of the event
	*	@pre None
	*	@post None
	*	@param None
	*	@return A string representing the name of the event
	*/
	std::string getName() const;

	/**
	*	Returns the number of days the event will occur
	*	@pre None
	*	@post None
	*	@param None
	*	@return An int representing the number of days the event will occur
	*/
	int getNumOfDays() const;

	/**
	*	The list of days the event will occur on will be returned
	*	@pre None
	*	@post None
	*	@param None
	*	@return A vector containing the list of dates the event will occur on in MM/DD/YYYY format
	*/
	std::vector<std::string> getDates() const;

	/**
	*	The 2D array of time slots will be returned. The first index refers to the day of the event and the second index refers to the 20min time slot for that day
	*	@pre None
	*	@post None
	*	@param None
	*	@return A 2D array of time slots for the event
	*/
	TimeSlots** getTimes() const;

	/**
	*	The 2D array of time slots will be set. The first index refers to the day of the event and the second index refers to the 20min time slot for that day
	*	@pre None
	*	@post None
	*	@param A 2D array of time slots
	*	@return None
	*/
	void setTimes(TimeSlots**);

	/**
	*	Adds a task to the list of tasks for the event
	*	@pre None
	*	@post New Task object added to m_Task list for the event
	*	@param The name of the task to be added
	*	@return None
	*/
	void addTask(std::string name);

	/**
	*	Allows a user to sign up for a task
	*	@pre There is an unhandled task in the list with the given name
	*	@post The task is handled
	*	@param The name of the task to be handled and the person handling it
	*	@return True if the person could sign up for the task, false otherwise
	*/
	bool signUpTask(std::string userName, std::string taskName);

	/**
	*	Allows a user to un-sign up for a task
	*	@pre The user is handling the task
	*	@post The user is no longer handling the task
	*	@param The name of the task to be un-handled and the name of the person trying to un-sign up
	*	@return True if the person could un-sign up, false otherwise
	*/
	bool cancelSignUpTask(std::string userName, std::string taskName);

	/**
	*	Gets the task list
	*	@pre None
	*	@post None
	*	@param None
	*	@return A vector with the task list for the event
	*/
	std::vector<Task> getTasks();

	/**
	*	Operator overload for == between two events, checks the name and dates of the events
	*	@pre None
	*	@post None
	*	@param The event to be compared to this one
	*	@return True if the name and dates of the events are the same, false otherwise
	*/
	bool operator==(const Events& rhs) const;

	/**
	*	Operator overload for == between an event and a string, checks the string against the event's name
	*	@pre None
	*	@post None
	*	@param A string to be compared to the event's name
	*	@return True if the string is equal to the name of the event, false otherwise
	*/
	bool operator==(const std::string& rhs) const;

	/**
	*	Operator overload for > between two events, checks the starting date of the events
	*	@pre None
	*	@post None
	*	@param The event to be compared to this one
	*	@return True if the starting date of the current event is after the event passed in, false otherwise
	*/
	bool operator>(const Events& rhs) const;

private:
	std::string m_name; /**< The name of the Event */
	int m_numOfDays; /**< The number of days the event will occur */
	std::vector<std::string> m_dates; /**< The actual dates that the event will occur */
	TimeSlots** timeSlot; /**< The time slots for the event, the first index cooresponds to the day and the second index cooresponds to the actual time slot */
	LinkedList<Task, std::string>* m_Task; /**< The list of tasks for the event */
};
