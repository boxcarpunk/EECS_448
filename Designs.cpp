#include "Designs.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#define WIDTH 60
#define HEIGHT 50

using namespace std;
using namespace chrono;
using namespace this_thread;
Designs::Designs()
{
}
void Designs::Title()
{
	ifstream InFile("Title.txt");
	string Cover((istreambuf_iterator<char>(InFile)), istreambuf_iterator<char>());
	const char * TitleValue = Cover.c_str();
	initscr();
	WINDOW * Top = newwin(10, 135, 0, 20);
	refresh();
	mvwprintw(Top, 1, 1, TitleValue);
	box(Top, 0, 0);
	wrefresh(Top);
}
