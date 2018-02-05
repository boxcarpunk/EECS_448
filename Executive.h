//EECS448 Project 1 Kleyn
#pragma once
#inlude "LinkedList.h"

class Executive(){
	public:
	Executive();
	~Executive();
	void run();
	
	private:
	std::ifstream inFile; 
	

