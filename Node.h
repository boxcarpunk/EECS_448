#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
	/**
	*	Creates a new node with the value that is passed in
	*	@pre None
	* @post A node with the passed value is created
	*	@param Templated value to be held by the node
	* @return None
	*/
	Node(T value);

	/**
	*	Returns the value that is associate with any given node
	*	@pre None
	* @post None
	*	@param None
	* @return Returns m_value private member variable
	*/
	T& getValue();

	/**
	*	Sets the value of a node equal to the value passed in
	*	@pre The value for 'T' is valid
	* @post The value for a node is set
	*	@param Templated value to be held by the node
	* @return None
	*/
	void setValue(T value);

	/**
	*	Returns a pointer to the node that follows the current
	*	@pre None
	* @post None
	*	@param None
	* @return Returns m_next Node pointer to next node in list
	*/
	Node<T>* getNext() const;

	/**
	*	Sets the next node in a structure equal to the pointer that is passed in a parameter
	*	@pre None
	* @post Sets the next node to a pointer given by the user
	*	@param A node pointer representing the next value in a data structure
	* @return None
	*/
	void setNext(Node<T>* next);

private:

	T m_value; /**< the current value of the node */
	Node<T>* m_next; /**< a ptr to the next node */

};

#include "Node.hpp"
#endif
