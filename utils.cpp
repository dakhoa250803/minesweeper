#include <cstdlib>
#include <ctime>
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

void clearScreen() {
	system("cls");
}

