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
	Login(1,0);
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
		mvwprintw(win0,1,1,"Enter name");
		mvwprintw(win0,3,1,"Username: ");
		wrefresh(win0);
		box(win1,0,0);
		wrefresh(win1);
		refresh();
	}
	else if((screen == 5)&&(AdminOrUser==0))
	{
		mvwprintw(win0,1,1,"Enter even name");
		mvwprintw(win0,3,1,"Name:");
		wrefresh(win0);
		box(win1,0,0);
		wrefresh(win1);
		refresh();
	}
	else if((screen == 6)&&(AdminOrUser==0))
	{
		mvwprintw(win0,1,1,"Enter even date"); 
		mvwprintw(win0,3,1,"Date:"); 
		mvwprintw(win0,6,1,"(MM/DD/YYYY)");
		wrefresh(win0);
		box(win1,0,0);
		wrefresh(win1);
		refresh();
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
			Login(2,1);
		}
		else
		{
			Login(4,Choice);
		}
	}
	else if((screen == 4)&&(AdminOrUser==0))
	{
		wclear(win0);
		wclear(win1);
		box(win0,0,0);
		wrefresh(win0);
		mvwprintw(win0,1,1,"Admin Actions:");
		int Choice = H->print_scroll(win0,FirstAdminMenu,3,3,2);
		wclear(win0);
		wrefresh(win0);
		//string B = to_string(Choice);
		//char const *pchar = B.c_str();
		//mvwprintw(win0,0,0,pchar);
		if(Choice==2)
		{
			Login(3,1);
		}
		else
		{
			Login(5,1);
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
		else
		{
			Login(3,1);
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
		Ev.push_back("Event1");
		Ev.push_back("Event2");
		Ev.push_back("Event3");
		int Choice = H->print_vec(win0,Ev,3,2);
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
			string B = to_string(Choice2);
			char const *pchar = B.c_str();
			mvwprintw(win0,0,0,pchar);
			wrefresh(win0);
			getch();
		}
	}
	else if((screen==7)&&(AdminOrUser==1))
	{
		int Choice2 = H->print_scroll(win0,SecondUserMenu,3,2,2);
		if(Choice2==1)
		{
			Login(6,1);
		}
	}
	keypad(stdscr,TRUE);
	int Keys = 0;
	string ValidChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+,<.>/?';:[{]}";
	string Info = "";
	bool success = true;
	string A = "A";
	string B = "B";
	while(1)
	{
		Keys = getch();
		switch(Keys)
		{
			//Enter
			case 10:
			{
				wclear(win1);
				if(screen==1)
				{
					Login(3,1);
				}
				else if((screen == 5)&&(AdminOrUser==0))
				{
					Login(6,0);
				}
				else if((screen == 6)&&(AdminOrUser==0))
				{
					Login(6,0);
				}
				wrefresh(win1);
				break;
			}
			//backspace
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
				//string i = to_string(Keys);
				//const char  * number = i.c_str();
				//mvwprintw(win1, 0, 0, number);
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
}
