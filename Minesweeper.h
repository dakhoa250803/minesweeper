#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

#include "GameBoard.h"

class Minesweeper {
	private:
		GameBoard* _board;
	public:
		Minesweeper();
		~Minesweeper();
		void start();
};

#endif
