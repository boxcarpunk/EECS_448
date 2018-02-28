#include <string>
#include <fstream>
#include <ncurses.h>
#include "Dialog.h"
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
		char * FirstAdminMenu[3]={"Add Event","Edit Event","Back"};
		char * FirstUserMenu[2]={"Add Availability","Back"};
		char * AorUMenu[3] = {"Admin","User","Back"};
		char * TwelveOrTwentyFourMenu[2]={"12 hour","24 hour"};
		char * EventNames[9]={"1","2","3","4","5","6","7","8","9"};
		char * stuff[2]={"How!?","What!!"};
		bool TT1;
		WINDOW * InvWin;
		bool TalkedTo1;
		bool Exit;
		Highlight * H;
		Designs * Des;
		std::string ValAdUser;
		std::string ValAdPass;
		std::string ValUser;
		std::string ValPass;
};
#endif
