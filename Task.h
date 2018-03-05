#pragma once
#include <string>

class Task
{
public:

	/**
	*	Creates a task with default values
	*	@pre None
	*	@post Creates a task with default values
	*	@param None
	*	@return None
	*/
	Task();

	/**
	*	Creates a task with the given name
	*	@pre None
	*	@post Creates a task with the given name
	*	@param The name of the task being created
	*	@return None
	*/
	Task(std::string name);

	Task(const Task& oldTask);

	/**
	*	Allows someone to sign up to handle the task
	*	@pre The task is not being handled already
	*	@post The task is being handled
	*	@param The name of the person signing up to handle the task
	*	@return True if the person was able to sign up for the task, false otherwise
	*/
	bool signUp(std::string name);

	/**
	*	Allows someone to un-sign up for the task 
	*	@pre The task is being handled
	*	@post The task is not being handled
	*	@param None
	*	@return True if the person was able to un-sign up for the task, false otherwise
	*/
	bool cancelSignUp();

	/**
	*	Returns the variable m_handled
	*	@pre None
	*	@post None
	*	@param None
	*	@return True if the task is handled, false if it isn't
	*/
	bool isHandled();

	/**
	*	Returns the variable m_taskName
	*	@pre None
	*	@post None
	*	@param None
	*	@return The name of the task
	*/
	std::string getTaskName();

	/**
	*	Returns the variable m_personName
	*	@pre None
	*	@post None
	*	@param None
	*	@return The name of the person handling the task
	*/
	std::string getPersonName();

	/**
	*	Operator overload for Task == Task
	*	@pre None
	*	@post None
	*	@param The task to compare to this one
	*	@return True if the member variables are the equal, false otherwise
	*/
	bool operator==(const Task& rhs);

	/**
	*	Operator overload for Task > Task
	*	@pre None
	*	@post None
	*	@param The task to compare to this one
	*	@return True if the task name is greater than the name of the task passed in, false otherwise
	*/
	bool operator>(const Task& rhs);

	/**
	*	Operator overload for Task == string
	*	@pre None
	*	@post None
	*	@param The string to compare to the task's name
	*	@return True if the string is equal to the task's name, false otherwise
	*/
	bool operator==(const std::string& rhs);

	Task& operator=(const Task& rhs);

private:
	std::string m_taskName; /**< name of the task */
	std::string m_personName; /**< name of the person handling the task */
	bool m_handled; /**< whether the task is being handled or not */
};
