#ifndef UTILS_H
#define UTILS_H

#include<string>


enum Direction { DIR_NOMATCH=0, DIR_UP=1, DIR_DOWN=-1, DIR_LEFT=2, DIR_RIGHT=-2 };

void gotoxy(short x, short y);
void printxy(short x, short y, std::string content);
void clearScreen();

/**
 * Generates a random integer whose value is from lowest (inclusive) to highest (exclusive).
 */
int randomIntegerInRange(int lowest, int highest);

#endif
