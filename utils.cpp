#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <windows.h>
#include "utils.h"
/*
 * Utility functions
 */

void gotoxy(short x, short y) {
    COORD cursorPosition;
	cursorPosition.X = x;
	cursorPosition.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void printxy(short x, short y, std::string content) {
	gotoxy(x, y);
	std::cout << content;
	gotoxy(0, 0);
}

void clearScreen() {
	system("cls");
}

int randomIntegerInRange(int lowest, int highest) { 
	static bool first = true;
	if (first) 
	{  
	  srand((unsigned)time(0)); //seeding for the first time only!
	  first = false;
	}
    int range=(highest-lowest)+1; 
    int random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0)); 
    return random_integer;
}
