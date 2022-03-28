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

const char CELL_VER_BAR = 179;

const short BOARD_MARGIN_TOP = 3;
const short BOARD_MARGIN_LEFT = 5;
const short BOARD_MARGIN_BOTTOM = 1;
const short BOARD_CELL_COLS = 40;
const short BOARD_CELL_ROWS = 20;
const short BOARD_WIDTH = BOARD_CELL_COLS + 2;
const short BOARD_HEIGHT = BOARD_CELL_ROWS + 2;



GameBoard::GameBoard() {
	this->_boardRootPoint.X = BOARD_MARGIN_LEFT;
	this->_boardRootPoint.Y = BOARD_MARGIN_TOP;
	this->_cellsRootPoint.X = this->_boardRootPoint.X + 1;
	this->_cellsRootPoint.Y = this->_boardRootPoint.Y + 1;
	this->_initCells();
	this->_boardDrawn = false;
	this->_highlightedCol = -1;
	this->_highlightedRow = -1;
}

void GameBoard::_drawRow(char c, int width) {
	for (int w = 0; w < width; ++w) {
		cout << c;
	}
}

void GameBoard::_drawBoardTop(COORD fromPoint) {
	gotoxy(fromPoint.X, fromPoint.Y);
	cout << BOARD_TOP_LEFT;
	this->_drawRow(BOARD_HOZ_BAR, BOARD_WIDTH - 1);
	cout << BOARD_TOP_RIGHT;
}

void GameBoard::_drawBoardBody(COORD fromPoint) {
	for (int h = 0; h < BOARD_CELL_ROWS; ++h) {
		gotoxy(fromPoint.X, fromPoint.Y + h);
		cout << BOARD_VER_BAR;

		gotoxy(fromPoint.X + BOARD_WIDTH  , fromPoint.Y + h);
		cout << BOARD_VER_BAR;
	}
}

void GameBoard::_drawBoardBottom(COORD fromPoint) {
	gotoxy(fromPoint.X, fromPoint.Y);
	cout << BOARD_BOTTOM_LEFT;
	this->_drawRow(BOARD_HOZ_BAR, BOARD_WIDTH - 1);
	cout << BOARD_BOTTOM_RIGHT;
}



void GameBoard::drawBoard() {
	setWhiteText();
	if (!this->_boardDrawn) {
		COORD root = this->_boardRootPoint;
		this->_drawBoardTop(root);
		
		root.Y++;
		this->_drawBoardBody(root);
	
		root.Y += BOARD_CELL_ROWS;
		this->_drawBoardBottom(root);
		
		this->_boardDrawn = true;
	}

	this->_drawCells(this->_cellsRootPoint);
	this->_drawBottomSpace();
}

void GameBoard::highlightCell(short col, short row){
	this->_highlightedCol = col - this->_cellsRootPoint.X;
	this->_highlightedRow = row - this->_cellsRootPoint.Y;
}

void GameBoard::flagCell(short col, short row){
	short cellCol = col - this->_cellsRootPoint.X;
	short cellRow = row - this->_cellsRootPoint.Y;
	CellPtr cell = this->_cells[cellRow][cellCol/2];
	cell->setFlag(true);
}

void GameBoard::_drawBottomSpace() {
	COORD bottom = this->_boardRootPoint;
	bottom.X = 0;
	bottom.Y += BOARD_HEIGHT + BOARD_MARGIN_BOTTOM;
	gotoxy(bottom.X, bottom.Y);
}

void GameBoard::_drawCells(COORD fromPoint) {
	for (int i = 0; i < BOARD_CELL_ROWS; ++i) {
		for (int j = 0; j < BOARD_WIDTH; j+=2) {
			short cellX = fromPoint.X + j;
			if(j > 0){
				--cellX;
			}
			gotoxy(cellX, fromPoint.Y + i);
			if(j > 0){
				setWhiteText();
				cout << CELL_VER_BAR;
			}
			if(i == this->_highlightedRow && j == this->_highlightedCol){
				this->_cells[i][j/2]->draw(true);
			}
			else{
				this->_cells[i][j/2]->draw();
			}
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


