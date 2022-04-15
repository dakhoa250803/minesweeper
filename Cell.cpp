#include <iostream>
#include <windows.h>

#include "console.h"
#include "Cell.h"

using namespace std;

const char CELL_CLOSED = 22;
const char CELL_FLAGGED = 3;
const char CELL_BOMB = 15;

Cell::Cell(CellType type) {
	this->_state = CELL_STATE_CLOSED;
	this->_type = type;
}

void Cell::draw(bool isHighlight) {
	if (isHighlight) {
		setLightGreenText();
	}
	else {
		setWhiteText();
	}
	switch(this->_state){
		case CELL_STATE_OPEN:
			switch(this->_type){
				case CELL_TYPE_BOMB:
					setLightRedText();
					cout << CELL_BOMB;
					break;
				default:
					cout << " ";
			}
			break;
		case CELL_STATE_FLAGGED:
			setLightRedText();
			cout << CELL_FLAGGED;
			break;
		default:
			cout << CELL_CLOSED;
	}
	
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

void Cell::open(){
	this->_state = CELL_STATE_OPEN;
}

void Cell::makeBomb(){
	this->_type = CELL_TYPE_BOMB;
}
