#pragma once
#include <string>
#include <vector>
#include "TimeSlots.h"
#include "Task.h"
#include "LinkedList.h"

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
	*	Creates an event with default values
	*	@pre None
	*	@post Assigns member variables the corresponding value passed in and creates an event
	*	@param String for name and integers for month, day, and year
	*	@return None
	*/
	Events(std::string name,std::string adminName, int numOfDays, TimeSlots**);

	/**
	*	Destructor deletes the linked lists
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
	//~Events();

	/**
	*	Sets the name of the event
	*	@pre None
	*	@post The name of the event is equal to the name passed in
	*	@param String representing the name of an event
	*	@return None
	*/
	void setEventName(std::string name);

	/**
	*	Returns the name of the event
	*	@pre None
	*	@post None
	*	@param None
	*	@return A string representing the name of the event
	*/
	std::string getEventName() const;
	
	/**
	*	Returns the name of the admin
	*	@pre None
	*	@post None
	*	@param None
	*	@return A string representing the name of the admin
	*/
	std::string getAdminName() const;

	/**
	*	Returns the number of days the event will occur
	*	@pre None
	*	@post None
	*	@param None
	*	@return An int representing the number of days the event will occur
	*/
	int getNumOfDays() const;

	/**
	*	The name of the event being accessed is returned to the program
	*	@pre None
	*	@post The name of an event it returned
	*	@param None
	*	@return A string representing the name of the event
	*/
	std::string getName() const;

	/**
	*	The list of days the event will occur on will be returned
	*	@pre None
	*	@post None
	*	@param None
	*	@return A vector containing the list of dates the event will occur on in MM/DD/YYYY format
	*/
	std::vector<std::string> getDates() const;
	
	/**
	*	Removes a date from the event
	*	@pre A date is at the given index
	*	@post The date at the given index is removed
	*	@param An int corresponding to the index of the date to be removed, indexing starts at 0
	*	@return None
	*/
	void removeDate(int index);
	
	/**
	*	Adds a date that the event will take place
	*	@pre None
	*	@post The date is added to the event
	*	@param A string representing a date in MM/DD/YYYY format
	*	@return None
	*/
	void addDate(std::string date);

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
	*	Removes a task from the task list
	*	@pre A task exists at the given index
	*	@post The task at the given index is removed
	*	@param An int representing the index of the task to be removed
	*	@return None
	*/
	void removeTask(int index);

	/**
	*	The list of time slots for the event being accessed is returned to the program
	*	@pre None
	*	@post The list of time slots for an event it returned
	*	@param None
	*	@return Head pointer to m_TimeSlot. Specifically created for >, <, == operator overloads
	*/
	LinkedList<TimeSlots, TimeSlots>* getTimeSlots() const;

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
	*	Operator overload for == between two events, checks the event name, admin name, and dates of the events
	*	@pre None
	*	@post None
	*	@param The event to be compared to this one
	*	@return True if the names and dates of the events are the same, false otherwise
	*/
	bool operator==(const Events& rhs) const;

	/**
	*	Operator overload for == between two events, checks the event name, admin name, and dates of the events
	*	@pre None
	*	@post None
	*	@param The event to be compared to this one
	*	@return True if the names and dates of the events are the same, false otherwise
	*/
	Events& operator<<(Events& rhs);

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

	/**
	*	The information for an event is printed out so that the user can see it
	*	@pre None
	*	@post The info for an event is printed
	*	@param None
	*	@return None
	*/
	void getInfo();

	void setDates(std::string date);



private:
	std::string m_eventName; /**< The name of the event */
	std::string m_adminName; /**< The name of the admin for the event */
	
	int m_numOfDays; /**< The number of days the event will occur */
	std::vector<std::string> m_dates; /**< The actual dates that the event will occur */
	TimeSlots** timeSlot; /**< The time slots for the event, the first index cooresponds to the day and the second index cooresponds to the actual time slot */
	
	std::vector<Task> m_Task; /**< The list of tasks for the event */

	LinkedList<TimeSlots, TimeSlots>* m_TimeSlot; /**< pointer to list of time slots for this event */

};
