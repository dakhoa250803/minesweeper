#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include<iostream>
#include <windows.h>

#include "Cell.h"
#include "events.h"

using namespace std;

typedef Cell* CellPtr;
typedef CellPtr** CellMatrix;

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
		GameResetHandler _resetHandler;
		
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
		bool _bombExists(short row, short col);
		CellPtr _getCellAt(short screenX, short screenY);
		short _toCellCol(short screenX);
		short _countNeighborBombs(short row, short col);
		void _redraw(CellPtr cell);
		void _openCell(CellPtr cell);
		void _endGame();
		void _printAlert(string msg, COORD pos);
		void _clearAlert(string msg, COORD pos);
	public:
		GameBoard();
		~GameBoard();
		void draw();
		void highlightCell(COORD pos);
		void toggleFlagCell(COORD pos);
		void tryOpenCell(COORD pos);
		void onGameReset(GameResetHandler handler);
};

#endif
