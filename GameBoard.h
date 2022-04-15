#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <windows.h>
#include "Cell.h"


typedef Cell* CellPtr;
typedef CellPtr** CellMatrix;

class GameBoard {
	private:
		COORD _boardRootPoint;
		COORD _cellsRootPoint;
		short _width;
		short _height;
		CellMatrix _cells;
		COORD* _bombCells;
		size_t _bombCellsLength;
		short _highlightedX;
		short _highlightedY;
		bool _boardDrawn;

		void _drawBoardBottom(COORD fromPoint);
		void _drawBoardBody(COORD fromPoint);
		void _drawBoardTop(COORD fromPoint);
		void _drawRow(char c, int width);
		void _initCells();
		void _destroyCells();
		void _drawCells(COORD fromPoint);
		void _drawBottomSpace();
		void _setCellTypes();
		void _randomizeBombCells();
		bool _bombExists(COORD bomb);
		CellPtr _getCellAt(short screenX, short screenY);
		short _toCellCol(short screenX);
	public:
		GameBoard();
		~GameBoard();
		void draw();
		void highlightCell(COORD pos);
		void toggleFlagCell(COORD pos);
		void tryOpenCell(COORD pos);
};

#endif
