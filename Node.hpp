template <typename T>
Node<T>::Node(T value)
{
	m_next = nullptr; //sets next ptr to null
	m_value = value; //sets the value to what was passed in
}

template <typename T>
T& Node<T>::getValue()
{
	return(m_value); //returns the value
}

template <typename T>
void Node<T>::setValue(T value)
{
	m_value = value; //sets the value to what was passed in
}

template <typename T>
Node<T>* Node<T>::getNext() const
{
	return(m_next); //returns the ptr to the next node
}

template <typename T>
void Node<T>::setNext(Node<T>* next)
{
	m_next = next; //sets the next node ptr to the one passed in
}
