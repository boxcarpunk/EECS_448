#include "Events.h"

Events::Events()
{
	m_name = "";
	m_month = "";
	m_day = 0;
	m_year = 0;
	m_start = 0;
	m_end = 0;
}

Events::~Events()
{

}

Events::Events(std::string name, std::string month, std::string day, std::string year, std::string start, std::string end)
{
	m_name = name;
	m_month = month;
	m_day = stoi(day);
	m_year = stoi(year);
	m_start = stoi(start);
	m_end = stoi(end);
}

void Events::getInfo()
{
	std::cout << "'" << m_name << "' on" << m_month << " " << m_day << ", " << m_year << " from " <<  m_start << " to " << m_end << ".\n";
}


