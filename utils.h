#ifndef UTILS_H
#define UTILS_H

enum Direction { DIR_NOMATCH=0, DIR_UP=1, DIR_DOWN=-1, DIR_LEFT=2, DIR_RIGHT=-2 };

void gotoxy(short x, short y);
void clearScreen();
int randomIntegerInRange(int lowest, int highest);

#endif
