#include <iostream>
#include <windows.h>

#include "console.h"
#include "Cell.h"

using namespace std;

const char CHAR_CELL_CLOSED = 254;
const char CHAR_CELL_FLAGGED = 5;
const char CHAR_CELL_BOMB = 15;

Cell::Cell(CellType type, short i, short j) {
	this->_state = CELL_STATE_CLOSED;
//	this->_state = CELL_STATE_OPEN;
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
			switch (this->_type) {
				case CELL_TYPE_BOMB:
					setLightRedText();
					cout << CHAR_CELL_BOMB;
					break;
				case CELL_TYPE_NUM:
					setLightBlueText();
					cout << this->_num;
					break;
				default:
					cout << " ";
			}
			break;
		case CELL_STATE_FLAGGED:
			setGreenText();
			cout << CHAR_CELL_FLAGGED;
			break;
		default:
			cout << CHAR_CELL_CLOSED;
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

void Cell::makeBomb() {
	this->_type = CELL_TYPE_BOMB;
}

void Cell::open() {
	this->_state = CELL_STATE_OPEN;
}
