/**
*	@author Sahil Hirani
*	@date 02/05/2018
*	@file LinkedList.hpp
*	@brief Implementation file for templated LinkedList class
*/
#include <iostream>

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
  for(int i = 1; i < position; i++)
  {
    temp = temp -> getNext();
  }
  return(temp -> getValue());
}

template <typename T>
bool LinkedList<T>::search(T value) const
{
	Node<T>* temp = m_front;
	bool isFound = false;
	while(temp != nullptr)
	{
		if(temp -> getValue() == value)
		{
			isFound = true;
			break;
		}
		else{}
		temp = temp -> getNext();
	}
	return(isFound);
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  while(m_front != nullptr)
  {
    removeFront();
  }
}
