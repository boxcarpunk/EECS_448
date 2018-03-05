#ifndef Highlight_h
#define Highlight_h
#include <ncurses.h>
#include <vector>
class Highlight
{
	public:
		Highlight();
		int print_menu(WINDOW * win, char * Menu[], int size, int StartLine);
		int print_scroll(WINDOW * win, char * Menu[], int size, int Actual, int StartLine);
		int print_vec(WINDOW * win, std::vector<char *> Menu, int Actual, int StartLine);
	private:
};
#endif

