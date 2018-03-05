#include "Executive.h"

const std::string fileName = "eventslist.txt";

Executive::Executive()
{
	std::ifstream inFile;
  inFile.open(fileName);
  std::vector<Events> eventsVector;
  if(inFile.is_open())
  {
    std::string strEventList;
    while( std::getline(inFile, strEventList ))
    {
      std::vector<std::string> strEventParts = split(strEventList, ',');

      std::string eventName = strEventParts[0]; //read the event name
      std::string eventAdminName = strEventParts[1]; //read the admin for the event

      std::vector<std::string> strDateParts = split(strEventParts[2], '~'); //get all parts of the date which include the days of the event, the time slots and the attendees
      std::vector<std::string> strDates;
      std::vector<std::string> strTimeSlots;
      std::vector<std::vector<TimeSlots>> timeSlotsVector;

      for(int i = 0; i < strDateParts.size(); i++) //TimeSlots
      {
        if(i % 2 == 0) //read the day of the event
        {
          strDates.push_back(strDateParts[i]);
        }
        else //get the timeslots and the attendees
        {
          strTimeSlots = split(strDateParts[i], '|'); // split all the time slots parts grouped by the time slot
          std::vector<std::string> strTimeSlotsParts // read all the index, and attendees
          std::vector<TimeSlots> timeSlots; //
          for(int b = 0; b < strTimeSlots; b++)
          {

            strTimeSlotsParts = split(strTimeSlots[b], ';');
            std::string index = strTimeSlotsParts[0] //read the index of the time slot
            TimeSlots ts(std::stoi(index));
            std::string numOfAttendees = strTimeSlotsParts[1] // read the number of attendees
            for(int c = 2; c < strTimeSlotsParts.size(); c++) // read all the attendees
            {
              ts.addAttendee(strTimeSlotsParts[c]);
            }
            timeSlots.push_back(ts);
          }
          timeSlotsVector.push_back(timeSlots); //add all timeslots to the 2d timeslots vector
        }
      }

      //convert the 2d vector to a 2d array
      TimeSlots **timeSlotsArr = new TimeSlots[timeSlotsVector.size()][54];
      for(int b = 0; b < strDates.size(); b++)
      {
        timeSlotsArr[b] = &timeSlotsVector[b][0];
      }

      //create the event, and populate it with event name, admin, dates, and time slots
      Event readEvent(eventName, eventAdminName, strDates.size(), strDates);
      readEvent.setTimes(timeSlotsArr);

      //read the tasks
      std::vector<std::string> strTaskList = split(strEventParts[3], '~'); //Tasks
      for(int taskIndex = 0; taskIndex < strTaskList.size(); taskIndex++)
      {
        std::vector<std::string>  strTaskParts = split(strTaskList[taskIndex], ';');
        readEvent.addTask(strTaskParts[0]); //stores the task name
        if(std::toLower(strTaskParts[1]) == "1")
        {
          readEvent.signUpTask(strTaskParts[2],strTaskParts[0]); //sign up for a task
        }
      }
      eventsVector.push_back(readEvent);
    }
    inFile.close();
  }
}

Executive::~Executive()
{
	std::ofstream outFile;
  outFile.open(fileName);
  //go through all the events
  for (int eventIndex = 1; eventIndex <= eventList.size(); eventIndex++)
  {
    Event writeEvent = eventList[eventIndex];
    outFile << writeEvent.getName() << ',';  //write the event name
    outFile << writeEvent.getAdminName() << ',';  //write the admin name
    for(int dateIndex = 0; dateIndex < writeEvent.getNumOfDays(); dateIndex++)
    {
      outFile << writeEvent.getDates()[dateIndex] << '~';  //write the date of the event
      for(int timeIndex = 0; timeIndex < 54; timeIndex++)
      {
        TimeSlots* ts = writeEvent.getTimes()[dateIndex][timeIndex];
        outFile << ts->getIndex() << ';';  //write the index of the time slot
        outFile << ts->getNum();  //write the number of attendees
        if(timeIndex < 53 || ts->getNum() != 0)
        {
           outFile << ';';
        }
        for(int attendeesIndex = 0; attendeesIndex < ts->getNum(); attendeesIndex++)
        {
          outFile << ts->getAttendees()[attendeesIndex];  //write the attendees if they exist
          if(attendeesIndex < ts->getNum()-1|)
            outFile << ';';
        }
        if(attendeesIndex < 53)
          outFile << '|';
      }
      if(dateIndex <  writeEvent.getNumOfDays()-1)
        outFile << '~';
    }
    outFile << ',';
    std::vector<Task> eTasks = writeEvent.getTasks();
    for(int taskIndex = 0; taskIndex < eTasks.size(); taskIndex++)
    {
      outFile << eTasks[taskIndex].getTaskName() << ';';  //write the task name
      outFile << eTasks[taskIndex].isHandled()  << ';';  //write if the task is being handled
      if(eTasks[taskIndex].isHandled())
        outFile << eTasks[taskIndex].getPersonName() << ';';  //write the person handling the task if they exist
      if(attendeesIndex < 54)
        outFile << '~';
    }
    if(eventIndex != eventList.size())
      outFile << "\n";
  }
  outFile.close();
}

void Executive::setCurrentUser(std::string name)
{
	m_currentUser = name; //set the current user to the name passed in
}

std::string Executive::getCurrentUser() const
{
	return(m_currentUser); //returns the name of the current user
}

Events& Executive::addEvent(std::string eventName, std::string adminName, int numOfDays, std::vector<std::string> dates)
{
	Events* newEvent = new Events(eventName, adminName, numOfDays, dates); //creates a new event with the parameters passed in
	m_eventList.push_back(*newEvent); //adds the event to the back of the event list
	return(*newEvent); //returns the newly created event
}

std::vector<Events> Executive::getEventList() const
{
	return(m_eventList); //returns the vector
}

bool Executive::dateCheck(int y, int m, int d)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int curY = (1900 + ltm->tm_year);
	if (y < curY)
	{
		//std::cout << "The year needs to be this year or later, you cannot create a past event!\n";
		return false;
		if (m <= ltm->tm_mon)
		{
			//std::cout << "The month needs to be this month or later, you cannot create a past event!\n";
			return false;
			if (d <= ltm->tm_mday)
			{
				//std::cout << "The day needs to be this day or later, you cannot create a past event!\n";
				return false;
			}
		}

	}
	if (d < 1)
	{
		//std::cout << "\nThe day must be 1 or higher.\n";
		return false;
	}
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		if (d > 31)
		{
			//std::cout << "\nYou have selected a day outside the range of this month.\n";
			return false;
		}
	}
	else if (m == 4 || m == 6 || m == 9 || m == 11)
	{
		if (d > 30)
		{
			//std::cout << "\nYou have selected a day outside the range of this month.\n";
			return false;
		}
	}
	else if (m == 2)
	{
		if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) //Leap year conditions: cite "crazzyguy101 - cplusplus.com"
		{
			if (d > 29)
			{
				//std::cout << "\nYou have selected a day outside the range of this month.\n";
				return false;
			}
		}
		else
		{
			if (d > 28)
			{
				//std::cout << "\nYou have selected a day outside the range of this month.\n";
				return false;
			}
		}
	}

	const std::string holidays[3] = { "01/01", "07/4","12/25" };
	int size = sizeof(holidays);

	//check if holiday (uses holiday size)
	for (int i = 0; i < size; i++) {
		std::istringstream issholiday(holidays[i]);
		std::string f;
		std::vector<std::string> holiday;
		while (std::getline(issholiday, f, '/')) {
			holiday.push_back(f);
		}
		if (std::stoi(holiday[0]) == m && std::stoi(holiday[1]) == d) {
			return false;
		}
	}
	return true;
}

std::vector<std::string> Executive::split(std::string baseString, char splitChar){
	std::istringstream issBaseString(baseString);
	std::string splitStringPart;
	std::vector<std::string> splitString;
	while (std::getline(issBaseString, splitStringPart, splitChar)) {
		splitString.push_back(splitStringPart);
	}
	return splitString;
}
