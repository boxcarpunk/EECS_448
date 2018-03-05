#include <string>
#include <fstream>
#include <ncurses.h>
#include "Highlight.h"
#include "Designs.h"
#include "Executive.h"
#include <string>
#ifndef PATH_H
#define PATH_H
class Path
{
	public:

		/**
		*	Creates the Executive, Highlights and Designs objects intializes values
		*	@pre None
		*	@post Objects are created
		*	@param None
		*	@return None
		*/
		Path();

		/**
		*	Deletes the Executive, Highlights and Designs objects  
		*	@pre None
		*	@post Objects are deleted
		*	@param None
		*	@return None
		*/
		~Path();

		/**
		*	Controls which screens the program user goes to
		*	@pre In the constructor screen is intially 1 and AdminOrUser is 0
		*	@post Changes to the next screen
		*	@param Int representing what screen we go to next, and an int with value 0 if user is an Admin, and 1 if not
		*	@return None
		*/
		void Login(int screen,int AdminOrUser);

		/**
		*	Checks the value of the input by the program user
		*	@pre In the constructor screen is intially 1 and AdminOrUser is 0
		*	@post The string is created with proper characters
		*	@param pointer to type WINDOW 
		*	@return String of the input
		*/
		std::string Input(WINDOW * win1);

	private:
		Executive exec; /**< The executive object that runs the backend code */

		std::string eventName; /**< Holds the name of an event */
		std::string date; /**< Holds the date of an event */

		const char * m_Field[100][100]; /**< Variable Description */
		std::string m_Name; /**< Variable Description */
		WINDOW * Playwin; /**< Variable Description */
		int m_FieldRow; /**< Variable Description */
		int m_FieldCol; /**< Variable Description */
		int m_StartRow; /**< Variable Description */
		int m_StartCol; /**< Variable Description */
		int m_Counter; /**< Variable Description */
		int m_ForC; /**< Variable Description */
		int m_SpawnEnemy; /**< Variable Description */
		int m_MenuCounter; /**< Variable Description */
		std::string EmptyString; /**< Variable Description */
		char * FirstAdminMenu[3]={"Add Event","Edit Event","Back"}; /**< Variable Description */
		char * FirstUserMenu[3]={"Add Availability","Back","Submit"}; /**< Variable Description */
		char * Events[3]={"Even1","Event2","Event3"}; /**< Variable Description */
		char * SecondUserMenu[3]={"Add Available Tasks","Submit","Back"}; /**< Variable Description */

		char * TwelveAval[19] = { "5:00 AM","6:00 AM","7:00 AM","8:00 AM","9:00 AM","10:00 AM","11:00 AM","1:00 PM","2:00 PM","3:00 PM","4:00 PM","5:00 PM","6:00 PM","7:00 PM","8:00 PM","9:00 PM","10:00 PM","11:00 PM","Submit" }; /**< The list of hours able to be available for in 12hr format */
		char * TwelveSp1[5] = { "5:00 - 5:20 AM","5:20 - 5:40 AM","5:40 - 6:00 AM","Entire hour","Go Back" }; /**< The 20min time slots for 5 am in 12hr format */
		char * TwelveSp2[5] = { "6:00 - 6:20 AM","6:20 - 6:40 AM","6:40 - 7:00 AM","Entire hour","Go Back" }; /**< The 20min time slots for 6 am in 12hr format */
		char * TwelveSp3[5] = { "7:00 - 7:20 AM","7:20 - 7:40 AM","7:40 - 8:00 AM","Entire hour","Go Back" }; /**< The 20min time slots for 7 am in 12hr format */
		char * TwelveSp4[5] = { "8:00 - 8:20 AM","8:20 - 8:40 AM","8:40 - 9:00 AM","Entire hour","Go Back" }; /**< The 20min time slots for 8 am in 12hr format */
		char * TwelveSp5[5] = { "9:00 - 9:20 AM","9:20 - 9:40 AM","9:40 - 10:00 AM","Entire hour","Go Back" }; /**< The 20min time slots for 9 am in 12hr format */
		char * TwelveSp6[5] = { "10:00 - 10:20 AM","10:20 - 10:40 AM","10:40 - 11:00 AM","Entire hour","Go Back" }; /**< The 20min time slots for 10 am in 12hr format */
		char * TwelveSp7[5] = { "11:00 - 11:20 AM","11:20 - 11:40 AM","11:40 - 12:00 AM","Entire hour","Go Back" }; /**< The 20min time slots for 11 am in 12hr format */
		char * TwelveSp8[5] = { "1:00 - 1:20 PM","1:20 - 1:40 PM","1:40 - 2:00 PM","Entire hour","Go Back" }; /**< The 20min time slots for 1 pm in 12hr format */
		char * TwelveSp9[5] = { "2:00 - 2:20 PM","2:20 - 2:40 PM","2:40 - 3:00 PM","Entire hour","Go Back" }; /**< The 20min time slots for 2 pm in 12hr format */
		char * TwelveSp10[5] = { "3:00 - 3:20 PM","3:20 - 3:40 PM","3:40 - 4:00 PM","Entire hour","Go Back" }; /**< The 20min time slots for 3 pm in 12hr format */
		char * TwelveSp11[5] = { "4:00 - 4:20 PM","4:20 - 4:40 PM","4:40 - 5:00 PM","Entire hour","Go Back" }; /**< The 20min time slots for 4 pm in 12hr format */
		char * TwelveSp12[5] = { "5:00 - 5:20 PM","5:20 - 5:40 PM","5:40 - 6:00 PM","Entire hour","Go Back" }; /**< The 20min time slots for 5 pm in 12hr format */
		char * TwelveSp13[5] = { "6:00 - 6:20 PM","6:20 - 6:40 PM","6:40 - 7:00 PM","Entire hour","Go Back" }; /**< The 20min time slots for 6 pm in 12hr format */
		char * TwelveSp14[5] = { "7:00 - 7:20 PM","7:20 - 7:40 PM","7:40 - 8:00 PM","Entire hour","Go Back" }; /**< The 20min time slots for 7 pm in 12hr format */
		char * TwelveSp15[5] = { "8:00 - 8:20 PM","8:20 - 8:40 PM","8:40 - 9:00 PM","Entire hour","Go Back" }; /**< The 20min time slots for 8 pm in 12hr format */
		char * TwelveSp16[5] = { "9:00 - 9:20 PM","9:20 - 9:40 PM","9:40 - 10:00 PM","Entire hour","Go Back" }; /**< The 20min time slots for 9 pm in 12hr format */
		char * TwelveSp17[5] = { "10:00 - 10:20 PM","10:20 - 10:40 PM","10:40 - 11:00 PM","Entire hour","Go Back" }; /**< The 20min time slots for 10 pm in 12hr format */
		char * TwelveSp18[5] = { "11:00 - 11:20 PM","11:20 - 11:40 PM","11:40 PM - 12:00 AM","Entire hour","Go Back" }; /**< The 20min time slots for 11 pm in 12hr format */

		char * TwentyFourAval[19] = { "5:00","6:00","7:00","8:00","9:00","10:00","11:00","13:00","14:00","15:00","16:00","17:00","18:00","19:00","20:00","21:00","22:00","23:00","Submit" }; /**< The list of hours able to be available for in 24hr format */
		char * TwentyFourSp1[5] = { "5:00 - 5:20","5:20 - 5:40","5:40 - 6:00","Entire hour","Go Back" }; /**< The 20min time slots for 5 o'clock in 24hr format */
		char * TwentyFourSp2[5] = { "6:00 - 6:20","6:20 - 6:40","6:40 - 7:00","Entire hour","Go Back" }; /**< The 20min time slots for 6 o'clock in 24hr format */
		char * TwentyFourSp3[5] = { "7:00 - 7:20","7:20 - 7:40","7:40 - 8:00","Entire hour","Go Back" }; /**< The 20min time slots for 7 o'clock in 24hr format */
		char * TwentyFourSp4[5] = { "8:00 - 8:20","8:20 - 8:40","8:40 - 9:00","Entire hour","Go Back" }; /**< The 20min time slots for 8 o'clock in 24hr format */
		char * TwentyFourSp5[5] = { "9:00 - 9:20","9:20 - 9:40","9:40 - 10:00","Entire hour","Go Back" }; /**< The 20min time slots for 9 o'clock in 24hr format */
		char * TwentyFourSp6[5] = { "10:00 - 10:20","10:20 - 10:40","10:40 - 11:00","Entire hour","Go Back" }; /**< The 20min time slots for 10 o'clock in 24hr format */
		char * TwentyFourSp7[5] = { "11:00 - 11:20","11:20 - 11:40","11:40 - 12:00","Entire hour","Go Back" }; /**< The 20min time slots for 11 o'clock in 24hr format */
		char * TwentyFourSp8[5] = { "13:00 - 13:20","13:20 - 13:40","13:40 - 14:00","Entire hour","Go Back" }; /**< The 20min time slots for 13 o'clock in 24hr format */
		char * TwentyFourSp9[5] = { "14:00 - 14:20","14:20 - 14:40","14:40 - 15:00","Entire hour","Go Back" }; /**< The 20min time slots for 14 o'clock in 24hr format */
		char * TwentyFourSp10[5] = { "15:00 - 15:20","15:20 - 15:40","15:40 - 16:00","Entire hour","Go Back" }; /**< The 20min time slots for 15 o'clock in 24hr format */
		char * TwentyFourSp11[5] = { "16:00 - 16:20","16:20 - 16:40","16:40 - 17:00","Entire hour","Go Back" }; /**< The 20min time slots for 16 o'clock in 24hr format */
		char * TwentyFourSp12[5] = { "17:00 - 17:20","17:20 - 17:40","17:40 - 18:00","Entire hour","Go Back" }; /**< The 20min time slots for 17 o'clock in 24hr format */
		char * TwentyFourSp13[5] = { "18:00 - 18:20","18:20 - 18:40","18:40 - 19:00","Entire hour","Go Back" }; /**< The 20min time slots for 18 o'clock in 24hr format */
		char * TwentyFourSp14[5] = { "19:00 - 19:20","19:20 - 19:40","19:40 - 20:00","Entire hour","Go Back" }; /**< The 20min time slots for 19 o'clock in 24hr format */
		char * TwentyFourSp15[5] = { "20:00 - 20:20","20:20 - 20:40","20:40 - 21:00","Entire hour","Go Back" }; /**< The 20min time slots for 20 o'clock in 24hr format */
		char * TwentyFourSp16[5] = { "21:00 - 21:20","21:20 - 21:40","21:40 - 22:00","Entire hour","Go Back" }; /**< The 20min time slots for 21 o'clock in 24hr format */
		char * TwentyFourSp17[5] = { "22:00 - 22:20","22:20 - 22:40","22:40 - 23:00","Entire hour","Go Back" }; /**< The 20min time slots for 22 o'clock in 24hr format */
		char * TwentyFourSp18[5] = { "23:00 - 23:20","23:20 - 23:40","23:40 - 00:00","Entire hour","Go Back" }; /**< The 20min time slots for 23 o'clock in 24hr format */

		char * AorUMenu[3] = {"Admin","User","Back"}; /**< Variable Description */
		char * TwelveOrTwentyFourMenu[2]={"12 hour","24 hour"}; /**< Variable Description */
		char * EventNames[9]={"1","2","3","4","5","6","7","8","9"}; /**< Variable Description */
		char * AddTask[2]={"Yes","No"}; /**< Variable Description */
		char * Edit[4]={"Edit event name","Edit event date","Add task","Submit"}; /**< Variable Description */
		bool TT1; /**< Variable Description */
		bool Type; /**< Variable Description */
		WINDOW * InvWin; /**< Variable Description */
		bool TalkedTo1; /**< Variable Description */
		bool Twelve; /**< Variable Description */
		Highlight * H; /**< Variable Description */
		Designs * Des; /**< Variable Description */
		std::string ValAdUser; /**< Variable Description */
		std::string ValAdPass; /**< Variable Description */
		std::string ValUser; /**< Variable Description */
		std::string ValPass; /**< Variable Description */
}; 
#endif
