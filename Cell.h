#ifndef _CELL_H_
#define _CELL_H_

#include <windows.h>


enum CellType { CELL_TYPE_EMPTY, CELL_TYPE_NUM, CELL_TYPE_BOMB };
enum CellState { CELL_STATE_CLOSED, CELL_STATE_OPEN, CELL_STATE_FLAGGED };

struct CELL_COORD {
	short row;
	short col;
};

class Cell {
	private:
		CellType _type;
		CellState _state;
		bool _isHighlight;
		short _num;
		CELL_COORD _cellCoord;
		COORD _screenCoord;
		void _drawNum();
	public:
		Cell(CellType type, short row, short col);
		void draw(bool isHighlight = false);
		bool isFlagged();
		void setFlag(bool value);
		void makeBomb();
		bool isBomb();
		void setNumber(short val);
		void open();
		bool isOpen();
		bool isEmpty();
		void setScreenCoord(COORD val);
		COORD getScreenCoord();
		void setCellCoord(CELL_COORD val);
		CELL_COORD getCellCoord();
};

#endif
