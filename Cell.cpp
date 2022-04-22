#include <iostream>
#include <windows.h>

#include "console.h"
#include "Cell.h"

using namespace std;

const char CELL_CLOSED = 22;
const char CELL_FLAGGED = 3;
const char CELL_BOMB = 15;

Cell::Cell(CellType type, short i, short j) {
	this->_state = CELL_STATE_CLOSED;
	this->_type = type;
}

void Cell::draw(bool isHighlight) {
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
					cout << CELL_BOMB;
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
			cout << CELL_FLAGGED;
			break;
		default:
			cout << CELL_CLOSED;
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

void Cell::setFlag(bool value){
	if (value) {
		this->_state = CELL_STATE_FLAGGED;
	}
	else {
		this->_state = CELL_STATE_CLOSED;
	}
}

bool Cell::isFlagged(){
	return this->_state == CELL_STATE_FLAGGED;
}

bool Cell::isBomb(){
	return this->_type == CELL_TYPE_BOMB;
}

void Cell::open(){
	this->_state = CELL_STATE_OPEN;
}

void Cell::makeBomb(){
	this->_type = CELL_TYPE_BOMB;
}

void Cell::setNum(short value){
	this->_num = value;
	this->_type =(value > 0 ? CELL_TYPE_NUM : CELL_TYPE_EMPTY);
}

void Cell::setPosition(COORD pos) {
	this->_pos = pos;
}

COORD Cell::getPosition() {
	return this->_pos;
}
