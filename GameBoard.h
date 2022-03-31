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
		short _highlightedRow;
		short _highlightedCol;
		bool _boardDrawn;

		void _drawBoardBottom(COORD fromPoint);
		void _drawBoardBody(COORD fromPoint);
		void _drawBoardTop(COORD fromPoint);
		void _drawRow(char c, int width);
		void _initCells();
		void _drawCells(COORD fromPoint);
		void _drawBottomSpace();
		CellPtr _getCellAt(short row, short col);
		void _setCellTypes();
		void _randomizeBombCells();
		bool _bombExists(COORD bomb);
	public:
		GameBoard();
		void draw();
		void highlightCell(short row, short col);
		void toggleFlagCell(short col, short row);
		void tryOpenCell();
};

#endif
