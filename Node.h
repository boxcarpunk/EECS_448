/**
* @author Sahil Hirani
* @cal448
* @date 12 February 2017
* @brief A header file for templated Node class
* @file Node.h **/

#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
  /** @pre None
	*   @post Creates a Node with given value
	*   @return None
	*/
  Node(T value);
  /** @pre None.
	*   @post None.
	*   @return returns m_value Private member variable
	*/
  T& getValue() ;
  /** @pre None.
	*   @post Sets New Node value
	*   @return None
	*/
  void setValue(T value);
  /** @pre None.
	*   @post None.
	*   @return Returns m_next Node pointer to next node in list
	*/
  Node<T>* getNext() const;
  /** @pre None.
	*   @post Sets Next Node to a Node pointer given by the user
	*   @return None
	*/
  void setNext(Node<T>* next);

private:

  T m_value;
  Node<T>* m_next;

};

#include "Node.hpp"
#endif
