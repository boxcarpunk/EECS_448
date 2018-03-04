#include "LinkedList.h"

template <typename keyType, typename searchType>
LinkedList<keyType, searchType>::LinkedList()
{
  m_front = nullptr; //sets the ptr to the first node to null
  m_length = 0; //sets the length to zero
}

template <typename keyType, typename searchType>
LinkedList<keyType, searchType>::~LinkedList()
{
	while (m_front != nullptr) //while the list is not empty
	{
		removeFront(); //remove the first node
	}
}

template <typename keyType, typename searchType>
bool LinkedList<keyType, searchType>::isEmpty() const
{
	return(m_length == 0); //returns true if the length is zero and false otherwise
}

template <typename keyType, typename searchType>
int LinkedList<keyType, searchType>::getLength() const
{
  return(m_length); //returns the length of the list
}

template <typename keyType, typename searchType>
int LinkedList<keyType, searchType>::positionOf(keyType value) const
{
  Node<keyType>* temp = m_front; //creates a temp ptr pointing at the first node

  for(int i = 1; i <= m_length; i++) //runs through the list
  {
    if( value == temp->getValue()) //if the value passed in is equal to the value in the node
    {
      return(i); //returns the index of the node
    }
    else //if the value passed in is not equal to the value in the node
    {
      temp = temp->getNext(); //move on to the next node or null if looking at the last node
    }
  }

  return(0); //return zero if the value was not found
}

template <typename keyType, typename searchType>
void LinkedList<keyType, searchType>::addBack(keyType value)
{
  if(isEmpty()) //if the list is empty
  {
		  addFront(value); //add the value to the front

  }
  else //if the list is not empty
  {
    Node<keyType>* newNode = new Node<keyType>(value); //create a new node containing the given value
    Node<keyType>* temp = m_front; //creates a temp ptr pointing at the first node

    while(temp -> getNext() != nullptr) //loops until temp is pointing to the last node
    {
      temp = temp -> getNext(); //moves onto the next node
    }

    temp -> setNext(newNode); //makes the old back point to the new node so that it is now the back
    m_length++; //increases the length of the list by one since a node was added
  }
}

template <typename keyType, typename searchType>
void LinkedList<keyType, searchType>::addFront(keyType value)
{
  Node<keyType>* temp = new Node<keyType>(value); //creates a new node containing the given value

    if(m_front == nullptr) //if the list is empty
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

template <typename keyType, typename searchType>
bool LinkedList<keyType, searchType>::insert(int position, keyType value)
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
    Node<keyType>* newNode = new Node<keyType>(value); //creates a new node containing the given value

    Node<keyType>* temp = m_front; //creates a temp ptr pointing to the first node
    Node<keyType>* temp2 = m_front; //creates a second temp ptr pointing to the first node

    for(int i = 1; i < (position-1); i++) //goes through the list until temp is pointing at the node before the position
    {
      temp = temp->getNext(); //moves onto the next node
    }

	temp2 = temp->getNext(); //sets temp2 to the node currently at the position
    temp -> setNext(newNode); //makes the node before the given position point to the new node
    newNode -> setNext(temp2); //makes the new node point to the node previously occupying the position

    m_length++; //increases the length of the list by one since a node was added
    return(true); //returns true since the node was added
  }
}

template <typename keyType, typename searchType>
bool LinkedList<keyType, searchType>::removeBack()
{
  if(isEmpty()) //if the list is empty
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
    Node<keyType>* temp = m_front; //makes a temp ptr that points to the first node
    Node<keyType>* temp2 = m_front; //makes a second temp ptr that points to the first node

    for(int i = 1; i < m_length-1; i++) //runs through the list until temp is pointing at the second to last node
    {
      temp = temp -> getNext(); //moves on to the next node
    }

	temp2 = temp->getNext(); //makes temp2 point at the last node
    delete temp2; //deletes the last node
    temp -> setNext(nullptr); //makes the new last node point to null

    m_length--; //decreases the length by one since a node was removed
    return(true); //returns true since a node was removed
  }
}

template <typename keyType, typename searchType>
bool LinkedList<keyType, searchType>::removeFront()
{
  if(isEmpty()) //if the list is empty
  {
    return(false); //return false since no nodes were removed
  }
  else //if the list is not empty
  {
    Node<keyType>* temp = m_front -> getNext(); //creates a temp ptr that points at the second node (or null if the list only has one node)
    delete m_front; //deletes the first node
    m_front = temp; //makes the front ptr point to the node that was at index 2 or null

    m_length--; //decreases the length by one since a node was removed
    return(true); //returns true since a node was removed
  }
}

template <typename keyType, typename searchType>
bool LinkedList<keyType, searchType>::removeAt(int position)
{
  if((position <= 0) || (position > m_length)) //if the position is invalid (it isn't between one and the length inclusively)
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
    Node<keyType>* temp = m_front; //create a temp ptr pointing to the first node
    Node<keyType>* temp2 = m_front; //create a second temp ptr pointing to the first node

    for(int i = 1; i < (position-1); i++) //runs through the list until temp is pointing to the node before the position
    {
      temp = temp -> getNext(); //moves onto the next node
    }
	temp2 = temp->getNext()->getNext(); //makes temp2 point at the node after the position
    delete temp -> getNext(); //deletes the node at the position
    temp -> setNext(temp2); //makes the node before the position point at the node after the position

    m_length--; //decreases the length by one since a node was removed
    return(true); //returns true since a node was removed
  }
}

template <typename keyType, typename searchType>
bool LinkedList<keyType, searchType>::setEntry(int position, keyType value)
{
	if ((position < 1) || (position > m_length)) //if the position is invalid (it isn't between one and the length inclusively)
	{
		return(false); //returns false since the entry at the position couldn't be set
	}
	else //if the position is valid
	{
		Node<keyType>* temp = m_front; //creates a temp ptr pointing to the first node

		for (int i = 1; i < position; i++) //runs through the list until temp is pointing at the position
		{
			temp = temp->getNext(); //moves on to the next node
		}

		temp->setValue(value); //sets the value of the node at the position to the given value
		return(true); //returns true since the entry at the position was set
	}
}

template <typename keyType, typename searchType>
keyType& LinkedList<keyType, searchType>::getEntry(int position) const throw(std::runtime_error)
{
	if (position<1 || position>m_length) //if the position is invalid (it isn't between one and the length inclusively)
	{
		throw(std::runtime_error("Error in LinkedList method getEntry: Invalid Index - Out of range")); //throws an error stating the invalid position
	}
	else if (position == 1) //if getting the value at the front
	{
		return m_front->getValue(); //returns the value stored at the front
	}
	else //if the position is valid but not the front
	{
		Node<keyType>* temp = m_front; //creates a temp ptr pointing at the first node

		for (int i=1; i<position; i++) //runs through the list until temp is pointing at the position
		{
			temp = temp->getNext(); //moves onto the next node
		}

		return temp->getValue(); //returns the value stored at the position
	}
}

template <typename keyType, typename searchType>
keyType& LinkedList<keyType, searchType>::search(searchType value) const throw(std::runtime_error)
{
	Node<keyType>* temp = m_front; //makes a temp ptr pointing at the first node

	while(temp != nullptr) //while temp is not pointing at null
	{
		if(temp->getValue() == value) //if the entry at the current node is the one being searched for
		{
			return(temp->getValue()); //returns the value stored in the node
		}
		else //if the entry at the current node is not the one being searched for
		{
			temp = temp -> getNext(); //moves on to the next node (or null if already at the final node)
		}
	}

	throw(std::runtime_error("Error in LinkedList method search: Entry could not be found\n")); //throws an error stating that the entry was not found in the list
}

template <typename keyType, typename searchType>
bool LinkedList<keyType, searchType>::isFound(searchType value) const
{
	Node<keyType>* temp = m_front; //makes a temp ptr pointing at the first node

	while(temp != nullptr) //while temp is not pointing at null
	{
		if(temp->getValue() == value) //if the entry at the current node is the one being searched for
		{
			return(true); //returns true since the entry cooresponding to the search value was found
		}
		else //if the entry at the current node is not the one being searched for
		{
			temp = temp -> getNext(); //moves on to the next node (or null if already at the last)
		}
	}

	return(false); //returns false since the entry was not found in the list
}

template <typename keyType, typename searchType>
void LinkedList<keyType, searchType>::sort()
{
	if(m_length <= 1) //if the list is empty or has one node
	{
		//already sorted since it is empty or has one node
	}
	else if(m_length == 2) //if the list has two nodes
	{
		if(m_front->getValue() > m_front->getNext()->getValue()) //if the first node is greater than the second
		{
			//swaps the position of the two nodes in the list
			addBack(m_front -> getValue()); //adds the value held in the first node to the back
			removeFront(); //deletes the first node
		}
	}
	else //if the length is greater than 2
	{
		Node<keyType>* currentNode = nullptr; //creates a ptr to point to the current node
		keyType temp; //creates a temp storage object

		for(int i = 1; i < m_length; i++) //iterates n-1 times
		{
			currentNode = m_front; //makes the front the current node

			for (int j = 1; j <= (m_length - i); j++) //goes through the list until one node before the already sorted portion
			{
				if(currentNode->getValue() > currentNode->getNext()->getValue()) //if the current node is greater than the next node
				{
					//swaps the values of the nodes
					temp = currentNode -> getValue(); //stores the current node's value in temp
					currentNode -> setValue(currentNode -> getNext() -> getValue()); //overrides the current node's value with the next node's value
					currentNode -> getNext() -> setValue(temp); //overrides the next node's value with the value that was in the current node
	    		}

				currentNode = currentNode->getNext(); //moves along the list
			}
		}
	}
}
