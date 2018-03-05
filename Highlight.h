#ifndef Highlight_h
#define Highlight_h
#include <ncurses.h>
#include <vector>
class Highlight
{
public:
	/**
	* Constructor does nothing
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
	Highlight();
	/**
	* Prints an array
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
	int print_scroll(WINDOW * win, char * Menu[], int size, int Actual, int StartLine);
	/**
	* Prints a vector, just like print_scroll but vector
	*	@pre None
	*	@post None
	*	@param None
	*	@return None
	*/
	int print_vec(WINDOW * win, std::vector<char *> Menu, int Actual, int StartLine);
private:
};
#endif
