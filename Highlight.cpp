#include "Highlight.h"
#include <string>
using namespace std;

Highlight::Highlight()
{
}

int Highlight::print_scroll(WINDOW * win, char * Menu[], int size, int Actual, int StartLine)
{
	int index = 0;
	int highlightNum = StartLine;
	keypad(win, true);
	if (size>Actual)
	{
		size = Actual;
	}
	while (1)
	{
		wclear(win);
		box(win, 0, 0);
		wrefresh(win);

		for (int i = size + StartLine; i > StartLine; i--)
		{
			if (highlightNum == i - 1)
			{
				wattron(win, A_REVERSE);
				mvwprintw(win, i, 1, Menu[i - StartLine + index - 1]);
				wattroff(win, A_REVERSE);
			}
			else
			{
				mvwprintw(win, i, 1, Menu[i - StartLine + index - 1]);
			}
		}
		int Arrows = wgetch(win);
		switch (Arrows)
		{
		case KEY_UP:
			highlightNum--;
			if (highlightNum == StartLine - 1)
			{
				index--;
				if (index == -1)
				{
					index = 0;
				}
				highlightNum = StartLine;
			}
			break;
		case KEY_DOWN:
			highlightNum++;
			if (highlightNum == size + StartLine)
			{
				index++;
				if (index == Actual - size + 1)
				{
					index--;
				}
				highlightNum = size + StartLine - 1;
			}

			break;
		default:
			break;
		}
		if (Arrows == 10)
			break;
	}
	return(highlightNum - StartLine + index);
}

int Highlight::print_vec(WINDOW * win, vector<char *> Menu, int size, int StartLine)
{
	int index = 0;
	int highlightNum = StartLine;
	int Actual = Menu.size();
	if (size>Actual)
	{
		size = Actual;
	}
	keypad(win, true);
	while (1)
	{
		wclear(win);
		box(win, 0, 0);
		wrefresh(win);
		for (int i = size + StartLine; i > StartLine; i--)
		{
			if ((i - StartLine + index)>Actual)
			{
				break;
			}
			if (highlightNum == i - 1)
			{
				wattron(win, A_REVERSE);
				mvwprintw(win, i, 1, Menu[i - StartLine + index - 1]);
				wattroff(win, A_REVERSE);
			}
			else
			{
				mvwprintw(win, i, 1, Menu[i - StartLine + index - 1]);
			}
		}
		int Arrows = wgetch(win);
		switch (Arrows)
		{
		case KEY_UP:
			highlightNum--;
			if (highlightNum == StartLine - 1)
			{
				index--;
				if (index == -1)
				{
					index = 0;
				}
				highlightNum = StartLine;
			}
			break;
		case KEY_DOWN:
			highlightNum++;
			if (highlightNum == size + StartLine)
			{
				index++;
				if (index == Actual - size + 1)
				{
					index--;
				}
				highlightNum = size + StartLine - 1;
			}

			break;
		default:
			break;
		}
		if (Arrows == 10)
			break;
	}
	return(highlightNum - StartLine + index);
}
