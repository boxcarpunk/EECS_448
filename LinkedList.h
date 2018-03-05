#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"
#include <stdexcept>

template <typename keyType, typename searchType>
class LinkedList
{
	public:
	/**
	*	Assigns private member variables default values and creates an empty list
	*	@pre None
	*	@post An empty LinkedList object is created
	*	@param None
	*	@return None
	*/
	LinkedList();

	/**
	*	Each element in the list is traversed and removed until no more exist
	*	@pre  All nodes in the LinkedList object are deleted
	*	@post The Linked List is empty and prompty deallocated
	*	@param None
	*	@return None
	*/
	~LinkedList();

	/**
	*	Checks to see if the value associated with the private member variable 'm_length' is greater than 0. If it is, 'false' will be returned. 'true' otherwise
	*	@pre None
	* @post None
	*	@param None
	* @return True if the list is empty, false otherwise
	*/
	bool isEmpty() const;

	/**
	*	Returns the value associated with the number of nodes that are in the list at the time called
	*	@pre None
	* @post None
	*	@param None
	* @return The number of elements in the list
	*/
	int getLength() const;

	/**
	*	Returns the index associated with the templated value. If it does not exist in the list, the user is notified. NOTE: The range of indices is from 1 to n, where n is the number of elements in the list
	*	@pre keyType supports "keyType == keyType"
	* @post None
	*	@param Templated value representing an object potentially held in the list
	* @return Returns the index of the first node in the list that contains the value. Returns 0 otherwise
	*/
	int positionOf(keyType value) const;

	/**
	*	Add a new element to the end of the list
	*	@pre None
	* @post A single, new element is created and added to the back of the list
	*	@param Templated value to be added to the list
	* @return None
	*/
	void addBack(keyType value);

	/**
	*	Adds a new element to the front of the list
	*	@pre None
	* @post A single, new element is created and added to the front of the list
	*	@param Templated value to be added to the list
	* @return None
	*/
	void addFront(keyType value);

	/**
	*	Returns 'true' if the value was inserted at the given position, 'false' otherwise. NOTE: The range of indices is from 1 to n, where n is the number of elements in the list
	*	@pre None
	* @post A single, new element is created and added in the position specified or none depending upon the validity of the position
	*	@param Templated value to be added to the list and an integer representing the index at which the value is to be added
	* @return True if the element was inserted and false otherwise
	*/
	bool insert(int position, keyType value);

	/**
	*	Returns 'true' if the element at the end of the list is removed, 'false' if the list is empty
	*	@pre None
	* @post One element is removed from the back of the list or none if list is empty
	*	@param None
	* @return True if the back element was removed, false if the list is empty
	*/
	bool removeBack();

	/**
	*	Return 'true' if the element at the front of the list is removed, 'false' if the list is empty
	*	@pre None
	* @post One element is removed from the front of the list or none if list is empty
	*	@param None
	* @return True if the front element was removed, false if the list is empty
	*/
	bool removeFront();

	/**
	*	Returns 'true' if the element at the given position is removed, 'false' otherwise. NOTE: The range of indices is from 1 to n, where n is the number of elements in the list
	*	@pre None
	* @post The element that is in the specified position is removed from the list or none depending upon the validity of the position
	*	@param Integer representing the index at which you wish to remove a value
	* @return True if an element was removed, false otherwise
	*/
	bool removeAt(int position);

	/**
	*	The value at the given position is overridden with the value passed in. If the position is beyond the size of the list, the user is notified. NOTE: The range of indices is from 1 to n, where n is the number of elements in the list
	*	@pre None
	* @post The value at the given position is overridden with the value passed in or none depending upon the validity of the position
	*	@param Integer representing the index you wish to change and the value to set it to
	* @return True if the value at the position was overridden, false otherwise
	*/
	bool setEntry(int position, keyType value);

	/**
	*	Returns the value associated with the index that is passed in. NOTE: The range of indices is from 1 to n, where n is the number of elements in the list
	*	@pre None
	* @post None
	*	@param Integer representing the index cooresponding to the value to be returned
	*	@throw Throws a runtime error if the position is invalid
	* @return The entry at the given position
	*/
	keyType& getEntry(int position) const throw(std::runtime_error);

	/**
	*	The list is searched and if the value passed in is found 'true' is returned, 'false' signifies that the value does not exist in the list
	*	@pre keyType supports "keyType == searchType"
	* @post None
	*	@param Templated search value that cooresponds to a potential entry in the list
	*	@throw Throws a runtime error if the entry was not found
	* @return The entry that cooresponds to the search value
	*/
	keyType& search(searchType value) const throw(std::runtime_error);

	/**
	*	The list is traversed and if the entry being searched for is found 'true' is returned, 'false' otherwise
	*	@pre keyType supports "keyType == searchType"
	* @post None
	*	@param Templated search value that cooresponds to a potential entry in the list
	* @return True if the entry is in the list, false otherwise
	*/
	bool isFound(searchType value) const;

	/**
	*	The list is traversed and bubble sorted into ascending order
	*	@pre keyType supports "keyType > keyType"
	* @post The LinkedList is sorted in ascending order
	*	@param None
	* @return None
	*/
	void sort();

	private:
	Node<keyType>* m_front; /**< ptr to the first node in the list */
	int m_length; /**< the length of the list */
};

#include "LinkedList.hpp"

#endif
