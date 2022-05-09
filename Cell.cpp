#include <iostream>
#include <windows.h>

#include "console.h"
#include "Cell.h"

using namespace std;

const char CHAR_CELL_CLOSED = 254;
const char CHAR_CELL_FLAGGED = 5;
const char CHAR_CELL_BOMB = 15;

Cell::Cell(CellType type, short row, short col) {
	this->_state = CELL_STATE_CLOSED;
//	this->_state = CELL_STATE_OPEN;
	this->_type = type;

	CELL_COORD coord;
	coord.row = row;
	coord.col = col;
	this->_cellCoord = coord;
}

void Cell::draw(bool isHighlight) {
//	printf("Cell(%d, %d)=%d; ", this->_i, this->_j, this->_state);
	//cout << "draw: " << this->_state;
	if (isHighlight) {
		setLightYellowText();
	}
	else {
		setLightWhiteText();
	}

	switch (this->_state) {
		case CELL_STATE_OPEN:
			switch (this->_type) {
				case CELL_TYPE_BOMB:
					setRedText();
					cout << CHAR_CELL_BOMB;
					break;
				case CELL_TYPE_NUM:
					this->_drawNum();
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

void Cell::_drawNum() {
	switch(this->_num) {
		case 1:
		case 5: setGreenText(); break;
		case 2:
		case 6: setCyanText(); break;
		case 3:
		case 7: setYellowText(); break;
		case 4:
		case 8: 
		default: setVioletText();
	}

	cout << this->_num;
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

bool Cell::isBomb() {
	return (this->_type == CELL_TYPE_BOMB);
}

void Cell::open() {
	this->_state = CELL_STATE_OPEN;
}

bool Cell::isOpen() {
	return (this->_state == CELL_STATE_OPEN);
}

bool Cell::isEmpty() {
	return (this->_type == CELL_TYPE_EMPTY);
}

void Cell::setNumber(short val) {
	this->_num = val;
	this->_type = (val > 0 ? CELL_TYPE_NUM : CELL_TYPE_EMPTY);
}

void Cell::setCellCoord(CELL_COORD val) {
	this->_cellCoord = val;
}

CELL_COORD Cell::getCellCoord() {
	return this->_cellCoord;
}

void Cell::setScreenCoord(COORD val) {
	this->_screenCoord = val;
}

COORD Cell::getScreenCoord() {
	return this->_screenCoord;
}

