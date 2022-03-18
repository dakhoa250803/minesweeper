#include <iostream>
#include <windows.h>

#include "console.h"
#include "Cell.h"

using namespace std;

const char CELL_CLOSED_CHAR = 176;

Cell::Cell(CellType type) {
	this->_state = CELL_STATE_CLOSED;
	this->_type = type;
}

void Cell::draw(bool isHighlight) {
	if (isHighlight) {
		setYellowText();
	}
	else {
		setWhiteText();
	}
	cout << CELL_CLOSED_CHAR;
}
