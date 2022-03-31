#ifndef UTILS_H
#define UTILS_H

#include<time.h>

enum Direction { DIR_NOMATCH=0, DIR_UP=1, DIR_DOWN=-1, DIR_LEFT=2, DIR_RIGHT=-2 };

void gotoxy(short x, short y);
void clearScreen();


template <typename T>
T randomNumInRange(T lowest, T highest) { 
	static bool first = true;
	if (first) 
	{  
	  srand((unsigned)time(0)); //seeding for the first time only!
	  first = false;
	}
    T range=(highest-lowest)+1; 
    T random_num = lowest + T(range*rand()/(RAND_MAX + 1.0)); 
    return random_num;
}

#endif

