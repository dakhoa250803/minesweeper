#include <iostream>
#include <windows.h>

#include "console.h"
#include "Cell.h"

using namespace std;

const char CELL_CLOSED = 254;
const char CELL_FLAGGED = 5;

Cell::Cell(CellType type, short i, short j) {
	this->_state = CELL_STATE_CLOSED;
	this->_type = type;
//	this->_i = i;
//	this->_j = j;
}

void Cell::draw(bool isHighlight) {
//	printf("Cell(%d, %d)=%d; ", this->_i, this->_j, this->_state);
	//cout << "draw: " << this->_state;
	if (isHighlight) {
		setLightYellowText();
	}
	else {
		setWhiteText();
	}

	switch (this->_state) {
		case CELL_STATE_OPEN:
			break;
		case CELL_STATE_FLAGGED:
			setGreenText();
			cout << CELL_FLAGGED;
			break;
		default:
			cout << CELL_CLOSED;
	}
}

bool Cell::isFlagged() {
	return (this->_state == CELL_STATE_FLAGGED);
}

void Cell::setFlag(bool value) {
	if (value) {
		this->_state = CELL_STATE_FLAGGED;
	}
	else {
		this->_state = CELL_STATE_CLOSED;
	}
}
