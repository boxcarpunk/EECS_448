/**
* @author Sahil Hirani
* @cal448
* @date 12 February 2017
* @brief Implementation file for templated LinkedList class
* @file LinkedList.hpp **/

#include <iostream>
#include "LinkedList.h"
#include <string>

template <typename T>
LinkedList<T>::LinkedList()
{
  m_front = nullptr; //sets the ptr to the first node to null
  m_length = 0; //sets the length to zero
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
  return(m_length == 0) //returns true if the length is zero and false otherwise
}

template <typename T>
int LinkedList<T>::getLength() const
{
  return(m_length); //returns the length of the list
}

template <typename T>
int LinkedList<T>::positionOf(T value) const
{
  int val = 0; //a variable that keeps track of the index of the current node
  Node<T>* temp = m_front; //creates a temp ptr pointing at the first node
  for(int i = 1; i <= m_length; i++) //runs through the list
  {
    val++; //increments val
    if( value == temp->getValue()) //if the value passed in is equal to the value in the node
    {
      return(val); //returns the index of the node
    }
    else //if the value passed in is not equal to the value in the node
    {
      temp = temp->getNext(); //move on to the next node or null if looking at the last node
    }
  }
  return(0); //return zero if the value was not found
}

template <typename T>
void LinkedList<T>::addBack(T value)
{
  if(m_length == 0) //if the list is empty
  {
    addFront(value); //add the value to the front
  }
  else //if the list is not empty
  {
    Node<T>* newNode = new Node<T>(value); //create a new node containing the given value
    Node<T>* temp = m_front; //creates a temp ptr pointing at the first node
    while(temp -> getNext() != nullptr) //loops until temp is pointing to the last node
    {
      temp = temp -> getNext(); //moves onto the next node
    }
    temp -> setNext(newNode); //makes the old back point to the new node so that it is now the back
    m_length++; //increases the length of the list by one since a node was added
  }
}

template <typename T>
void LinkedList<T>::addFront(T value)
{
  Node<T>* temp = new Node<T>(value); //creates a new node containing the given value
    if(m_length == 0) //if the list is empty
    {
      m_front = temp; //makes the front node ptr point to the new node
    }
    else //if the list is not empty
    {
      temp -> setNext(m_front); //makes the new node point to the old front
      m_front = temp; //makes the front node ptr point to the new node
    }
    m_length++; //increases the length of the list by one since a node was added
}

template <typename T>
bool LinkedList<T>::insert(int position, T value)
{
  if((position <= 0) || (position > (m_length+1))) //if the position is invalid (it isn't between one and one greater than the current length inclusively)
  {
    return(false); //return false since the node was not added
  }
  else if(position == 1) //if the position is one (will be the front)
  {
    addFront(value); //add the value to the front of the list
    return(true); //return true since the node was added
  }
  else if(position == (m_length+1)) //if the position is one more than the current length (will be the back)
  {
    addBack(value); //add the value to the back of the list
    return(true); //return true since the node was added
  }
  else //if the position is valid but not the front or back
  {
    Node<T>* newNode = new Node<T>(value); //creates a new node containing the given value
    Node<T>* temp = m_front; //creates a temp ptr pointing to the first node
    Node<T>* temp2 = m_front; //creates a second temp ptr pointing to the first node
    for(int i = 1; i < (position-1); i++) //goes through the list until the temp2 is pointing at the node before the position
    {
      temp2 = temp2->getNext(); //moves onto the next node
    }

	temp = temp2->getNext(); //sets temp to the node currently at the position
    temp2 -> setNext(newNode); //makes the node before the given position point to the new node
    newNode -> setNext(temp); //makes the new node point to the node previously occupying the position
    m_length++; //increases the length of the list by one since a node was added
    return(true); //returns true since the node was added
  }
}

template <typename T>
bool LinkedList<T>::removeBack()
{
  if(m_length == 0) //if the list is empty
  {
    return(false); //return false since no nodes were removed
  }
  else if(m_length == 1) //if there is one node in the list
  {
    removeFront(); //remove the first node (the only one)
    return(true); //return true since the node was removed
  }
  else //if the list has more than one node
  {
    Node<T>* temp = m_front; //makes a temp ptr that points to the first node
    Node<T>* temp2 = m_front; //makes a second temp ptr that points to the first node
    for(int i = 1; i < m_length-1; i++) //runs through the list until temp2 is pointing at the second to last node
    {
      temp2 = temp2 -> getNext(); //moves on to the next node
    }
	temp = temp2->getNext(); //makes temp point at the last node
    delete temp; //deletes the last node
    temp2 -> setNext(nullptr); //makes the new last node point to null
    m_length = m_length -1; //decreases the length by one since a node was removed
    return(true); //returns true since a node was removed
  }
}

template <typename T>
bool LinkedList<T>::removeFront()
{
  if(m_length == 0) //if the list is empty
  {
    return(false); //return false since no nodes were removed
  }
  else //if the list is not empty
  {
    Node<T>* temp = m_front -> getNext(); //creates a temp ptr that points at the second node (or null if the list only has one node)
    delete m_front; //deletes the first node
    m_front = temp; //makes the front ptr point to whatever the deleted node was pointing to
    m_length--; //decreases the length by one since a node was removed
    return(true); //returns true since a node was removed
  }
}

template <typename T>
bool LinkedList<T>::removeAt(int position)
{
  if((m_length == 0) || (position <= 0) || (position > m_length)) //if the list is empty or the position is invalid (it isn't between one and the length inclusively)
  {
    return(false); //return false since no node was removed
  }
  else if(position == 1) //if removing the front
  {
    removeFront(); //remove the front
    return(true); //return true since a node was removed
  }
  else if( position == m_length) //if removing the back
  {
    removeBack(); //remove the back
    return(true); //return true since a node was removed
  }
  else //if the position is valid and not the front or back
  {
    Node<T>* temp = m_front; //create a temp ptr pointing to the first node
    Node<T>* temp2 = m_front; //create a second temp ptr pointing to the first node
    for(int i = 1; i < (position-1); i++) //runs through the list until temp2 is pointing to the node before the position
    {
      temp2 = temp2 -> getNext(); //moves onto the next node
    }
	temp = temp2->getNext()->getNext(); //makes temp point at the node after the position
    delete temp2 -> getNext(); //deletes the node at the position
    temp2 -> setNext(temp); //makes the node before the position point at the node after the position
    m_length--; //decreases the length by one since a node was removed
    return(true); //returns true since a node was removed
  }
}

template <typename T>
void LinkedList<T>::setEntry(int position, T value)
{
	Node<T>* temp = m_front; //creates a temp ptr pointing to the first node
    for(int i = 1; i < position; i++) //runs through the list until temp is pointing at the position
    {
      temp = temp -> getNext(); //moves on to the next node
    }
    temp -> setValue(value); //sets the value of the node at the position to the given value
}

template <typename T>
T& LinkedList<T>::getEntry(int position)
{
	Node<T>* temp = m_front; //creates a temp ptr pointing at the first node
	if (position<1 || position>m_length) //if the position is invalid (it isn't between one and the length inclusively)
	{
		throw(std::runtime_error("Invalid Entry - Out of range")); //throw an error stating the invalid position
	}
	else if (position == 1) //if getting the value at the front
	{
		return m_front->getValue(); //return the value stored at the front
	}
	else //if the position is valid but not the front
	{
		for (int i=0; i<position-1; i++) //run through the list until temp is pointing at the position
		{
			temp = temp->getNext(); //move onto the next node
		}
		return temp->getValue(); //return the value stored at the position
	}
}

template <typename T>
T& LinkedList<T>::search(std::string name)
{
	Node<T>* temp = m_front; //makes a temp ptr pointing at the first node
	T temp1 = temp ->getValue(); //stores the value at the front in a temp variable
	while(temp != nullptr) //while temp in not pointing at null
	{
		if(temp1.getName() == name) //if the name of the value stored is equal to the name passed in
		{
			return(temp -> getValue()); //returns the value stored in the first node
			break; //breaks out of the while loop
			throw(std::runtime_error("Invalid Entry - Out of range")); //throws an error stating invalid position
		}
		else //if the name of the value stored is not equal to the name passed in
		{
			temp = temp -> getNext(); //moves on to the next node (or null if already at the final node)
			temp1 = temp -> getValue(); //stores the value contained in the node (or seg faults if temp is pointing at null)
		}
	}
	throw(std::runtime_error("Event doesn't Exist!\n")); //throws an error stating that the event does not exist if it wasn't found in the while loop
}

template <typename T>
bool LinkedList<T>::isFound(std::string name2)
{
	Node<T>* temp = m_front; //makes a temp ptr pointing at the first node
	T temp1 = temp -> getValue(); //stores the value contained by the first node in a temp variable
	bool found = false; //creates a flag that tracks if the object was found and sets it to false since the object has not yet been found
	while(temp != nullptr) //while temp is not pointing at null
	{
		if(temp1.getName() == name2) //if the name of the value stored is equal to the name passed in
		{
			found = true; //sets the flag to true
			return(found); //returns the flag
			break; //breaks out of the while loop
		}
		else //if the name of the value stored is not equal to the name passed in
		{
			temp = temp -> getNext(); //moves on to the next node (or null if already at the last)
			temp1 = temp -> getValue(); //stores the value contained in the node (or seg faults if temp is pointing at null)
		}
	}
	return(found); //returns the flag
}


template <typename T>
void LinkedList<T>::sortListEvent()
{
  Node<T>* currentNode = nullptr; //creates a ptr to point to the current node
  Node<T>* prevNode = nullptr; //creates a ptr to point to the previous node
  Node<T>* temp = nullptr; //creates a temp ptr

	if(m_length =< 1) //if the list is empty or has one node
	{
    //already sorted since it is empty or has one node
	}
	else if(m_length == 2) //if the list has two nodes
	{
		currentNode = m_front; //makes the front the current node
		if(compareEvent((currentNode -> getValue()), (currentNode -> getNext() -> getValue())) == true) //if the current event occurs after the next event
		{
			//swaps the position of the two nodes in the list
			addBack(currentNode -> getValue()); //adds the value held in the first node to the back
			removeFront(); //deletes the first node
		}
	}
	else //if the length is greater than 2
	{
		for(int i = 1; i <= m_length; i++) //runs through the list
		{
			currentNode = m_front; //makes the front the current node
			prevNode = m_front; //makes the front the previous node

			while(currentNode -> getNext() != nullptr) //while the next node is not null (does not loop for the last node)
			{
				if(compareEvent(currentNode -> getValue(), currentNode -> getNext() -> getValue()) == true) //if the current event occurs after the next event in the list
				{
					//swaps the current node with the node one after
					temp = currentNode -> getNext(); //makes temp point at the next node
					currentNode -> setNext(currentNode -> getNext() -> getNext()); //makes the current node point at the node two positions ahead
					temp -> setNext(currentNode); //makes temp's node point to the current one

					if(currentNode == m_front) //if the current node was the first one
					{
						//makes m_front point to the new first node
						prevNode = temp; //makes the previous node ptr point at the node before the current one
						m_front = prevNode; //makes the previous node the new first node
					}
					else //if the current node was not the first
					{
						prevNode -> setNext(temp); //makes the previous node point to the temp node
	        			currentNode = temp; //makes the temp node the current one
					}
	    		}
				//moves both ptrs one position forward in the list
				prevNode = currentNode; //makes the previous node ptr point to the current node
				currentNode = currentNode->getNext(); //makes the current node ptr point to the next node (or null if the last)
			}
		}
	}
}

template <typename T>
bool LinkedList<T>::compareEvent(T event1, T event2)
{
	if(event1.getYear() > event2.getYear()) //if event1 occurs on a later year
	{
		return(true); //returns true since event1 occurs after event2
	}
	if((event1.getYear() == event2.getYear()) && (event1.getMonth() > event2.getMonth())) //if the events occur on the same year but event1 occurs on a later month
	{
		return(true); //returns true since event1 occurs after event2
	}
	if((event1.getYear() == event2.getYear()) && (event1.getMonth() == event2.getMonth()) && (event1.getDay() > event2.getDay())) //if the events occur on the same month and year but event1 occurs on a later day
	{
		return(true); //return true since event1 occurs after event2
	}
	else
	{
		return(false); //returns false because event1 does not occur on a later year, month, or day than event2
	}
}

template <typename T>
void LinkedList<T>::sortListTime()
{
  Node<T>* currentNode = nullptr; //creates a ptr to point at the current node
  Node<T>* prevNode = nullptr; //creates a ptr to point at the previous node
  Node<T>* temp = nullptr; //creates a temp ptr

	if(m_length =< 1) //if the list is empty or only contains one node
	{
    //already sorted since it is empty or has only one node
	}
	else if(m_length == 2) //if the list has two nodes
	{
		currentNode = m_front; //makes the front the current node
		if (compareTime(currentNode -> getValue(), currentNode -> getNext() -> getValue()) == true) //if the current event is after the next event in the list
		{
			//swaps the position of the two nodes in the list
			addBack(currentNode -> getValue()); //adds the vaue held in the first node to the back of the list
			removeFront(); //removes the first node
		}
	}
	else //if the list has greater than 2 nodes
	{
		for(int i = 1; i <= m_length; i++) //runs through the list
		{
			currentNode = m_front; //makes the front the current node
			prevNode = m_front; //makes the front the previous node

			while(currentNode -> getNext() != nullptr) //while the next node is not null (does not loop for the last node)
			{
				if(compareTime(currentNode -> getValue(), currentNode -> getNext() -> getValue()) == true) //if the current event is after the next event in the list
				{
					//swaps the current node with the node one after
					temp = currentNode -> getNext(); //makes temp point to the next node
					currentNode -> setNext(currentNode -> getNext() -> getNext()); //makes the current node point to the node two positions ahead
					temp -> setNext(currentNode); //makes temp's node point at the current node

					if(currentNode == m_front) //if the current node was the front
					{
						//makes m_front point to the new first node
						prevNode = temp; //make the previous node ptr point to temp's node
						m_front = prevNode; //makes the front the previous node
					}
					else //if the current node was not the front
					{
						//makes the previous node point to the node that was swappped with current node and then makes that the current node
						prevNode -> setNext(temp); //makes the previous node point to temp's node
	        			currentNode = temp; //makes temp the current node
					}
	    		}
				//moves the ptrs one position forward
				prevNode = currentNode; //makes the previous node ptr point at the current node
				currentNode = currentNode -> getNext(); //makes the current node ptr point to the next node (or null if the last)
			}
		}
	}
}

template <typename T>
bool LinkedList<T>::compareTime(T time1, T time2)
{
	if(time1.getTimeSlot() > time2.getTimeSlot()) //if time1 is after time2
	{
		return(true); //return true since time1 occurs later
	}
	else //if time1 is not after time2
	{
		return(false); //return false since time1 does not occur later
	}
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	while(m_front != nullptr) //while the list is not empty
	{
		removeFront(); //remove the first node
	}
}
