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
const short BOARD_WIDTH = BOARD_CELL_COLS*2;
const short BOARD_HEIGHT = BOARD_CELL_ROWS + 2;

const short BOMB_COUNT = 20;

GameBoard::GameBoard() {
	this->_boardRootPoint.X = BOARD_MARGIN_LEFT;
	this->_boardRootPoint.Y = BOARD_MARGIN_TOP;
	this->_cellsRootPoint.X = this->_boardRootPoint.X + 1;
	this->_cellsRootPoint.Y = this->_boardRootPoint.Y + 1;
	this->_boardDrawn = false;
	this->_highlightedCol = -1;
	this->_highlightedRow = -1;
	this->_bombCellsLength = 0;
	this->_initCells();
	this->_setCellTypes();
}

GameBoard::~GameBoard(){
	this->_destroyCells();
	delete this->_bombCells;
}

void GameBoard::_drawRow(char c, int width) {
	for (int w = 0; w < width; ++w) {
		cout << c;
	}
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

void GameBoard::toggleFlagCell(short col, short row){
	short cellCol = col - this->_cellsRootPoint.X;
	short cellRow = row - this->_cellsRootPoint.Y;
	CellPtr cell = this->_getCellAt(cellRow,cellCol);
	if(cell->isFlagged()){
		cell->setFlag(false);
	}
	else{
		cell->setFlag(true);
	}
}

void GameBoard::openCell(short col, short row){
	short cellCol = col - this->_cellsRootPoint.X;
	short cellRow = row - this->_cellsRootPoint.Y;
	if(this->_isInBoard(cellCol,cellRow)){
		CellPtr cell = this->_getCellAt(cellCol,cellRow);
		cell->open();
	}
}

bool GameBoard::_isInBoard(short col, short row){
	return (col < BOARD_WIDTH && col >= 0 && row < BOARD_CELL_ROWS && row >= 0);
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

		gotoxy(fromPoint.X + BOARD_WIDTH , fromPoint.Y + h);
		cout << BOARD_VER_BAR;
	}
}

void GameBoard::_drawBoardBottom(COORD fromPoint) {
	gotoxy(fromPoint.X, fromPoint.Y);
	cout << BOARD_BOTTOM_LEFT;
	this->_drawRow(BOARD_HOZ_BAR, BOARD_WIDTH - 1);
	cout << BOARD_BOTTOM_RIGHT;
}

void GameBoard::_drawBottomSpace() {
	COORD bottom = this->_boardRootPoint;
	bottom.X = 0;
	bottom.Y += BOARD_HEIGHT + BOARD_MARGIN_BOTTOM;
	gotoxy(bottom.X, bottom.Y);
}

void GameBoard::_drawCells(COORD fromPoint) {
	for (int y = 0; y < BOARD_CELL_ROWS; ++y) {
		for (int x = 0; x < BOARD_WIDTH; x+=2) {
			short cellX = fromPoint.X + x;
			if(x > 0){
				--cellX;
			}
			gotoxy(cellX, fromPoint.Y + y);
			if(x > 0){
				setWhiteText();
				cout << CELL_VER_BAR;
			}
			if(y == this->_highlightedRow && x == this->_highlightedCol){
				this->_getCellAt(x,y)->draw(true);
			}
			else{
				this->_getCellAt(x,y)->draw();
			}
		}
	}
}

void GameBoard::_initCells() {
	this->_cells = new Cell**[BOARD_CELL_ROWS];
	for (short y = 0; y < BOARD_CELL_ROWS; ++y) {
		this->_cells[y] = new Cell*[BOARD_CELL_COLS];
		for (short x = 0; x < BOARD_CELL_COLS; ++x) {
			this->_cells[y][x] = new Cell(CELL_TYPE_EMPTY);
		}
	}
}



void GameBoard::_setCellTypes() {
	// Iterate all cells
	// For each cell:
	//  - If is random bomb -> set bomb
	//  - else look around -> set number
	//         if number == 0 -> set empty
	this->_randomizeBombCells();
	for(short row = 0; row < BOARD_CELL_ROWS; ++row){
		for(short col = 0; col < BOARD_CELL_COLS; ++col){
			CellPtr cell = this->_cells[row][col];
			
			for(int k = 0; k < this->_bombCellsLength;++k){
				if(col == this->_bombCells[k].X && row == this->_bombCells[k].Y){
					cell->makeBomb();
				}
						
			}
		}
	}
}


void GameBoard::_randomizeBombCells() {
	this->_bombCells = new COORD[BOMB_COUNT];
	COORD bomb;
	int i = 0;
	bool bombExists;

	while (i < BOMB_COUNT) {
		bomb.X = randomNumInRange(0, BOARD_CELL_COLS - 1);
		bomb.Y = randomNumInRange(0, BOARD_CELL_ROWS - 1);

		bombExists = false;
		for (int j = 0; j < this->_bombCellsLength; ++j) {
			if (bomb.X == this->_bombCells[j].X && bomb.Y == this->_bombCells[j].Y) {
				bombExists = true;
				break;
			}
		}
		if (bombExists) {
			continue; // randomize again!
		}
		else {
			this->_bombCells[i] = bomb;
			++this->_bombCellsLength;
			++i;
		}
	}
}
CellPtr GameBoard::_getCellAt(short screenX, short screenY){
	short col = this->_toCellCol(screenX);
	short row = screenY;
	if(col >= 0 && col < BOARD_CELL_COLS && row >= 0 && row < BOARD_CELL_ROWS){
		return this->_cells[row][col];
	}
	return NULL;
}

short GameBoard::_toCellCol(short screenX){
	return screenX/2;
}

void GameBoard::_destroyCells() {
	for (short i = 0; i < BOARD_CELL_ROWS; ++i) {
		for (short j = 0; j < BOARD_CELL_COLS; ++j) {
			delete[] this->_cells[j];
		}
	}
	delete[] this->_cells;
}
