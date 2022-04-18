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
//		short _i;
//		short _j;
		void _drawNum();
	public:
		Cell(CellType type, short i, short j);
		void draw(bool isHighlight = false);
		bool isFlagged();
		void setFlag(bool value);
		void makeBomb();
		bool isBomb();
		void setNumber(short val);
		void open();
};

#endif
