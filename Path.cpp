#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <mutex>
#include "Path.h"
#define ALT_BACKSPACE 127
#define WIDTH 60
#define HEIGHT 50
using namespace std;
Path::Path()
{
	TT1 = false;
	EmptyString = "";
	initscr();
	noecho();
	H = new Highlight();
	Des = new Designs();
	Des->Title();
	m_Counter = 0;
	m_StartRow = 15;
	m_StartCol = 10;
	m_MenuCounter = 1;
	ValAdUser = "Nick";
	ValAdPass = "Alvarez";
	ValUser = "Ryan";
	ValPass = "Alvarez";
	Twelve = true;
	Login(1,3);
}
Path::~Path()
{
	delete H;
	delete Des;
}
void Path::Login(int screen, int AdminOrUser)
{
	initscr();
	noecho();
	WINDOW * win0 = newwin(7,23,20,70);
	WINDOW * win1 = newwin(3,11,22,80);

	box(win0,0,0);
	wrefresh(win0);

	if(screen == 1)
	{
		if((AdminOrUser!=0)&&(AdminOrUser!=1))
		{
			mvwprintw(win0,1,1,"Enter name");
			mvwprintw(win0,3,1,"Username: ");
			wrefresh(win0);
			box(win1,0,0);
			wrefresh(win1);
			refresh();
			string Username = Input(win1);
		}
		wclear(win1);
		wrefresh(win1);
		int Choice = AOrU(win0, win1);
		if(Choice==2)
		{
			Login(1,3);
		}
		else if(Choice == 0)
		{
			Choice = AdminActions(win0,win1);
			if(Choice==0)
			{
				wclear(win0);
				mvwprintw(win0,1,1,"Enter event name");
				mvwprintw(win0,3,1,"Name:");
				box(win0,0,0);
				box(win1,0,0);
				wrefresh(win0);
				wrefresh(win1);
				refresh();
				string EventN = Input(win1);
				wclear(win0);
				wclear(win1);
				mvwprintw(win0,1,1,"Enter number of dates");
				mvwprintw(win0,3,1,"Number: ");
				box(win0,0,0);
				box(win1,0,0);
				wrefresh(win0);
				wrefresh(win1);
				refresh();
				int num = stoi(Input(win1));
				for(int i = 0; i<num;i++)
				{
					wclear(win0);
					wclear(win1);
					mvwprintw(win0,1,1,"Enter date");
					mvwprintw(win0,3,1,"Date: ");
					mvwprintw(win0,6,1,"(MM/DD/YYYY)");
					box(win0,0,0);
					box(win1,0,0);
					wrefresh(win0);
					wrefresh(win1);
					refresh();
					string Date = Input(win1);
					wclear(win1);
					wrefresh(win1);
				}
				wclear(win1);
				wrefresh(win1);
				Choice = AddATask(win0,win1);
				if(!Choice)
				{
					mvwprintw(win0,1,1,"Enter name");
					mvwprintw(win0,3,1,"Task name: ");
					wrefresh(win0);
					box(win1,0,0);
					wrefresh(win1);
					refresh();
					string TaskName = Input(win1);
					wclear(win1);
					wrefresh(win1);
				}
					Login(1,0);
			}
			else if(Choice==1)
			{
				Choice = SelectEvents(win0,win1);
				Choice = H->print_scroll(win0,Edit,3,6,2);
				if(Choice==0)
				{
					wclear(win0);
					mvwprintw(win0,1,1,"Enter event name");
					mvwprintw(win0,3,1,"Name:");
					box(win0,0,0);
					box(win1,0,0);
					wrefresh(win0);
					wrefresh(win1);
					refresh();
					string EventN = Input(win1);
				}
				else if(Choice==1)
				{
					wclear(win0);
					wclear(win1);
					mvwprintw(win0,1,1,"Enter date");
					mvwprintw(win0,3,1,"Date: ");
					mvwprintw(win0,6,1,"(MM/DD/YYYY)");
					box(win0,0,0);
					box(win1,0,0);
					wrefresh(win0);
					wrefresh(win1);
					refresh();
					string Date = Input(win1);
				}
				else if(Choice==2)
				{
					//needs to be fed appropriate date vector
					vector<char *> DateVec;
					DateVec.push_back("Date 1");
					DateVec.push_back("Date 2");
					DateVec.push_back("Date 3");
					Choice=H->print_vec(win0,DateVec,3,2);
					wclear(win0);
					wclear(win1);
					wrefresh(win0);
					wrefresh(win1);
					Login(1,0);
				}
			}
			else
			{
				//Login(3,1);
			}
		}
		else
		{
			Login(4,1);
		}
	}
	else if(screen == 3)
	{
		wclear(win0);
		wclear(win1);
		box(win0,0,0);
		wrefresh(win0);
		mvwprintw(win0,1,1,"User or Admin?");
		int Choice = H->print_scroll(win0,AorUMenu, 3,3, 2);
		wclear(win0);
		wrefresh(win0);
		//string B = to_string(Choice);
		//char const *pchar = B.c_str();
		//mvwprintw(win0,0,0,pchar);
		//wrefresh(win0);
		//getch();
		if(Choice==2)
		{
			Login(1,1);
		}
		else
		{
			Login(4,Choice);
		}
	}
	else if((screen == 4)&&(AdminOrUser==1))
	{
		wclear(win0);
		wclear(win1);
		box(win0,0,0);
		wrefresh(win0);
		mvwprintw(win0,1,1,"User Actions:");
		int Choice = H->print_scroll(win0,FirstUserMenu,2,2,2);
		wclear(win0);
		wrefresh(win0);
		//string B = to_string(Choice);
		//char const *pchar = B.c_str();
		//mvwprintw(win0,0,0,pchar);
		if(Choice==0)
		{
			Login(5,1);
		}
		else if(Choice==1)
		{
			Login(3,1);
		}
		else
		{
			string B = to_string(Choice);
			char const *pchar = B.c_str();
			mvwprintw(win0,0,0,pchar);
			wrefresh(win0);
			getch();
		}
	}
	else if((screen == 5)&&(AdminOrUser==1))
	{
		wclear(win0);
		wclear(win1);
		box(win0,0,0);
		wrefresh(win0);
		mvwprintw(win0,1,1,"Events:");
		vector<char *> Ev;
		vector<char *> Ev1D;
		vector<char *> Ev2D;
		vector<char *> Ev3D;
		Ev1D.push_back("Day1");
		Ev1D.push_back("Day2");
		Ev2D.push_back("Day1");
		Ev2D.push_back("Day2");
		Ev3D.push_back("Day1");
		Ev3D.push_back("Day2");
		Ev.push_back("Event1");
		Ev.push_back("Event2");
		Ev.push_back("Event3");
		int Choice = H->print_vec(win0,Ev,3,2);
		//Interface will only currectly print days of event 1
		//appropriate data structure will need to be applied so that the interface displays correct vector when event is picked
		Choice = H->print_vec(win0,Ev1D,3,2);
		Login(6,1);
	}
	else if((screen==6)&&(AdminOrUser==1))
	{
		bool Submit = false;
		int Choice2 = 0;
		if(Twelve)
		{
			while(!Submit)
			{
				Choice2 = H->print_scroll(win0,TwelveAval,3,19,2);
				//use the integer Choice2 to be an index on an array that stores what times the user signed up for
				switch(Choice2)
				{
					case 0:
					{
						Choice2 = H->print_scroll(win0,TwelveSp1,3,5,2);
						break;
					}
					case 1:
					{
						Choice2 = H->print_scroll(win0,TwelveSp2,3,5,2);
						break;
					}
					case 2:
					{
						Choice2 = H->print_scroll(win0,TwelveSp3,3,5,2);
						break;
					}
					case 3:
					{
						Choice2 = H->print_scroll(win0,TwelveSp4,3,5,2);
						break;
					}
					case 4:
					{
						Choice2 = H->print_scroll(win0,TwelveSp5,3,5,2);
						break;
					}
					case 5:
					{
						Choice2 = H->print_scroll(win0,TwelveSp6,3,5,2);
						break;
					}
					case 6:
					{
						Choice2 = H->print_scroll(win0,TwelveSp7,3,5,2);
						break;
					}
					case 7:
					{
						Choice2 = H->print_scroll(win0,TwelveSp8,3,5,2);
						break;
					}
					case 8:
					{
						Choice2 = H->print_scroll(win0,TwelveSp9,3,5,2);
						break;
					}
					case 9:
					{
						Choice2 = H->print_scroll(win0,TwelveSp10,3,5,2);
						break;
					}
					case 10:
					{
						Choice2 = H->print_scroll(win0,TwelveSp11,3,5,2);
						break;
					}
					case 11:
					{
						Choice2 = H->print_scroll(win0,TwelveSp12,3,5,2);
						break;
					}
					case 12:
					{
						Choice2 = H->print_scroll(win0,TwelveSp13,3,5,2);
						break;
					}
					case 13:
					{
						Choice2 = H->print_scroll(win0,TwelveSp14,3,5,2);
						break;
					}
					case 14:
					{
						Choice2 = H->print_scroll(win0,TwelveSp15,3,5,2);
						break;
					}
					case 15:
					{
						Choice2 = H->print_scroll(win0,TwelveSp16,3,5,2);
						break;
					}
					case 16:
					{
						Choice2 = H->print_scroll(win0,TwelveSp17,3,5,2);
						break;
					}
					case 17:
					{
						Choice2 = H->print_scroll(win0,TwelveSp18,3,5,2);
						break;
					}
					case 18:
					{
						Submit = true;
						break;
					}
				}
			}
			//string B = to_string(Choice2);
			//char const *pchar = B.c_str();
			//mvwprintw(win0,0,0,pchar);
			//wrefresh(win0);
			//getch();
			Login(7,1);
		}
	}
	else if((screen==7)&&(AdminOrUser==0))
	{
		wclear(win0);
		wclear(win1);
		box(win0,0,0);
		wrefresh(win0);
		mvwprintw(win0,1,1,"Select events:");
		vector<char *> Ev;
		vector<char *> Ev1D;
		vector<char *> Ev2D;
		vector<char *> Ev3D;
		Ev3D.push_back("Day1");
		Ev3D.push_back("Day2");
		Ev.push_back("Event1");
		Ev.push_back("Event2");
		Ev.push_back("Event3");
		int Choice = H->print_vec(win0,Ev,3,2);
		int Choice2 = H->print_scroll(win0,Edit,3,2,2);
		wclear(win1);
		if(Choice2 == 0)
		{
			mvwprintw(win0,1,1,"Enter even name");
			mvwprintw(win0,3,1,"Name:");
			box(win1,0,0);
			wrefresh(win1);
			refresh();
			string Name = Input(win1);
		}
		else if(Choice == 1)
		{
			mvwprintw(win0,1,1,"Enter event date");
			mvwprintw(win0,3,1,"Date:");
			wrefresh(win0);
			box(win1,0,0);
			wrefresh(win1);
			refresh();
			string Date = Input(win1);
		}
		else if(Choice ==2)
		{
			Login(8,0);
		}
	}
	else if((screen == 8)&&(AdminOrUser==0))
	{
		wclear(win0);
		wclear(win1);
		box(win0,0,0);
		wrefresh(win0);
		mvwprintw(win0,1,1,"Add Task?");
		int Choice = H->print_scroll(win0,AddTask,3,2,2);
		if(!Choice)
		{
			mvwprintw(win0,1,1,"Enter name");
			mvwprintw(win0,3,1,"Task name: ");
			wrefresh(win0);
			box(win1,0,0);
			wrefresh(win1);
			refresh();
			string TaskName = Input(win1);
			wclear(win1);
			wrefresh(win1);
		}	
	}
	else if((screen==7)&&(AdminOrUser==1))
	{
		int Choice2 = H->print_scroll(win0,SecondUserMenu,3,3,2);
		if(Choice2==0)
		{
			//Interface will only currectly print unrelated vector of tasks
			//appropriate data structure will need to be applied so that the interface displays correct vector when event is picked
			vector<char *> Taskvec;
			Taskvec.push_back("Task 1");
			Taskvec.push_back("Task 2");
			Choice2 = H->print_vec(win0,Taskvec,3,2);
			Login(7,1);
		}
		else if(Choice2==1)
		{
			//string B = to_string(Choice2);
			//char const *pchar = B.c_str();
			mvwprintw(win0,0,0,"Done!");
			wrefresh(win0);
			getch();
		}
		else
		{
			Login(6,1);
		}
	}
}
string Path::EventName(WINDOW * win0, WINDOW * win1)
{
	mvwprintw(win0,1,1,"Enter event name");
	mvwprintw(win0,3,1,"Name:");
	box(win1,0,0);
	wrefresh(win1);
	refresh();
	return(Input(win1));
}
int Path::AOrU(WINDOW * win0, WINDOW * win1)
{
	wclear(win0);
	wclear(win1);
	box(win0,0,0);
	wrefresh(win0);
	mvwprintw(win0,1,1,"User or Admin?");
	int Choice = H->print_scroll(win0,AorUMenu, 3,3, 2);
	wclear(win0);
	wrefresh(win0);
	return(Choice);
}
int Path::AddATask(WINDOW * win0,WINDOW * win1)
{
	wclear(win0);
	wclear(win1);
	box(win0,0,0);
	wrefresh(win0);
	mvwprintw(win0,1,1,"Add Task?");
	int Choice = H->print_scroll(win0,AddTask,3,2,2);
	return(Choice);
}
int Path::AdminActions(WINDOW * win0, WINDOW * win1)
{
	wclear(win0);
	wclear(win1);
	box(win0,0,0);
	wrefresh(win0);
	mvwprintw(win0,1,1,"Admin Actions:");
	int Choice = H->print_scroll(win0,FirstAdminMenu,3,3,2);
	wclear(win0);
	wrefresh(win0);
	return(Choice);
}
int Path::SelectEvents(WINDOW * win0, WINDOW * win1)
{
	wclear(win0);
	wclear(win1);
	box(win0,0,0);
	wrefresh(win0);
	mvwprintw(win0,1,1,"Select events:");
	vector<char *> Ev;
	vector<char *> Ev1D;
	vector<char *> Ev2D;
	vector<char *> Ev3D;
	Ev3D.push_back("Day1");
	Ev3D.push_back("Day2");
	Ev.push_back("Event1");
	Ev.push_back("Event2");
	Ev.push_back("Event3");
	int Choice = H->print_vec(win0,Ev,3,2);
	return(Choice);
	/*
	int Choice2 = H->print_scroll(win0,Edit,3,2,2);
	wclear(win1);
	if(Choice2 == 0)
	{
		mvwprintw(win0,1,1,"Enter even name");
		mvwprintw(win0,3,1,"Name:");
		box(win1,0,0);
		wrefresh(win1);
		refresh();
		string Name = Input(win1);
	}
	else if(Choice == 1)
	{
		mvwprintw(win0,1,1,"Enter event date");
		mvwprintw(win0,3,1,"Date:");
		wrefresh(win0);
		box(win1,0,0);
		wrefresh(win1);
		refresh();
		string Date = Input(win1);
	}
	else if(Choice ==2)
	{
		Login(8,0);
	}
	*/
}
string Path::Input(WINDOW * win1)
{
	keypad(stdscr,TRUE);
	int Keys = 0;
	string ValidChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+,<.>/?';:[{]}";
	string Info = "";
	bool Enter = false;
	string A = "A";
	string B = "B";
	while(!Enter)
	{
		Keys = getch();
		switch(Keys)
		{
			//Enter
			case 10:
			{
				Enter = true;
				break;
			}
			//backspace
			case 263:
			case 127:
			{
				if(Info.length()!=0)
				{
					wclear(win1);
					box(win1,0,0);
					Info.pop_back();
					const char * Ch = Info.c_str();
					mvwprintw(win1,1,1,Ch);
				}
				break;
			}
			default:
			{
				break;
			}
		}
		for(int i = 0; i<ValidChars.length();i++)
		{
			if(Keys==ValidChars[i])
			{
				wclear(win1);
				box(win1,0,0);
				Info += ValidChars[i];
				const char * Characters = Info.c_str();
				mvwprintw(win1,1,1,Characters);
				wrefresh(win1);
			}
		}
		wrefresh(win1);
	}
	return(Info);
}
