#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <windows.h>
#include "Cell.h"


typedef Cell* CellPtr;

class GameBoard {
	private:
		COORD _rootPoint;
		short _width;
		short _height;
		CellPtr** _cells;
		bool _boardDrawn;

		void _drawBoardBottom(COORD fromPoint);
		void _drawBoardBody(COORD fromPoint);
		void _drawBoardTop(COORD fromPoint);
		void _drawRow(char c, int width);
		void _initCells();
		void _drawCells(COORD fromPoint);
		void _drawBottomSpace();
	public:
		GameBoard();
		void draw();
};

#endif
