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
	bool adminFunc();
	bool userFunc();
	int listLength = 0;
};
	

