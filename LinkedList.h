/**
* @author Sahil Hirani
* @cal448
* @date 12 February 2017
* @brief A header file for templated LinkedList class
* @file LinkedList.h **/

/*
*	Note: Not actually a templated class, only works if T is the Event class
*	Will work to change this if time permits
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

//TODO You need to implement the Node class!
#include "Node.h"
#include <string>
#include <stdexcept>

template <typename T>
class LinkedList
{
	public:
	/**
	*	Assigns private member variables and creates an empty list
	*	@pre None
	*	@post An empty LinkedList object is created
	*	@param None
	*	@return None
	*/
	LinkedList();

	/**
	*	Each element in the list is traversed and removed until no more exist
	*	@pre  All nodes in the LinkedList object are deleted
	*	@post None
	*	@param None
	*	@return None
	*/
	~LinkedList();

	/** 
	*	Checks to see if the value associated with the private member variable 'm_length' is greater than 0. If it is, 'false' will be returned. 'true' otherwise.
	*	@pre None
	*   @post None
	*	@param None
	*   @return True if the list is empty, false otherwise.
	*/
	bool isEmpty() const;

	/** 
	*	Returns the value associated with the number of nodes that are in the list at the time called.
	*	@pre None
	*   @post None
	*	@param None
	*   @return The number of elements in the list.
	*/
	int getLength() const;

	/** 
	*	Returns the index associated with the templated value. If it does not exist in the list, the user is notified. NOTE: The range of indices is from 1 to n, where n is the number of elements in the list
	*	@pre T's type is overloaded with the '==' operator
	*   @post None
	*	@param Templated value
	*   @return Returns the index of the first node in the list that contains the value. Returns 0 otherwise.
	*/
	int positionOf(T value) const;

	/** 
	*	Add a new element to the end of the list
	*	@pre The value 'T' is valid
	*   @post A single, new element is created and added to the back of the list
	*	@param Templated value
	*   @return None
	*/
	void addBack(T value);

	/** 
	*	Adds a new element to the front of the list
	*	@pre The value 'T' is valid
	*   @post A single, new element is created and added to the front of the list
	*	@param Templated value
	*   @return None
	*/
	void addFront(T value);

	/**
	*	Returns 'true' if the value was inserted at the given position, 'false' otherwise. NOTE: The range of indices is from 1 to n, where n is the number of elements in the list
	*	@pre None
	*   @post A single, new element is created and added in the position specified
	*	@param Templated value and an integer representing the index at which the value is to be added
	*   @return True if the element was inserted false otherwise.
	*/
	bool insert(int position, T value);

	/**
	*	Returns 'true' if the element at the end of the list is removed, 'false' if the list is empty
	*	@pre None
	*   @post One element is removed from the back of the list
	*	@param None
	*   @return True if the back element was removed, false if the list is empty.
	*/
	bool removeBack();

	/**
	*	Return 'true' if the element at the front of the list is removed, 'false' if the list is empty
	*	@pre None
	*   @post One element is removed from the front of the list
	*	@param None
	*   @return True if the front element was removed, false if the list is empty.
	*/
	bool removeFront();

	/**
	*	Returns 'true' if the element at the given position is removed, 'false' otherwise. NOTE: The range of indices is from 1 to n, where n is the number of elements in the list
	*	@pre None
	*   @post The element that is in the specified position is removed from the list
	*	@param Integer representing the index at which you wish to remove a value
	*   @return True if an element was removed, false otherwise.
	*/
	bool removeAt(int position);

	/**
	*	The value at the given position is overridden with the value passed in. If the position is beyond the size of the list, the user is notified. NOTE: The range of indices is from 1 to n, where n is the number of elements in the list
	*	@pre None
	*   @post The value at the given position is overridden with the value passed in
	*	@param Integer representing the index you wish to change the value and the value you want
	*   @return None
	*/
	void setEntry(int position, T value);

	/**
	*	Returns the value associated with the index that is passed in. NOTE: The range of indices is from 1 to n, where n is the number of elements in the list
	*	@pre None
	*   @post None
	*	@param Integer representing the index you wish to have the value returned
	*   @return The entry at the given position.
	*/
	T& getEntry(int position);

	/**
	*	The list is searched and if the value passed in is found 'true' is returned, 'false' signifies that the value does not exist in the lsit
	*	@pre The value for T is valid
	*   @post None
	*	@param Templated value
	*   @return True if the value is in the list, false otherwise.
	*/
	T& search(std::string name);

	/**
	*	The list is traversed and sorted by dates
	*	@pre None
	*   @post The LinkedList is sorted by events
	*	@param None
	*   @return None
	*/
	void sortListEvent();

	/**
	*	The two values are compared, if event1 occurs after event2 'true' is returned, 'false' otherwise
	*	@pre Both 'T' values are valid
	*   @post None
	*	@param Two templated values
	*   @return True if event1 comes after event2.
	*/
	bool compareEvent(T event1, T event2);

	/**
	*	The list is traversed and sorted by time
	*	@pre None
	*   @post The LinkedList of times is sorted
	*	@param None
	*   @return none
	*/
	void sortListTime();

	/**
	*	The two values are compared, if time1 occurs after time2 'true' is returnd, 'false' otherwise
	*	@pre Both 'T' values are valid
	*   @post None
	*	@param Two templated values
	*   @return True if time1 comes after time2.
	*/
	bool compareTime(T time1, T time2);

	/**
	*	The list is traversed and if an event exists with the same name as the one passed in 'true' is returned, 'false' otherwise
	*	@pre The list is not empty
	*   @post None
	*	@param String representing the name of a potential event
	*   @return True if an event is found with a matching name
	*/
	bool isFound(std::string name2);


	private:
	Node<T>* m_front;//ptr to the first node in the list
	int m_length; //the length of the list
};

#include "LinkedList.hpp"

#endif
