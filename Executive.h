//EECS448 Project 1 Kleyn
#pragma once
#include "LinkedList.h"
#include "Events.h"
#include <fstream>
#include <vector>
#include <iostream>

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
	std::string name = "";
	std::string month = "";
	std::string day = "";										//Event variables
	std::string year = "";
	std::string s_time = "";
	std::string e_time = "";

};
