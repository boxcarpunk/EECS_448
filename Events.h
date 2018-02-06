//EECS448 Project 1 Kleyn
#pragma once
#include <iostream>
#include <sstream>

class Events
{
	public:
	Events(std::string name, std::string month, std::string day, std::string year, std::string start, std::string end);
	Events();
	~Events();
	void getInfo();
	
	private:
	std::string m_name;
	std::string m_month;
	int m_day;
	int m_year;
	int m_start;
	int m_end;

};
