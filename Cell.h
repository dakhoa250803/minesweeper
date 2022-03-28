#ifndef _CELL_H_
#define _CELL_H_

#include <windows.h>


enum CellType { CELL_TYPE_EMPTY, CELL_TYPE_NUM, CELL_TYPE_BOMB };
enum CellState { CELL_STATE_CLOSED, CELL_STATE_OPEN, CELL_STATE_FLAGGED };


class Cell {
	private:
		CellType _type;
		CellState _state;
		bool _isHighlight;
	public:
		Cell(CellType type);
		void draw(bool isHighlight = false);
		void setFlag(bool isHighlightl);
};

#endif
