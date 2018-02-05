/**
*	@file Node.hpp
*	@author Sahil Hirani
*	@date 02/09/2017
*	@brief A class file for the Node class
*/

template <typename T>
Node<T>::Node(T value)
{
  m_next = nullptr;
  m_value = value;
}

template <typename T>
T& Node<T>::getValue()
{
  return(m_value);
}

template <typename T>
void Node<T>::setValue(T value)
{
  m_value = value;
}

template <typename T>
Node<T>* Node<T>::getNext() const
{
  return(m_next);
}

template <typename T>
void Node<T>::setNext(Node<T>* next)
{
  m_next = next;
}
