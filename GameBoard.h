#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <windows.h>
#include "Cell.h"


typedef Cell* CellPtr;
typedef CellPtr** CellMatrix;

struct CELL_COORD{
	short row;
	short col;
};

class GameBoard {
	private:
		COORD _boardRootPoint;
		COORD _cellsRootPoint;
		short _width;
		short _height;
		CellMatrix _cells;
		CELL_COORD* _bombCells;
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
		CellPtr _getCellAt(short row, short col);
		void _setCellTypes();
		void _randomizeBombCells();
		bool _bombExists(COORD bomb);
		short _toCellCol(short screenCol);
		bool _isInBoard(short col, short row);
		bool _isBombExists(short row, short col);
		short _countNeighborBombs(short row,short col);
		void _reDraw(CellPtr cell);
	public:
		GameBoard();
		~GameBoard();
		void drawBoard();
		void highlightCell(COORD pos);
		void toggleFlagCell(COORD pos);
		void openCell(COORD pos);
};

#endif
