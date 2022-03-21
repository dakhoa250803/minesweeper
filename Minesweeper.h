#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

#include "Controller.h"
#include "GameBoard.h"

class Minesweeper {
	public:
		Minesweeper();
		~Minesweeper();
		GameBoard* board;
		Controller* controller;
		void start();

};

void createNewGame();
void startGame();

#endif
