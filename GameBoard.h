#ifndef __GAMEBOARD__
#define __GAMEBOARD__

#include <windows.h>
#include "Cell.h"

typedef Cell* CellPtr;
typedef CellPtr** CellMatrix;

class GameBoard{
	private:
		COORD _boardRootPoint;
		COORD _cellsRootPoint;
		short _width;
		short _height;
		short _highlightedRow;
		short _highlightedCol;
		CellMatrix _cells;
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
		void drawBoard();
		void highlightCell(short col, short row);
		void flagCell(short col, short row);
};

#endif
