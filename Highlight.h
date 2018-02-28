#ifndef Highlight_h
#define Highlight_h
#include <ncurses.h>
class Highlight
{
	public:
		Highlight();
		print_menu(WINDOW * win, char * Menu[], int size, int StartLine);
		print_scroll(WINDOW * win, char * Menu[], int size, int Actual, int StartLine);
	private:
};
#endif

