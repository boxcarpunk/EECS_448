#include "Executive.h"

Executive::Executive() : fileName("eventlist.txt")
{
	std::ifstream inFile;
	inFile.open(fileName);
	eventList = new LinkedList<Events, std::string>;
	if (inFile.is_open())
	{
		std::string strEventList;
		while (std::getline(inFile, strEventList))
		{
			std::vector<std::string> strEventParts = split(strEventList, ',');

			std::string eventName = strEventParts[0]; //read the event name
			std::string eventAdminName = strEventParts[1]; //read the admin for the event

			std::vector<std::string> strDateParts = split(strEventParts[2], '~'); //get all parts of the date which include the days of the event, the time slots and the attendees
			std::vector<std::string> strDates;
			std::vector<std::string> strTimeSlots;
			std::vector<std::vector<TimeSlots>> timeSlotsVector;

			for (int i = 0; i < strDateParts.size(); i++) //TimeSlots
			{
				if (i % 2 == 0) //read the day of the event
				{
					strDates.push_back(strDateParts[i]);
				}
				else //get the timeslots and the attendees
				{
					strTimeSlots = split(strDateParts[i], '|'); // split all the time slots parts grouped by the time slot
					std::vector<std::string> strTimeSlotsParts; // read all the index, and attendees
						std::vector<TimeSlots> timeSlots; //
					for (int b = 0; b < strTimeSlots.size(); b++)
					{

						strTimeSlotsParts = split(strTimeSlots[b], ';');
						std::string index = strTimeSlotsParts[0]; //read the index of the time slot
							TimeSlots ts(std::stoi(index));
							std::string numOfAttendees = strTimeSlotsParts[1]; // read the number of attendees
							for (int c = 2; c < strTimeSlotsParts.size(); c++) // read all the attendees
							{
								ts.addAttendee(strTimeSlotsParts[c]);
							}
						timeSlots.push_back(ts);
					}
					timeSlotsVector.push_back(timeSlots); //add all timeslots to the 2d timeslots vector
				}
			}

			//convert the 2d vector to a 2d array
			TimeSlots** timeSlotsArr = new TimeSlots*[timeSlotsVector.size()];
			for (int b = 0; b < strDates.size(); b++)
			{
				timeSlotsArr[b] = new TimeSlots[54];
				timeSlotsArr[b] = &timeSlotsVector[b][0];
			}

			//create the event, and populate it with event name, admin, dates, and time slots
			Events readEvent(eventName, eventAdminName, strDates.size(), timeSlotsArr, strDates);
			readEvent.setTimes(timeSlotsArr);

			//read the tasks
			std::vector<std::string> strTaskList = split(strEventParts[3], '~'); //Tasks
			for (int taskIndex = 0; taskIndex < strTaskList.size(); taskIndex++)
			{
				std::vector<std::string>  strTaskParts = split(strTaskList[taskIndex], ';');
				readEvent.addTask(strTaskParts[0]); //stores the task name
				if (strTaskParts[1] == "1")
				{
					readEvent.signUpTask(strTaskParts[2], strTaskParts[0]); //sign up for a task
				}
			}
			eventList->addBack(readEvent);
		}
		inFile.close();
	}
}

Executive::~Executive()
{
	std::ofstream outFile;
	outFile.open(fileName);
	//go through all the events
	for (int eventIndex = 1; eventIndex <= eventList->getLength(); eventIndex++)
	{
		Events writeEvent = eventList->getEntry(eventIndex);
		outFile << writeEvent.getName() << ',';  //write the event name
		outFile << writeEvent.getAdminName() << ',';  //write the admin name
		for (int dateIndex = 0; dateIndex < writeEvent.getNumOfDays(); dateIndex++)
		{
			outFile << writeEvent.getDates()[dateIndex] << '~';  //write the date of the event
			for (int timeIndex = 0; timeIndex < 54; timeIndex++)
			{
				TimeSlots ts = writeEvent.getTimes()[dateIndex][timeIndex];
				outFile << ts.getIndex() << ';';  //write the index of the time slot
				outFile << ts.getNum();  //write the number of attendees
				if (timeIndex < 53 || ts.getNum() != 0)
				{
					outFile << ';';
				}
				for (int attendeesIndex = 0; attendeesIndex < ts.getNum(); attendeesIndex++)
				{
					outFile << ts.getAttendees()[attendeesIndex];  //write the attendees if they exist
					if (attendeesIndex < ts.getNum() - 1 )
						outFile << ';';
				}
				if (timeIndex < 53)
					outFile << '|';
			}
			if (dateIndex <  writeEvent.getNumOfDays() - 1)
				outFile << '~';
		}
		outFile << ',';
		std::vector<Task> eTasks = writeEvent.getTasks();
		for (int taskIndex = 0; taskIndex < eTasks.size(); taskIndex++)
		{
			outFile << eTasks[taskIndex].getTaskName() << ';';  //write the task name
			outFile << eTasks[taskIndex].isHandled() << ';';  //write if the task is being handled
			if (eTasks[taskIndex].isHandled())
				outFile << eTasks[taskIndex].getPersonName() << ';';  //write the person handling the task if they exist
			if (taskIndex < 54)
				outFile << '~';
		}
		if (eventIndex != eventList->getLength())
			outFile << "\n";
	}
	outFile.close();
}

void Executive::run()
{
	bool programStatus = true; //a flag to keep track of the state of the program
	int choice = 0; //an int that stores input from the user
	std::ofstream outFile; //the object used to write to file

	std::cout << "\n-------------------------\nWelcome to cal448!\n-------------------------\n\n";
	while (programStatus == true) //main program loop condition
	{
		std::cout << "Enter your name: \n";
		std::cin >> currentUser;
		std::cout << "Are you an admin or a user?\n  (1) Admin\n  (2) User\n  (3) Quit\n\n  Choice: ";
		std::cin.clear(); //wipes cin
		std::cin >> choice; //takes in and stores the menu input
		while(std::cin.fail()) //fail bit code to recover bad input
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input, please select '1'-'3'\n";
			std::cin >> choice;
		}


		if (choice == 1) //if an admin logs in
		{
			std::cout<<"Which time mode would you like to use?\n  (1) 12-hour\n  (2) 24-hour\n\n Choice: ";
			std::cin.ignore(); //wipes cin
			std::cin>>choice; //takes in and stores the time input
			while(std::cin.fail()) //fail bit code to recover from bad input
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Invalid input, please select '1'-'2'\n";
				std::cin >> choice;
			}

			if(choice == 1) //if 12hr mode
			{
				std::cout << "\n--------- Admin Mode Starting ---------\n";
				timeMode = 12;
				programStatus = adminFunc(true); //goes into admin mode with a 12-hr format
			}
			else //if 24hr mode
			{
				std::cout << "\n--------- Admin Mode Starting ---------\n";
				timeMode = 24;
				programStatus = adminFunc(false); //goes into admin mode with a 24-hr format
			}
		}
		else if (choice == 2) //if a user logs in
		{
			std::cout<<"Which time mode?\n  (1) 12-hour\n  (2) 24-hour\n\n Choice: ";
			std::cin.ignore(); //wipes cin
			std::cin>>choice; //takes in and stores the time input
			while(std::cin.fail()) //fail bit code to recover from bad input
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Invalid input, please select '1'-'2'\n";
				std::cin >> choice;
			}
			if(choice == 1) //if 12hr mode
			{
				std::cout << "\n--------- User Mode Starting ---------\n";
				programStatus = userFunc(true); //goes into user mode with a 12-hr format
			}
			else //if 24hr mode
			{
				std::cout << "\n--------- User Mode Starting ---------\n";
				programStatus = userFunc(false); //goes into user mode with a 24-hr format
			}
		}
		else if(choice == 3) //if exiting the program
		{
			std::cout << "Thank you for using cal448!\n";
			break; //breaks out of the while loop
		}
		else //if not 1-3
		{
			std::cout<<"\nInvalid input. Try again: \n";
		}
	}
	outFile.open("eventslist.txt"); //opens the file
	for (int i=1; i<=eventList->getLength(); i++) //goes through the event list
	{
		Events temp = eventList->getEntry(i); //stores an event in a temp variable
		outFile << temp.getName() << ",";
		for (int i = 0; i < temp.getDates().size(); i++)
		{
			outFile << temp.getDates()[i]; //writes the event info to file
		}
		if (!temp.getTimeSlots()->isEmpty()) //if there are time slots for the event
		{
			for (int j=1; j<=temp.getTimeSlots()->getLength(); j++) //goes through the time slots
			{
				outFile << "." << temp.getTimeSlots()->getEntry(j).getTimeSlot() << "," << temp.getTimeSlots()->getEntry(j).getNum() << ","; //writes the time slot info to file
			}
		}
	}
	outFile.close(); //closes the file
}

bool Executive::adminFunc(bool mode12)
{
	int adminChoice = 0; //an int that stores input from the user
	while (1) //runs infinitely
	{
		std::cout << "\nCurrently logged in as admin... How would you like to proceed?\n\n";
		std::cout << "  (1) Add an event\n  (2) Print all events\n  (3) Find a specific event\n  (4) Main Menu\n  (5) Quit\n\n  Choice: ";
		std::cin.ignore(); //wipes cin
		std::cin >> adminChoice; //takes in and stores the menu input
		while(std::cin.fail()) //fail bit code to recover from bad input
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input, please select '1'-'5'\n";
			std::cin >> adminChoice;
		}

		if (adminChoice == 1) //if add an event
		{
			if (addEvent(mode12)) //if the event could be added
			{
				std::cout << "\nYour event has been added!\n";
			}
			else //if the function could not add the event
			{
				std::cout << "There was an issue creating your event, please try again\n";
			}
		}
		else if (adminChoice == 2) //if print all events
		{
			printEvents(); //calls print events
		}
		else if (adminChoice == 3) //if find a specific event
		{
			std::string nameToSearch = ""; //creates a variable that stores the name of the event
			std::cout << "\nPlease enter the name of the event you would like to pull up: ";
			std::cin.ignore(); //wipes cin
			std::getline(std::cin, nameToSearch); //takes in the name of the event
			if (eventList->isFound(nameToSearch)) //if the event is in the list
			{
				std::cout << "\nThe event was found: " << nameToSearch << "\n\n"; //notifies the user that the event was found
				Events event = eventList->search(nameToSearch); //retrieves the event
				event.getInfo(); //prints the event info
				std::cout << "\nThere are " << event.getTimeSlots()->getLength() << " time slots in this event.\n"; //prints the amount of time slots for the event
				for (int i=1; i<=event.getTimeSlots()->getLength(); i++) //runs through the time slots
				{
					std::cout << "There are " << event.getTimeSlots()->getEntry(i).getNum() << " people available at " << event.getTimeSlots()->getEntry(i).getTimeSlot() << ".\n"; //prints the number of attendees at each time slot
				}
			}
			else //if the event is not in the list
			{
				std::cout << "\nThe event was not found\n"; //notify the user that the event was not found
			}
		}
		else if (adminChoice == 4) //if main menu
		{
			return true; //return true to run to go back to the main menu
		}
		else if (adminChoice == 5) //if quit
		{
			return false; //return false to run to quit the program
		}
		else //if not 1-5
		{
			std::cout << "\nPlease enter a valid choice\n";
		}
	}
}

bool Executive::userFunc(bool mode12)
{
	int userChoice = 0; //an int that stores input from the user
	while(1) //runs indefinitely
	{
		std::cout << "\nCurrently logged in as user... How would you like to proceed?\n";
		std::cout << "  (1) Print all events\n  (2) Find a specific event\n  (3) Main Menu\n  (4) Quit\n\n  Choice: ";
		std::cin.ignore(); //wipes cin
		std::cin >> userChoice; //takes in and stores the menu input
		while(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input, please select '1'-'4'\n";
			std::cin >> userChoice;
		}

		if (userChoice == 1) //if print all events
		{
			printEvents(); //prints the events
		}
		else if (userChoice == 2) //if find a specific event
		{
			std::string nameToSearch = ""; //creates a variable to store the name of the event
			std::cout << "\nPlease enter the name of the event you would like to pull up: ";
			std::cin.ignore(); //wipes cin
			std::getline(std::cin, nameToSearch); //takes in the name of the event
			if ((eventList->isFound(nameToSearch)) == true) //if the event is in the list
			{
				std::cout << "\nThe event was found: " << nameToSearch << "\n\n";
				std::cout <<"Would you like to attend this event?\n";
				std::cout <<"  (1) Yes\n  (2) No\n\n";
				//std::cin.ignore(); //wipes cin
				std::cin >> userChoice; //takes in and stores the attend input
				while(std::cin.fail()) //fail bit code to recover from bad input
				{
					std::cin.clear();
					std::cin.ignore();
					std::cout << "Invalid input, please select '1'-'2'\n";
					std::cin >> userChoice;
				}

				while((userChoice != 1) && (userChoice != 2)) //while the input is not 1 or 2
				{
					std::cout <<"Not a Valid Input, Try Again....\n";
					std::cin.ignore(); //wipes cin
					std::cin >> userChoice; //takes in and stores the attend input
					while (std::cin.fail()) //fail bit code to recover from bad input
					{
						std::cin.clear();
						std::cin.ignore();
						std::cout << "Invalid input, please select '1'-'2'\n";
						std::cin >> userChoice;
					}

				}
				if(userChoice == 1) //if the user would like to attend the event
				{
					Events temp = eventList -> search(nameToSearch); //stores the event
					/*for(int i = 1; i <= temp.getTimeSlots() -> getLength(); i++) //runs through the time slots
					{
						std::cout <<"(" << i << ") " << temp.getTimeSlots() -> getEntry(i).getTimeSlot() << "\n"; //prints the time slot
						std::cout <<"Are you Available for this Time Slot?\n (1)Yes\n (2)No\n";
						std::cin.ignore(); //wipes cin
						std::cin >> userChoice; //takes in and stores the availability input
						while (std::cin.fail()) //fail bit code to recover from bad input
						{
							std::cin.clear();
							std::cin.ignore();
							std::cout << "Invalid input, please select '1'-'2'\n";
							std::cin >> userChoice;
						}
						while(userChoice != 1 && userChoice != 2) //while the input is not 1 or 2
						{
							std::cout <<"Invalid Input Try Again!\n";
							std::cin.ignore(); //wipes cin
							std::cin >> userChoice; //takes in and stores the availability input
							while (std::cin.fail()) //fail bit code to recover from bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input, please select '1'-'2'\n";
								std::cin >> userChoice;
							}
						}
						if(userChoice == 1) //if the user is available
						{
							temp.getTimeSlots() -> getEntry(i).increaseAtt(); //increases the attendees for that time slot
							std::cout <<"You have been added to the list. Thank You!\n\n";
						}
						else //if the user is not available
						{
							std::cout << "Thank You! You will not be added to the Attendee list!\n\n";
						}
					}*/


					int taskNum = temp.getTasks().size();
					std::cout << "Sign up for task(s):\n";
					for (int o = 0; o < taskNum; o++)
					{
						std::cout << o + 1 << ") " << temp.getTasks()[o].getTaskName() << std::endl;
					}
					std::cout <<taskNum+1 << ") None\n";
					int taskSelection = 0;
					std::cin >> taskSelection;
					while (std::cin.fail()) //fail bit code to recover bad input
					{
						std::cin.clear();
						std::cin.ignore();
						std::cout << "Invalid input\n";
						std::cin >> taskSelection;
					}
					if (taskSelection <= taskNum)
					{
						bool test = temp.signUpTask(currentUser, temp.getTasks()[taskSelection-1].getTaskName());

						eventList->search(nameToSearch) = temp;
					}
					else
					{
						//no task handled
					}
					AddAvailability(temp);
				}
			}
			else //if the event is not in the list
			{
				std::cout << "\nThe event was not found\n"; //notify the user that the event was not found
			}
		}
		else if (userChoice == 3) //if main menu
		{
			return true; //return true to run to keep the program running
		}
		else if (userChoice == 4) //if quit
		{
			return false; //return false to run to end the program
		}
		else //if not 1-4
		{
			std::cout << "\nPlease enter a valid choice\n";
		}
	}
}

bool Executive::addEvent(bool mode12)
{
	std::string name = ""; //creates a placeholder variable for a name of an event
	int month = 0; //creates a placeholder variable for a month of an event
	int day = 0; //creates a placeholder variable for a day of an event
	int year = 0; //creates a placeholder variable for a year of an event
	int numOfDays = 0;

	std::cout << "\nWhat is the name of your event?\n";
	std::cin.ignore(); //wipes cin
	std::getline(std::cin, name); //gets the name of the event
	std::cout << "How many days would you like to add?\n";
	//TODO: Error check input
	std::cin >> numOfDays;
	while (std::cin.fail()) //fail bit code to recover bad input
	{
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Invalid input\n";
		std::cin >> numOfDays;
	}

	TimeSlots** myArray = new TimeSlots*[numOfDays];
	for (int i = 0; i < numOfDays; i++)
	{
		myArray[i] = new TimeSlots[54];
	}

	Events event1(name, currentUser, numOfDays, myArray);
	std::string m_months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	for (int i = 0; i < numOfDays; i++)
	{
		std::cout << "Day " << i+1 << ": \n";
		while (1) //runs infinitely
		{
			std::cout << "\nWhat year will your event take place?\n";
			std::cin >> year; //takes in the year
			while (std::cin.fail()) //fail bit code to recover from bad input
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Invalid input, please enter a year\n";
				std::cin >> year;
			}
			std::cout << "\nWhat month will your event take place?\n";
			for (int i = 0; i < 12; i++)
			{
				std::cout << "  (" << i + 1 << ")" << " " << m_months[i] << std::endl;
			}
			std::cin >> month; //takes in the month
			while (std::cin.fail()) //fail bit code to recover from bad input
			{
				std::cin.clear();
				std::cout << "Invalid input, please select '1'-'12'\n";
				std::cin >> month;
			}
			std::cout << "\nWhat day will your event take place?\n";
			std::cin.ignore(); //wipes cin
			std::cin >> day; //takes in the day
			while (std::cin.fail()) //fail bit code to recover from bad input
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Invalid input, please enter a day\n";
				std::cin >> day;
			}

			if (dateCheck(year, month, day) == true) //if the date is valid
			{
				break; //break out of the while loop
			}
			else //if the date is invalid
			{
				std::cout << "\nThis date is invalid, please enter a valid date\n"; //notify the user that the date is invalid
			}
		}
		std::string strMonth, strDay, strYear, date;
		strMonth = std::to_string(month);
		strDay = std::to_string(day);
		strYear = std::to_string(year);

		if (strMonth.length() == 1)
		{
			strMonth = "0" + strMonth;
		}

		if (strDay.length() == 1)
		{
			strDay = "0" + strDay;
		}

		date = strMonth + "/" + strDay + "/" + strYear;

		event1.setDates(date);

		/*std::string year, month, day;
		//std::string date = dates[0];
		day = date.substr(0, 2);
		month = date.substr(3, 2);
		year = date.substr(6, 10);
		std::cout << "\n" << m_name << " is occuring on " << month << "/" << day << "/" << year << ".\n"; //prints the name and date of the event*/

	}

	std::string taskOption = "";
	std::cout << "Would you like to add tasks?\n";
	std::cin >> taskOption;

	if (taskOption == "y" || taskOption == "Y")
	{
		int taskCount = 0;
		std::cout << "How many tasks would you like to add?\n";
		std::cin >> taskCount;
		while (std::cin.fail()) //fail bit code to recover bad input
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input\n";
			std::cin >> taskCount;
		}
		std::string task;

		std::cin.ignore();
		for (int i = 0; i < taskCount; i++)
		{
			std::cout << "Enter task " << i+1<<":\n";
			std::getline(std::cin, task);
			event1.addTask(task);
		}
	}

	eventList->addBack(event1);
	eventList->sort();

	AddAvailability(event1);

	return true;
}

void Executive::AddAvailability(Events event1)
{
	TimeSlots** myArray = new TimeSlots*[event1.getNumOfDays()];
	for (int i = 0; i < event1.getNumOfDays(); i++)
	{
		myArray[i] = new TimeSlots[54];
	}

	TimeSlots** temp = event1.getTimes();

	for (int i = 0; i < event1.getNumOfDays(); i++)
	{
		for (int j = 0; j < 54; j++)
		{
			myArray[i][j] = temp[i][j];
		}
	}

	for (int i = 0; i < event1.getNumOfDays(); i++)
	{
		std::cout << "Day #" << event1.getNumOfDays() << std::endl;
		std::string strCopy;
		bool copy = false;
		if (i > 0)
		{
			std::cout << "Copy the previous day's times? (y/n)\n";
			//TODO Error check input
			std::cin >> strCopy;
			while (std::cin.fail()) //fail bit code to recover bad input
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "Invalid input\n";
				std::cin >> strCopy;
			}
			if (strCopy == "y" || strCopy == "Y")
			{
				copy = true;
			}
			else if (strCopy == "n" || strCopy == "N")
			{
				copy = false;
			}
			TimeSlots** myNewArray = event1.getTimes();


				for (int j = 0; j < 54; j++)
				{
					myArray[i][j] = myNewArray[i-1][j];
				}
			//std::cin.ignore();
		}

		if(!copy)
		{
			if (timeMode == 12) //if 12-hr mode
			{


				int hourSelection = 0;
				do
				{
					//std::cin.ignore();
					hourSelection = 0;
					std::cout << "Select Time\n";
					std::cout << "1) 5:00 AM\n";
					std::cout << "2) 6:00 AM\n";
					std::cout << "3) 7:00 AM\n";
					std::cout << "4) 8:00 AM\n";
					std::cout << "5) 9:00 AM\n";
					std::cout << "6) 10:00 AM\n";
					std::cout << "7) 11:00 AM\n";
					std::cout << "8) 1:00 PM\n";
					std::cout << "9) 2:00 PM\n";
					std::cout << "10) 3:00 PM\n";
					std::cout << "11) 4:00 PM\n";
					std::cout << "12) 5:00 PM\n";
					std::cout << "13) 6:00 PM\n";
					std::cout << "14) 7:00 PM\n";
					std::cout << "15) 8:00 PM\n";
					std::cout << "16) 9:00 PM\n";
					std::cout << "17) 10:00 PM\n";
					std::cout << "18) 11:00 PM\n";
					std::cout << "19) Finish\n";
					std::cin >> hourSelection;
					while (std::cin.fail()) //fail bit code to recover bad input
					{
						std::cin.clear();
						std::cin.ignore();
						std::cout << "Invalid input, please select '1'-'19'\n";
						std::cin >> hourSelection;
					}
					if (hourSelection == 1)
					{
						std::cout << "1) 5:00 - 5:20 AM\n";
						std::cout << "2) 5:20 - 5:40 AM\n";
						std::cout << "3) 5:40 - 6:00 AM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 1)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input, please select '1'-'5'\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 0 = true
									
									myArray[i][0].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 1 = true
									
									myArray[i][1].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 2 = true
									
									myArray[i][2].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									
									myArray[i][0].addAttendee(currentUser);
									
									myArray[i][1].addAttendee(currentUser);
									
									myArray[i][2].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input, please select '1'-'5'\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 2)
					{
						std::cout << "1) 6:00 - 6:20 AM\n";
						std::cout << "2) 6:20 - 6:40 AM\n";
						std::cout << "3) 6:40 - 7:00 AM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 2)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input, please select '1'-'4'\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 3 = true
									
									myArray[i][3].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 4 = true
									
									myArray[i][4].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 5 = true
									
									myArray[i][5].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 3,4,5 = true
									
									myArray[i][3].addAttendee(currentUser);
									
									myArray[i][4].addAttendee(currentUser);
									
									myArray[i][5].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 3)
					{
						std::cout << "1) 7:00 - 7:20 AM\n";
						std::cout << "2) 7:20 - 7:40 AM\n";
						std::cout << "3) 7:40 - 8:00 AM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 3)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 6 = true
									
									myArray[i][6].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 7 = true
									
									myArray[i][7].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 8 = true
									
									myArray[i][8].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 6,7,8 = true
									
									myArray[i][6].addAttendee(currentUser);
									
									myArray[i][7].addAttendee(currentUser);
									
									myArray[i][8].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 4)
					{
						std::cout << "1) 8:00 - 8:20 AM\n";
						std::cout << "2) 8:20 - 8:40 AM\n";
						std::cout << "3) 8:40 - 9:00 AM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 4)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 9 = true
									
									myArray[i][9].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 10 = true
									
									myArray[i][10].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 11 = true
									
									myArray[i][11].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 9,10,11 = true
									
									myArray[i][9].addAttendee(currentUser);
									
									myArray[i][10].addAttendee(currentUser);
									
									myArray[i][11].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 5)
					{
						std::cout << "1) 9:00 - 9:20 AM\n";
						std::cout << "2) 9:20 - 9:40 AM\n";
						std::cout << "3) 9:40 - 10:00 AM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 5)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 12 = true
									
									myArray[i][12].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 13 = true
									
									myArray[i][13].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 14 = true
									
									myArray[i][14].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 12,13,14 = true
									
									myArray[i][12].addAttendee(currentUser);
									
									myArray[i][13].addAttendee(currentUser);
									
									myArray[i][14].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 6)
					{
						std::cout << "1) 10:00 - 10:20 AM\n";
						std::cout << "2) 10:20 - 10:40 AM\n";
						std::cout << "3) 10:40 - 11:00 AM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 6)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 15 = true
									
									myArray[i][15].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 16 = true
									
									myArray[i][16].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 17 = true
									
									myArray[i][17].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 15,16,17 = true
									
									myArray[i][15].addAttendee(currentUser);
									
									myArray[i][16].addAttendee(currentUser);
									
									myArray[i][17].addAttendee(currentUser);

								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 7)
					{
						std::cout << "1) 11:00 - 11:20 AM\n";
						std::cout << "2) 11:20 - 11:40 AM\n";
						std::cout << "3) 11:40 - 12:00 PM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 7)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 18 = true
									
									myArray[i][18].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 19 = true
									
									myArray[i][19].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 20 = true
									
									myArray[i][20].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 18,19,20 = true
									
									myArray[i][18].addAttendee(currentUser);
									
									myArray[i][19].addAttendee(currentUser);
									
									myArray[i][20].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 8)
					{
						std::cout << "1) 1:00 - 1:20 PM\n";
						std::cout << "2) 1:20 - 1:40 PM\n";
						std::cout << "3) 1:40 - 2:00 PM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 8)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 21 = true
									
									myArray[i][21].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 22 = true
									
									myArray[i][22].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 23 = true
									
									myArray[i][23].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 21,22,23 = true
									
									myArray[i][21].addAttendee(currentUser);
									
									myArray[i][22].addAttendee(currentUser);
									
									myArray[i][23].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 9)
					{
						std::cout << "1) 2:00 - 2:20 PM\n";
						std::cout << "2) 2:20 - 2:40 PM\n";
						std::cout << "3) 2:40 - 3:00 PM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 9)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 24 = true
									
									myArray[i][24].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 25 = true
									
									myArray[i][25].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 26 = true
									
									myArray[i][26].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 24,25,26 = true
									
									myArray[i][24].addAttendee(currentUser);
									
									myArray[i][25].addAttendee(currentUser);
									
									myArray[i][26].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 10)
					{
						std::cout << "1) 3:00 - 3:20 PM\n";
						std::cout << "2) 3:20 - 3:40 PM\n";
						std::cout << "3) 3:40 - 4:00 PM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 10)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 27 = true
									
									myArray[i][27].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 28 = true
									
									myArray[i][28].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 29 = true
									
									myArray[i][29].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 27,28,29 = true
									
									myArray[i][27].addAttendee(currentUser);
									
									myArray[i][28].addAttendee(currentUser);
									
									myArray[i][29].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 11)
					{
						std::cout << "1) 4:00 - 4:20 PM\n";
						std::cout << "2) 4:20 - 4:40 PM\n";
						std::cout << "3) 4:40 - 5:00 PM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 11)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 30 = true
									
									myArray[i][30].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 31 = true
									
									myArray[i][31].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 32 = true
									
									myArray[i][32].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 30,31,32 = true
									
									myArray[i][30].addAttendee(currentUser);
									
									myArray[i][31].addAttendee(currentUser);
									
									myArray[i][32].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 12)
					{
						std::cout << "1) 5:00 - 5:20 PM\n";
						std::cout << "2) 5:20 - 5:40 PM\n";
						std::cout << "3) 5:40 - 6:00 PM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 12)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 33 = true
									
									myArray[i][33].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 34 = true
									
									myArray[i][34].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 35 = true
									
									myArray[i][35].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 33,34,35 = true
									
									myArray[i][33].addAttendee(currentUser);
									
									myArray[i][34].addAttendee(currentUser);
									
									myArray[i][35].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 13)
					{
						std::cout << "1) 6:00 - 6:20 PM\n";
						std::cout << "2) 6:20 - 6:40 PM\n";
						std::cout << "3) 6:40 - 7:00 PM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 13)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 36 = true
									
									myArray[i][36].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 37 = true
									
									myArray[i][37].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 38 = true
									
									myArray[i][38].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 36,37,38 = true
									
									myArray[i][36].addAttendee(currentUser);
									
									myArray[i][37].addAttendee(currentUser);
									
									myArray[i][38].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 14)
					{
						std::cout << "1) 7:00 - 7:20 PM\n";
						std::cout << "2) 7:20 - 7:40 PM\n";
						std::cout << "3) 7:40 - 8:00 PM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 14)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 39 = true
									
									myArray[i][39].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 40 = true
									
									myArray[i][40].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 41 = true
									
									myArray[i][41].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 39,40,41 = true
									
									myArray[i][39].addAttendee(currentUser);
									
									myArray[i][40].addAttendee(currentUser);
									
									myArray[i][41].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 15)
					{
						std::cout << "1) 8:00 - 8:20 PM\n";
						std::cout << "2) 8:20 - 8:40 PM\n";
						std::cout << "3) 8:40 - 9:00 PM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 15)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 42 = true
									
									myArray[i][42].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 43 = true
									
									myArray[i][43].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 44 = true
									
									myArray[i][44].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 42,43,44 = true
									
									myArray[i][42].addAttendee(currentUser);
									
									myArray[i][43].addAttendee(currentUser);
									
									myArray[i][44].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 16)
					{
						std::cout << "1) 9:00 - 9:20 PM\n";
						std::cout << "2) 9:20 - 9:40 PM\n";
						std::cout << "3) 9:40 - 10:00 PM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 16)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 45 = true
									
									myArray[i][45].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 46 = true
									
									myArray[i][46].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 47 = true
									
									myArray[i][47].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 45,46,47 = true
									
									myArray[i][45].addAttendee(currentUser);
									
									myArray[i][46].addAttendee(currentUser);
									
									myArray[i][47].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 17)
					{
						std::cout << "1) 10:00 - 10:20 PM\n";
						std::cout << "2) 10:20 - 10:40 PM\n";
						std::cout << "3) 10:40 - 11:00 PM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 17)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 48 = true
									
									myArray[i][48].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 49 = true
									
									myArray[i][49].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 50 = true
									
									myArray[i][50].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 48,49,50 = true
									
									myArray[i][48].addAttendee(currentUser);
									
									myArray[i][49].addAttendee(currentUser);
									
									myArray[i][50].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
					if (hourSelection == 18)
					{
						std::cout << "1) 11:00 - 11:20 PM\n";
						std::cout << "2) 11:20 - 11:40 PM\n";
						std::cout << "3) 11:40 - 12:00 AM\n";
						std::cout << "4) Entire Hour\n";
						std::cout << "5) Go Back\n";
						while (hourSelection == 18)
						{
							int timeSelection = 0;
							while (timeSelection != 5)
							{
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
								if (timeSelection == 1)
								{
									//index 51 = true
									
									myArray[i][51].addAttendee(currentUser);
								}
								else if (timeSelection == 2)
								{
									//index 52 = true
									
									myArray[i][52].addAttendee(currentUser);
								}
								else if (timeSelection == 3)
								{
									//index 53 = true
									
									myArray[i][53].addAttendee(currentUser);
								}
								else if (timeSelection == 4)
								{
									//index 51,52,53 = true
									
									myArray[i][51].addAttendee(currentUser);
									
									myArray[i][52].addAttendee(currentUser);
									
									myArray[i][53].addAttendee(currentUser);
								}
								else if (timeSelection == 5)
								{
									hourSelection = 0;
								}
								else
								{
									std::cout << "Please enter a valid selection:\n";
									std::cin >> timeSelection;
									while (std::cin.fail()) //fail bit code to recover bad input
									{
										std::cin.clear();
										std::cin.ignore();
										std::cout << "Invalid input\n";
										std::cin >> timeSelection;
									}
								}
							}
						}
					}
				} while (hourSelection != 19);
			}
			else if (timeMode == 24) //if 12-hr mode
		{
			int hourSelection = 0;
			do
			{
				std::cout << "Select Time\n";
				std::cout << "1) 05:00\n";
				std::cout << "2) 06:00\n";
				std::cout << "3) 07:00\n";
				std::cout << "4) 08:00\n";
				std::cout << "5) 09:00\n";
				std::cout << "6) 10:00\n";
				std::cout << "7) 11:00\n";
				std::cout << "8) 13:00\n";
				std::cout << "9) 14:00\n";
				std::cout << "10) 15:00\n";
				std::cout << "11) 16:00\n";
				std::cout << "12) 17:00\n";
				std::cout << "13) 18:00\n";
				std::cout << "14) 19:00\n";
				std::cout << "15) 20:00\n";
				std::cout << "16) 21:00\n";
				std::cout << "17) 22:00\n";
				std::cout << "18) 23:00\n";
				std::cout << "19) Finish\n";

				std::cin >> hourSelection;
				while (std::cin.fail()) //fail bit code to recover bad input
				{
					std::cin.clear();
					std::cin.ignore();
					std::cout << "Invalid input\n";
					std::cin >> hourSelection;
				}
				if (hourSelection == 1)
				{
					std::cout << "1) 05:00 - 05:20\n";
					std::cout << "2) 05:20 - 05:40\n";
					std::cout << "3) 05:40 - 06:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 1)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 0 = true
								
								myArray[i][0].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 1 = true
								
								myArray[i][1].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 2 = true
								
								myArray[i][2].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 0,1,2 = true
								
								myArray[i][0].addAttendee(currentUser);
								
								myArray[i][1].addAttendee(currentUser);
								
								myArray[i][2].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 2)
				{
					std::cout << "1) 06:00 - 06:20\n";
					std::cout << "2) 06:20 - 06:40\n";
					std::cout << "3) 06:40 - 07:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 2)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 3 = true
								
								myArray[i][3].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 4 = true
								
								myArray[i][4].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 5 = true
								
								myArray[i][5].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 3,4,5 = true
								
								myArray[i][3].addAttendee(currentUser);
								
								myArray[i][4].addAttendee(currentUser);
								
								myArray[i][5].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 3)
				{
					std::cout << "1) 07:00 - 07:20\n";
					std::cout << "2) 07:20 - 07:40\n";
					std::cout << "3) 07:40 - 08:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 3)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 6 = true
								
								myArray[i][6].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 7 = true
								
								myArray[i][7].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 8 = true
								
								myArray[i][8].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 6,7,8 = true
								
								myArray[i][6].addAttendee(currentUser);
								
								myArray[i][7].addAttendee(currentUser);
								
								myArray[i][8].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 4)
				{
					std::cout << "1) 08:00 - 08:20\n";
					std::cout << "2) 08:20 - 08:40\n";
					std::cout << "3) 08:40 - 09:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 4)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 9 = true
								
								myArray[i][9].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 10 = true
								
								myArray[i][10].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 11 = true
								
								myArray[i][11].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 9,10,11 = true
								
								myArray[i][9].addAttendee(currentUser);
								
								myArray[i][10].addAttendee(currentUser);
								
								myArray[i][11].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 5)
				{
					std::cout << "1) 09:00 - 09:20\n";
					std::cout << "2) 09:20 - 09:40\n";
					std::cout << "3) 09:40 - 10:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 5)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 12 = true
								
								myArray[i][12].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 13 = true
								
								myArray[i][13].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 14 = true
								
								myArray[i][14].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 12,13,14 = true
								
								myArray[i][12].addAttendee(currentUser);
								
								myArray[i][13].addAttendee(currentUser);
								
								myArray[i][14].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 6)
				{
					std::cout << "1) 10:00 - 10:20\n";
					std::cout << "2) 10:20 - 10:40\n";
					std::cout << "3) 10:40 - 11:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 6)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 15 = true
								
								myArray[i][15].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 16 = true
								
								myArray[i][16].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 17 = true
								
								myArray[i][17].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 15,16,17 = true
								
								myArray[i][15].addAttendee(currentUser);
								
								myArray[i][16].addAttendee(currentUser);
								
								myArray[i][17].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 7)
				{
					std::cout << "1) 11:00 - 11:20 AM\n";
					std::cout << "2) 11:20 - 11:40 AM\n";
					std::cout << "3) 11:40 - 12:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 7)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 18 = true
								
								myArray[i][18].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 19 = true
								
								myArray[i][19].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 20 = true
								
								myArray[i][20].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 18,19,20 = true
								
								myArray[i][18].addAttendee(currentUser);
								
								myArray[i][19].addAttendee(currentUser);
								
								myArray[i][20].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 8)
				{
					std::cout << "1) 13:00 - 13:20\n";
					std::cout << "2) 13:20 - 13:40\n";
					std::cout << "3) 13:40 - 14:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 8)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 21 = true
								
								myArray[i][21].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 22 = true
								
								myArray[i][22].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 23 = true
								
								myArray[i][23].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 21,22,23 = true
								
								myArray[i][21].addAttendee(currentUser);
								
								myArray[i][22].addAttendee(currentUser);
								
								myArray[i][23].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 9)
				{
					std::cout << "1) 14:00 - 14:20\n";
					std::cout << "2) 14:20 - 14:40\n";
					std::cout << "3) 14:40 - 15:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 9)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 24 = 
								
								myArray[i][24].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 25 = true
								
								myArray[i][25].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 26 = true
								
								myArray[i][26].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 24,25,26 = true
								
								myArray[i][24].addAttendee(currentUser);
								
								myArray[i][25].addAttendee(currentUser);
								
								myArray[i][26].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 10)
				{
					std::cout << "1) 15:00 - 15:20\n";
					std::cout << "2) 15:20 - 15:40\n";
					std::cout << "3) 15:40 - 16:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 10)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 27 = true
								
								myArray[i][27].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 28 = true
								
								myArray[i][28].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 29 = true
								
								myArray[i][29].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 27,28,29 = true
								
								myArray[i][27].addAttendee(currentUser);
								
								myArray[i][28].addAttendee(currentUser);
								
								myArray[i][29].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 11)
				{
					std::cout << "1) 16:00 - 16:20\n";
					std::cout << "2) 16:20 - 16:40\n";
					std::cout << "3) 16:40 - 17:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 11)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 30 = true
								
								myArray[i][30].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 31 = true
								
								myArray[i][31].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 32 = true
								
								myArray[i][32].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 30,31,32 = true
								
								myArray[i][30].addAttendee(currentUser);
								
								myArray[i][31].addAttendee(currentUser);
								
								myArray[i][32].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 12)
				{
					std::cout << "1) 17:00 - 17:20\n";
					std::cout << "2) 17:20 - 17:40\n";
					std::cout << "3) 17:40 - 18:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 12)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 33 = true
								
								myArray[i][33].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 34 = true
								
								myArray[i][34].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 35 = true
								
								myArray[i][35].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 33,34,35 = true
								
								myArray[i][33].addAttendee(currentUser);
								
								myArray[i][34].addAttendee(currentUser);
								
								myArray[i][35].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 13)
				{
					std::cout << "1) 18:00 - 18:20\n";
					std::cout << "2) 18:20 - 18:40\n";
					std::cout << "3) 18:40 - 19:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 13)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 36 = true
								
								myArray[i][36].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 37 = true
								
								myArray[i][37].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 38 = true
								
								myArray[i][38].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 36,37,38 = true
								
								myArray[i][36].addAttendee(currentUser);
								
								myArray[i][37].addAttendee(currentUser);
								
								myArray[i][38].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 14)
				{
					std::cout << "1) 19:00 - 19:20\n";
					std::cout << "2) 19:20 - 19:40\n";
					std::cout << "3) 19:40 - 20:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 14)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 39 = true
								
								myArray[i][39].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 40 = true
								
								myArray[i][40].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 41 = true
								
								myArray[i][41].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 39,40,41 = true
								
								myArray[i][39].addAttendee(currentUser);
								
								myArray[i][40].addAttendee(currentUser);
								
								myArray[i][41].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 15)
				{
					std::cout << "1) 20:00 - 20:20\n";
					std::cout << "2) 20:20 - 20:40\n";
					std::cout << "3) 20:40 - 21:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 15)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 42 = true
								
								myArray[i][42].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 43 = true
								
								myArray[i][43].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 44 = true
								
								myArray[i][44].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 42,43,44 = true
								
								myArray[i][42].addAttendee(currentUser);
								
								myArray[i][43].addAttendee(currentUser);
								
								myArray[i][44].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 16)
				{
					std::cout << "1) 21:00 - 21:20\n";
					std::cout << "2) 21:20 - 21:40\n";
					std::cout << "3) 21:40 - 22:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 16)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 45 = true
								
								myArray[i][45].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 46 = true
								
								myArray[i][46].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 47 = true
								
								myArray[i][47].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 45,46,47 = true
								
								myArray[i][45].addAttendee(currentUser);
								
								myArray[i][46].addAttendee(currentUser);
								
								myArray[i][47].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 17)
				{
					std::cout << "1) 22:00 - 22:20\n";
					std::cout << "2) 22:20 - 22:40\n";
					std::cout << "3) 22:40 - 23:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 17)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 48 = true
								
								myArray[i][48].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 49 = true
								
								myArray[i][49].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 50 = true
								
								myArray[i][50].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 48,49,50 = true
								
								myArray[i][48].addAttendee(currentUser);
								
								myArray[i][49].addAttendee(currentUser);
								
								myArray[i][50].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
				if (hourSelection == 18)
				{
					std::cout << "1) 23:00 - 23:20\n";
					std::cout << "2) 23:20 - 23:40\n";
					std::cout << "3) 23:40 - 00:00\n";
					std::cout << "4) Entire Hour\n";
					std::cout << "5) Go Back\n";
					while (hourSelection == 18)
					{
						int timeSelection = 0;
						while (timeSelection != 5)
						{
							std::cin >> timeSelection;
							while (std::cin.fail()) //fail bit code to recover bad input
							{
								std::cin.clear();
								std::cin.ignore();
								std::cout << "Invalid input\n";
								std::cin >> timeSelection;
							}
							if (timeSelection == 1)
							{
								//index 51 = 
								
								myArray[i][51].addAttendee(currentUser);
							}
							else if (timeSelection == 2)
							{
								//index 52 = true
								
								myArray[i][52].addAttendee(currentUser);
							}
							else if (timeSelection == 3)
							{
								//index 53 = true
								
								myArray[i][53].addAttendee(currentUser);
							}
							else if (timeSelection == 4)
							{
								//index 51,52,53 = true
								
								myArray[i][51].addAttendee(currentUser);
								
								myArray[i][52].addAttendee(currentUser);
								
								myArray[i][53].addAttendee(currentUser);
							}
							else if (timeSelection == 5)
							{
								hourSelection = 0;
							}
							else
							{
								std::cout << "Please enter a valid selection:\n";
								std::cin >> timeSelection;
								while (std::cin.fail()) //fail bit code to recover bad input
								{
									std::cin.clear();
									std::cin.ignore();
									std::cout << "Invalid input\n";
									std::cin >> timeSelection;
								}
							}
						}
					}
				}
			} while (hourSelection != 19);
		}
			else {}
		}
		event1.setTimes(myArray);
	}
}

void Executive::printEvents()
{
	std::cout << "Number of events currently planned: " << eventList->getLength() << "\nEvent list:\n";
	for (int i=1; i<=eventList->getLength(); i++)
	{
		eventList->getEntry(i).getInfo();
	}
}

bool Executive::dateCheck(int y, int m, int d)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int curY = (1900 + ltm->tm_year);
	if(y < curY)
	{
		std::cout <<"The year needs to be this year or later, you cannot create a past event!\n";
		return false;
		if(m <= ltm -> tm_mon)
		{
			std::cout <<"The month needs to be this month or later, you cannot create a past event!\n";
			return false;
			if(d <= ltm->tm_mday)
			{
				std::cout <<"The day needs to be this day or later, you cannot create a past event!\n";
				return false;
			}
		}

	}
	if (d < 1)
	{
		std::cout << "\nThe day must be 1 or higher.\n";
		return false;
	}
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		if (d > 31)
		{
			std::cout << "\nYou have selected a day outside the range of this month.\n";
			return false;
		}
	}
	else if (m == 4 || m == 6 || m == 9 || m == 11)
	{
		if (d > 30)
		{
			std::cout << "\nYou have selected a day outside the range of this month.\n";
			return false;
		}
	}
	else if (m == 2)
	{
		if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))			//Leep year conditions: cite "crazzyguy101 - cplusplus.com"
		{
			if (d > 29)
			{
				std::cout << "\nYou have selected a day outside the range of this month.\n";
				return false;
			}
		}
		else
		{
			if (d > 28)
			{
				std::cout << "\nYou have selected a day outside the range of this month.\n";
				return false;
			}
		}
	}
	return true;
}

bool Executive::validEventName(std::string name, int value) {
	if (name.length() == 0 || name.length()>(value - 1))
		return false;
	else
		return true;
}
//seperates a string by the delimiting character
std::vector<std::string> Executive::split(std::string mainString, char seperatingChar) {
	std::istringstream issMainString(mainString);
	std::string f;
	std::vector<std::string> returnString;
	while (std::getline(issMainString, f, seperatingChar)) {
		returnString.push_back(f);
	}
	return returnString;
}