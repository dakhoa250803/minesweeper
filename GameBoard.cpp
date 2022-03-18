#include <iostream>
#include <windows.h>
#include "console.h"
#include "GameBoard.h"
#include "utils.h"

using namespace std;

const char BOARD_TOP_LEFT = 201;
const char BOARD_BOTTOM_LEFT = 200;
const char BOARD_TOP_RIGHT = 187;
const char BOARD_BOTTOM_RIGHT = 188;
const char BOARD_HOZ_BAR = 205; // horizontal bar
const char BOARD_VER_BAR = 186; // vertical bar
const char BOARD_BLOCK = 197;
const char BOARD_EMPTY_CELL = ' ';

const short BOARD_MARGIN_TOP = 3;
const short BOARD_MARGIN_LEFT = 5;
const short BOARD_MARGIN_BOTTOM = 1;
const short BOARD_CELL_COLS = 40;
const short BOARD_CELL_ROWS = 20;
const short BOARD_WIDTH = BOARD_CELL_COLS + 2;
const short BOARD_HEIGHT = BOARD_CELL_ROWS + 2;



GameBoard::GameBoard() {
	this->_rootPoint.X = BOARD_MARGIN_LEFT;
	this->_rootPoint.Y = BOARD_MARGIN_TOP;
	this->_initCells();
	this->_boardDrawn = false;
}

void GameBoard::_drawRow(char c, int width) {
	for (int w = 0; w < width; ++w) {
		cout << c;
	}
}

void GameBoard::_drawBoardTop(COORD fromPoint) {
	gotoxy(fromPoint.X, fromPoint.Y);
	cout << BOARD_TOP_LEFT;
	this->_drawRow(BOARD_HOZ_BAR, BOARD_CELL_COLS);
	cout << BOARD_TOP_RIGHT;
}

void GameBoard::_drawBoardBody(COORD fromPoint) {
	for (int h = 0; h < BOARD_CELL_ROWS; ++h) {
		gotoxy(fromPoint.X, fromPoint.Y + h);
		cout << BOARD_VER_BAR;

		gotoxy(fromPoint.X + BOARD_CELL_COLS + 1, fromPoint.Y + h);
		cout << BOARD_VER_BAR;
	}
}

void GameBoard::_drawBoardBottom(COORD fromPoint) {
	gotoxy(fromPoint.X, fromPoint.Y);
	cout << BOARD_BOTTOM_LEFT;
	this->_drawRow(BOARD_HOZ_BAR, BOARD_CELL_COLS);
	cout << BOARD_BOTTOM_RIGHT;
}



void GameBoard::drawBoard() {
	setWhiteText();
	if (!this->_boardDrawn) {
		COORD root = this->_rootPoint;
		this->_drawBoardTop(root);
		
		root.Y++;
		this->_drawBoardBody(root);
	
		root.Y += BOARD_CELL_ROWS;
		this->_drawBoardBottom(root);
		
		this->_boardDrawn = true;
	}

	COORD cellFrom;
	cellFrom.X = this->_rootPoint.X + 1;
	cellFrom.Y = this->_rootPoint.Y + 1;
	this->_drawCells(cellFrom);
	this->_drawBottomSpace();
}

void GameBoard::_drawBottomSpace() {
	COORD bottom = this->_rootPoint;
	bottom.X = 0;
	bottom.Y += BOARD_HEIGHT + BOARD_MARGIN_BOTTOM;
	gotoxy(bottom.X, bottom.Y);
}

void GameBoard::_drawCells(COORD fromPoint) {
	for (int i = 0; i < BOARD_CELL_ROWS; ++i) {
		for (int j = 0; j < BOARD_CELL_COLS; ++j) {
			gotoxy(fromPoint.X + j, fromPoint.Y + i);
			this->_cells[i][j]->draw();
		}
	}
}

void GameBoard::_initCells() {
	this->_cells = new Cell**[BOARD_CELL_ROWS];
	for (short i = 0; i < BOARD_CELL_ROWS; ++i) {
		this->_cells[i] = new Cell*[BOARD_CELL_COLS];
		for (short j = 0; j < BOARD_CELL_COLS; ++j) {
			this->_cells[i][j] = new Cell(CELL_TYPE_EMPTY);
		}
	}
}
