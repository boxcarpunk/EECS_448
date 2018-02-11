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
  m_front = nullptr;
  m_length = 0;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
  if(m_length == 0)
  {
    return(true);
  }
  else
  {
    return (false);
  }
}

template <typename T>
int LinkedList<T>::getLength() const
{
  return(m_length);
}

template <typename T>
int LinkedList<T>::positionOf(T value) const
{
  int val = 0;
  Node<T>* temp = m_front;
  for(int i = 1; i <= m_length; i++)
  {
    val++;
    if( value == temp->getValue())
    {
      return(val);
    }
    else
    {
      temp = temp->getNext();
    }
  }
  return(0);
}

template <typename T>
void LinkedList<T>::addBack(T value)
{
  if(m_length == 0)
  {
    addFront(value);
  }
  else
  {
    Node<T>* newNode = new Node<T>(value);
    Node<T>* temp = m_front;
    while(temp -> getNext() != nullptr)
    {
      temp = temp -> getNext();
    }
    temp -> setNext(newNode);
    m_length++;
  }
}

template <typename T>
void LinkedList<T>::addFront(T value)
{
  Node<T>* temp = new Node<T>(value);
    if(m_length == 0)
    {
      m_front = temp;
    }
    else
    {
      temp -> setNext(m_front);
      m_front = temp;
    }
    m_length++;
}

template <typename T>
bool LinkedList<T>::insert(int position, T value)
{
  if((position <= 0) || (position > (m_length+1)))
  {
    return(false);
  }
  else if(position == 1)
  {
    addFront(value);
    return(true);
  }
  else if(position == (m_length+1))
  {
    addBack(value);
    return(true);
  }
  else
  {
    Node<T>* newNode = new Node<T>(value);
    Node<T>* temp = m_front;
    Node<T>* temp2 = m_front;
    for(int i = 1; i <= (position-1); i++)
    {
      temp = temp->getNext();
    }
    for(int i = 1; i < (position-1); i++)
    {
      temp2 = temp2 -> getNext();
    }

    temp2 -> setNext(newNode);
    newNode -> setNext(temp);
    m_length++;
    return(true);
  }
}

template <typename T>
bool LinkedList<T>::removeBack()
{
  if(m_length == 0)
  {
    return(false);
  }
  else if(m_length == 1)
  {
    removeFront();
    return(true);
  }
  else
  {
    Node<T>* temp = m_front;
    Node<T>* temp2 = m_front;
    for(int i = 1; i <= (m_length-1); i++)
    {
      temp = temp -> getNext();
    }
    for(int i = 1; i < m_length-1; i++)
    {
      temp2 = temp2 -> getNext();
    }
    delete temp;
    temp2 -> setNext(nullptr);
    m_length = m_length -1;
    return(true);
  }
}

template <typename T>
bool LinkedList<T>::removeFront()
{
  if(m_length == 0)
  {
    return(false);
  }
  else
  {
    Node<T>* temp = m_front -> getNext();
    delete m_front;
    m_front = temp;
    m_length--;
    return(true);
  }
}

template <typename T>
bool LinkedList<T>::removeAt(int position)
{
  if((m_length == 0) || (position <= 0) || (position > m_length))
  {
    return(false);
  }
  else if(position == 1)
  {
    removeFront();
    return(true);
  }
  else if( position == m_length)
  {
    removeBack();
    return(true);
  }
  else
  {
    Node<T>* temp = m_front;
    Node<T>* temp2 = m_front;
    for(int i = 1; i <= position; i++)
    {
      temp = temp -> getNext();
    }
    for(int i = 1; i < (position-1); i++)
    {
      temp2 = temp2 -> getNext();
    }
    delete temp2 -> getNext();
    temp2 -> setNext(temp);
    m_length--;
    return(true);
  }
}

template <typename T>
void LinkedList<T>::setEntry(int position, T value)
{
  Node<T>* temp = m_front;
    for(int i = 1; i < position; i++)
    {
      temp = temp -> getNext();
    }
    temp -> setValue(value);
}

template <typename T>
T& LinkedList<T>::getEntry(int position)
{
	Node<T>* temp = m_front;
	if (position<1 || position>m_length)
	{
    std::cout<<"Invalid Entry - Out of range.\n";
		//throw(std::runtime_error("Invalid Entry - Out of range"));
	}
	else if (position == 1)
	{
		return m_front->getValue();
	}
	else
	{
		for (int i=0; i<position-1; i++)
		{
			temp = temp->getNext();
		}
		return temp->getValue();
	}
}

template <typename T>
T& LinkedList<T>::search(std::string name)
{
	Node<T>* temp = m_front;
  T temp1 = temp ->getValue();
	while(temp != nullptr)
	{
    temp1 = temp -> getValue();
		if(temp1.getName() == name)
		{
      return(temp1);
			break;
		}
		else{
		temp = temp -> getNext();
    }
	}
  T empty;
  return(empty);
}

template <typename T>
bool LinkedList<T>::isFound(std::string name2)
{
  Node<T>* temp = m_front;
  T temp1 = temp -> getValue();
  bool found = false;
  while(temp != nullptr)
  {
    temp1 = temp -> getValue();
		if(temp1.getName() == name2)
		{
      found = true;
      return(found);
			break;
		}
		else{
		temp = temp -> getNext();
    }
  }
  return(found);
}


template <typename T>
void LinkedList<T>::sortListEvent()
{
  Node<T>* currentNode = nullptr;
  Node<T>* prevNode = nullptr;
  Node<T>* temp = nullptr;

	if(m_length == 1)
	{
    //already sorted since there is only one
	}
	else if(m_length == 2)
	{
		currentNode = m_front;
		if (compareEvent((currentNode -> getValue()), (currentNode -> getNext() -> getValue())) == true)
		{
			addBack(currentNode -> getValue());
			removeFront();
		}
	}
	else
	{
		for(int i = 1; i <= m_length; i++)
		{
			currentNode = m_front;
			prevNode = m_front;

	    while(currentNode -> getNext() != nullptr)
		{
	      if (compareEvent(currentNode -> getValue(), currentNode -> getNext() -> getValue()) == true)
			{
	        temp = currentNode -> getNext();
	        currentNode -> setNext(currentNode -> getNext() -> getNext());
	        temp -> setNext(currentNode);

	        if(currentNode == m_front)
					{
						prevNode = temp;
						m_front = prevNode;
					}
	        else
					{
						prevNode -> setNext(temp);
	        	currentNode = temp;
					}
	    	}
	      prevNode = currentNode;
	      currentNode = currentNode -> getNext();
	    }
	  }
	}
}

template <typename T>
bool LinkedList<T>::compareEvent(T event1, T event2)
{
	bool isTrue = false;

	if(event1.getYear() > event2.getYear())
	{
		isTrue = true;
		return(isTrue);
	}
	if(event1.getYear() == event2.getYear() && event1.getMonth() > event2.getMonth())
	{
		isTrue = true;
		return(isTrue);
	}
	if(event1.getYear() == event2.getYear() && event1.getMonth() == event2.getMonth() && event1.getDay() > event2.getDay())
	{
		isTrue = true;
		return(isTrue);
	}
  else{
    //nothing happens, false is returned outside the if statements
  }
	return(isTrue);
}

template <typename T>
void LinkedList<T>::sortListTime()
{
  Node<T>* currentNode = nullptr;
  Node<T>* prevNode = nullptr;
  Node<T>* temp = nullptr;

	if(m_length == 1)
	{
    //already sorted since there is only one
	}
	else if(m_length == 2)
	{
		currentNode = m_front;
		if (compareTime(currentNode -> getValue(), currentNode -> getNext() -> getValue()) == true)
		{
			addBack(currentNode -> getValue());
			removeFront();
		}
	}
	else
	{
		for(int i = 1; i <= m_length; i++)
		{
			currentNode = m_front;
			prevNode = m_front;

	    while(currentNode -> getNext() != nullptr)
		{
	      if (compareTime(currentNode -> getValue(), currentNode -> getNext() -> getValue()) == true)
			{
	        temp = currentNode -> getNext();
	        currentNode -> setNext(currentNode -> getNext() -> getNext());
	        temp -> setNext(currentNode);

	        if(currentNode == m_front)
					{
						prevNode = temp;
						m_front = prevNode;
					}
	        else
					{
						prevNode -> setNext(temp);
	        	currentNode = temp;
					}
	    	}
	      prevNode = currentNode;
	      currentNode = currentNode -> getNext();
	    }
	  }
	}
}

template <typename T>
bool LinkedList<T>::compareTime(T time1, T time2)
{
  bool isTrue = false;

	if(time1.getTimeslot() > time2.getTimeslot())
	{
		isTrue = true;
		return(isTrue);
	}
  else{
    //nothing happens, false is returned after this
  }
	return(isTrue);
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  while(m_front != nullptr)
  {
    removeFront();
  }
}
