#include "GameBoard.h"
#include "Minesweeper.h"

Minesweeper::Minesweeper() {
	this->_board = new GameBoard();
}

Minesweeper::~Minesweeper() {
	delete this->_board;
}

void Minesweeper::start() {
	this->_board->draw();
}
