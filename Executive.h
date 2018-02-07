//EECS448 Project 1 Kleyn
#pragma once
#include "LinkedList.h"
#include "Events.h"
#include <fstream>

class Executive
{
	public:
	Executive();
	~Executive();
	void run();
	
	private:
	std::ifstream inFile; 
	LinkedList<Events>* eventList;
	void adminFunc();
	void userFunc();
	int listLength = 0;
};
	

