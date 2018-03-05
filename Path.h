#include <string>
#include <fstream>
#include <ncurses.h>
#include "Highlight.h"
#include "Designs.h"
#include <string>
#ifndef PATH_H
#define PATH_H
class Path
{
	public:
		Path();
		~Path();
		void Login(int screen,int AdminOrUser);
		int AOrU(WINDOW * win0, WINDOW * win1);
		int AdminActions(WINDOW * win0, WINDOW * win1);
		int SelectEvents(WINDOW * win0,WINDOW * win1);
		std::string EventName(WINDOW * win0, WINDOW * win1);
		std::string Input(WINDOW * win1);

	private:
		const char * m_Field[100][100];
		std::string m_Name;
		WINDOW * Playwin;
		int m_FieldRow;
		int m_FieldCol;
		int m_StartRow;
		int m_StartCol;
		int m_Counter;
		int m_ForC;
		int m_SpawnEnemy;
		int m_MenuCounter;
		std::string EmptyString;
		char * FirstAdminMenu[3]={"Add Event","Edit Event","Quit"};
		char * FirstUserMenu[3]={"Add Availability","Back","Submit"};
		char * Events[3]={"Even1","Event2","Event3"};
		char * SecondUserMenu[3]={"Add Available Tasks","Submit","Back"};
		/*
		char * TwelveAval[19]={"5:00 AM","6:00 AM","7:00 AM","8:00 AM","9:00 AM","10:00 AM","11:00 AM","1:00 PM","2:00 PM","3:00 PM","4:00 PM","5:00 PM","6:00 PM","7:00 PM","8:00 PM","9:00 PM","10:00 PM","11:00 PM","Submit"};
		char * TwelveSp1[5]={"5:00 - 5:20 AM","5:20 - 5:40 AM","5:40 - 6:00 AM","Entire hour","Go Back"};
		char * TwelveSp2[5]={"6:00 - 6:20 AM","6:20 - 6:40 AM","6:40 - 6:00 AM","Entire hour","Go Back"};
		char * TwelveSp3[5]={"7:00 - 7:20 AM","5:20 - 5:40 AM","5:40 - 6:00 AM","Entire hour","Go Back"};
		char * TwelveSp4[5]={"8:00 - 8:20 AM","5:20 - 5:40 AM","5:40 - 6:00 AM","Entire hour","Go Back"};
		char * TwelveSp5[5]={"9:00 - 9:20 AM","5:20 - 5:40 AM","5:40 - 6:00 AM","Entire hour","Go Back"};
		char * TwelveSp6[5]={"10:00 - 10:20 AM","10:20 - 10:40 AM","10:40 - 10:00 AM","Entire hour","Go Back"};
		char * TwelveSp7[5]={"11:00 - 11:20 AM","11:20 - 11:40 AM","11:40 - 11:00 AM","Entire hour","Go Back"};
		char * TwelveSp8[5]={"1:00 - 1:20 PM","1:20 - 1:40 PM","1:40 - 1:00 PM","Entire hour","Go Back"};
		char * TwelveSp9[5]={"2:00 - 2:20 PM","2:20 - 2:40 PM","2:40 - 2:00 PM","Entire hour","Go Back"};
		char * TwelveSp10[5]={"3:00 - 3:20 PM","3:20 - 3:40 PM","3:40 - 3:00 PM","Entire hour","Go Back"};
		char * TwelveSp11[5]={"4:00 - 4:20 PM","4:20 - 4:40 PM","4:40 - 4:00 PM","Entire hour","Go Back"};
		char * TwelveSp12[5]={"5:00 - 5:20 PM","5:20 - 5:40 PM","5:40 - 5:00 PM","Entire hour","Go Back"};
		char * TwelveSp13[5]={"6:00 - 6:20 PM","6:20 - 6:40 PM","6:40 - 6:00 PM","Entire hour","Go Back"};
		char * TwelveSp14[5]={"7:00 - 7:20 PM","7:20 - 7:40 PM","7:40 - 7:00 PM","Entire hour","Go Back"};
		char * TwelveSp15[5]={"8:00 - 8:20 PM","8:20 - 8:40 PM","8:40 - 8:00 PM","Entire hour","Go Back"};
		char * TwelveSp16[5]={"9:00 - 9:20 PM","9:20 - 9:40 PM","9:40 - 9:00 PM","Entire hour","Go Back"};
		char * TwelveSp17[5]={"10:00 - 10:20 PM","10:20 - 10:40 PM","10:40 - 10:00 PM","Entire hour","Go Back"};
		char * TwelveSp18[5]={"11:00 - 11:20 PM","11:20 - 11:40 PM","11:40 - 11:00 PM","Entire hour","Go Back"};
		*/
		char * TwelveAval[19] = { "5:00 AM","6:00 AM","7:00 AM","8:00 AM","9:00 AM","10:00 AM","11:00 AM","1:00 PM","2:00 PM","3:00 PM","4:00 PM","5:00 PM","6:00 PM","7:00 PM","8:00 PM","9:00 PM","10:00 PM","11:00 PM","Submit" };
		char * TwelveSp1[5] = { "5:00 - 5:20 AM","5:20 - 5:40 AM","5:40 - 6:00 AM","Entire hour","Go Back" };
		char * TwelveSp2[5] = { "6:00 - 6:20 AM","6:20 - 6:40 AM","6:40 - 7:00 AM","Entire hour","Go Back" };
		char * TwelveSp3[5] = { "7:00 - 7:20 AM","7:20 - 7:40 AM","7:40 - 8:00 AM","Entire hour","Go Back" };
		char * TwelveSp4[5] = { "8:00 - 8:20 AM","8:20 - 8:40 AM","8:40 - 9:00 AM","Entire hour","Go Back" };
		char * TwelveSp5[5] = { "9:00 - 9:20 AM","9:20 - 9:40 AM","9:40 - 10:00 AM","Entire hour","Go Back" };
		char * TwelveSp6[5] = { "10:00 - 10:20 AM","10:20 - 10:40 AM","10:40 - 11:00 AM","Entire hour","Go Back" };
		char * TwelveSp7[5] = { "11:00 - 11:20 AM","11:20 - 11:40 AM","11:40 - 12:00 AM","Entire hour","Go Back" };
		char * TwelveSp8[5] = { "1:00 - 1:20 PM","1:20 - 1:40 PM","1:40 - 2:00 PM","Entire hour","Go Back" };
		char * TwelveSp9[5] = { "2:00 - 2:20 PM","2:20 - 2:40 PM","2:40 - 3:00 PM","Entire hour","Go Back" };
		char * TwelveSp10[5] = { "3:00 - 3:20 PM","3:20 - 3:40 PM","3:40 - 4:00 PM","Entire hour","Go Back" };
		char * TwelveSp11[5] = { "4:00 - 4:20 PM","4:20 - 4:40 PM","4:40 - 5:00 PM","Entire hour","Go Back" };
		char * TwelveSp12[5] = { "5:00 - 5:20 PM","5:20 - 5:40 PM","5:40 - 6:00 PM","Entire hour","Go Back" };
		char * TwelveSp13[5] = { "6:00 - 6:20 PM","6:20 - 6:40 PM","6:40 - 7:00 PM","Entire hour","Go Back" };
		char * TwelveSp14[5] = { "7:00 - 7:20 PM","7:20 - 7:40 PM","7:40 - 8:00 PM","Entire hour","Go Back" };
		char * TwelveSp15[5] = { "8:00 - 8:20 PM","8:20 - 8:40 PM","8:40 - 9:00 PM","Entire hour","Go Back" };
		char * TwelveSp16[5] = { "9:00 - 9:20 PM","9:20 - 9:40 PM","9:40 - 10:00 PM","Entire hour","Go Back" };
		char * TwelveSp17[5] = { "10:00 - 10:20 PM","10:20 - 10:40 PM","10:40 - 11:00 PM","Entire hour","Go Back" };
		char * TwelveSp18[5] = { "11:00 - 11:20 PM","11:20 - 11:40 PM","11:40 PM - 12:00 AM","Entire hour","Go Back" };
		char * TwentyFourAval[19] = { "5:00","6:00","7:00","8:00","9:00","10:00","11:00","13:00","14:00","15:00","16:00","17:00","18:00","19:00","20:00","21:00","22:00","23:00","Submit" };
		char * TwentyFourSp1[5] = { "5:00 - 5:20","5:20 - 5:40","5:40 - 6:00","Entire hour","Go Back" };
		char * TwentyFourSp2[5] = { "6:00 - 6:20","6:20 - 6:40","6:40 - 7:00","Entire hour","Go Back" };
		char * TwentyFourSp3[5] = { "7:00 - 7:20","7:20 - 7:40","7:40 - 8:00","Entire hour","Go Back" };
		char * TwentyFourSp4[5] = { "8:00 - 8:20","8:20 - 8:40","8:40 - 9:00","Entire hour","Go Back" };
		char * TwentyFourSp5[5] = { "9:00 - 9:20","9:20 - 9:40","9:40 - 10:00","Entire hour","Go Back" };
		char * TwentyFourSp6[5] = { "10:00 - 10:20","10:20 - 10:40","10:40 - 11:00","Entire hour","Go Back" };
		char * TwentyFourSp7[5] = { "11:00 - 11:20","11:20 - 11:40","11:40 - 12:00","Entire hour","Go Back" };
		char * TwentyFourSp8[5] = { "13:00 - 13:20","13:20 - 13:40","13:40 - 14:00","Entire hour","Go Back" };
		char * TwentyFourSp9[5] = { "14:00 - 14:20","14:20 - 14:40","14:40 - 15:00","Entire hour","Go Back" };
		char * TwentyFourSp10[5] = { "15:00 - 15:20","15:20 - 15:40","15:40 - 16:00","Entire hour","Go Back" };
		char * TwentyFourSp11[5] = { "16:00 - 16:20","16:20 - 16:40","16:40 - 17:00","Entire hour","Go Back" };
		char * TwentyFourSp12[5] = { "17:00 - 17:20","17:20 - 17:40","17:40 - 18:00","Entire hour","Go Back" };
		char * TwentyFourSp13[5] = { "18:00 - 18:20","18:20 - 18:40","18:40 - 19:00","Entire hour","Go Back" };
		char * TwentyFourSp14[5] = { "19:00 - 19:20","19:20 - 19:40","19:40 - 20:00","Entire hour","Go Back" };
		char * TwentyFourSp15[5] = { "20:00 - 20:20","20:20 - 20:40","20:40 - 21:00","Entire hour","Go Back" };
		char * TwentyFourSp16[5] = { "21:00 - 21:20","21:20 - 21:40","21:40 - 22:00","Entire hour","Go Back" };
		char * TwentyFourSp17[5] = { "22:00 - 22:20","22:20 - 22:40","22:40 - 23:00","Entire hour","Go Back" };
		char * TwentyFourSp18[5] = { "23:00 - 23:20","23:20 - 23:40","23:40 - 00:00","Entire hour","Go Back" };
		char * AorUMenu[3] = {"Admin","User","Back"};
		char * TwelveOrTwentyFourMenu[2]={"12 hour","24 hour"};
		char * EventNames[9]={"1","2","3","4","5","6","7","8","9"};
		char * AddTask[2]={"Yes","No"};
		char * Edit[4]={"Edit event name","Edit event date","Add task","Submit"};
		bool TT1;
		bool Type;
		WINDOW * InvWin;
		bool TalkedTo1;
		bool Twelve;
		Highlight * H;
		Designs * Des;
		std::string ValAdUser;
		std::string ValAdPass;
		std::string ValUser;
		std::string ValPass;
};
#endif
