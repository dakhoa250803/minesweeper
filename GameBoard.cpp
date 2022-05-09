#include <iostream>
#include <windows.h>
#include "console.h"
#include "utils.h"
#include "Cell.h"
#include "GameBoard.h"
using namespace std;

const char BOARD_TOP_LEFT = 201;
const char BOARD_BOTTOM_LEFT = 200;
const char BOARD_TOP_RIGHT = 187;
const char BOARD_BOTTOM_RIGHT = 188;
const char BOARD_HOZ_BAR = 205; // horizontal bar
const char BOARD_VER_BAR = 186; // vertical bar
const char BOARD_EMPTY_CELL = ' ';
//const char BOARD_CROSS_CELL = 197; //176; //' ';
const char CELL_VER_BAR = 179;

const short BOARD_MARGIN_TOP = 3;
const short BOARD_MARGIN_LEFT = 5;
const short BOARD_MARGIN_BOTTOM = 1;
const short BOARD_CELL_COLS = 40;
const short BOARD_CELL_ROWS = 20;
const short BOARD_WIDTH = BOARD_CELL_COLS * 2;
const short BOARD_HEIGHT = BOARD_CELL_ROWS + 2;
const short BOMB_COUNT = 100;

GameBoard::GameBoard() {
	this->_boardRootPoint.X = BOARD_MARGIN_LEFT;
	this->_boardRootPoint.Y = BOARD_MARGIN_TOP;
	this->_cellsRootPoint.X = this->_boardRootPoint.X + 1;
	this->_cellsRootPoint.Y = this->_boardRootPoint.Y + 1;
	this->_boardDrawn = false;
	this->_highlightedX = -1; // Out of board
	this->_highlightedY = -1;
	this->_bombCellsLength = 0;
	this->_initCells();
	this->_setCellTypes();
}

GameBoard::~GameBoard() {
	this->_destroyCells();
	delete[] this->_bombCells;
}

void GameBoard::draw() {
	this->_drawCells(this->_cellsRootPoint);
	
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

	this->_drawBottomSpace();
}

void GameBoard::_redraw(CellPtr cell) {
	if (cell != NULL) {
		COORD pos = cell->getScreenCoord();
		gotoxy(pos.X, pos.Y);
		cell->draw();
		this->_drawBottomSpace();
	}
}

void GameBoard::highlightCell(COORD pos) {
	this->_highlightedX = pos.X - this->_cellsRootPoint.X;
	this->_highlightedY = pos.Y - this->_cellsRootPoint.Y;
}

void GameBoard::tryOpenCell(COORD pos) {
	short cellX = pos.X - this->_cellsRootPoint.X;
	short cellY = pos.Y - this->_cellsRootPoint.Y;
	CellPtr cell = this->_getCellAt(cellX, cellY);
	if (cell != NULL) {
		this->_openCell(cell);
	}
	printf("Left(%d, %d); ", pos.X, pos.Y);
}

void GameBoard::_openCell(CellPtr cell) {
	if (cell->isBomb()) {
		// End game >"<
		// return;
	}
	if (cell->isFlagged() || cell->isOpen()) return;

	cell->open();
	this->_redraw(cell);

	if (!cell->isEmpty()) return;
	
	// Open neighbors
	CellMatrix cells = this->_cells;
	CELL_COORD cellCoord = cell->getCellCoord();
	short curRow = cellCoord.row,
		curCol = cellCoord.col;
	
	// top-left
	if (curRow-1 >= 0 && curCol-1 >= 0) {
		this->_openCell(cells[curRow-1][curCol-1]);
	}
	// top-center
	if (curRow-1 >= 0) {
		this->_openCell(cells[curRow-1][curCol]);
	}
	// top-right
	if (curRow-1 >= 0 && curCol+1 < BOARD_CELL_COLS) {
		this->_openCell(cells[curRow-1][curCol+1]);
	}
	// mid-right
	if (curCol+1 < BOARD_CELL_COLS) {
		this->_openCell(cells[curRow][curCol+1]);
	}
	// bottom-right
	if (curRow+1 < BOARD_CELL_ROWS && curCol+1 < BOARD_CELL_COLS) {
		this->_openCell(cells[curRow+1][curCol+1]);
	}
	// bottom-center
	if (curRow+1 < BOARD_CELL_ROWS) {
		this->_openCell(cells[curRow+1][curCol]);
	}
	// bottom-left
	if (curRow+1 < BOARD_CELL_ROWS && curCol-1 >= 0) {
		this->_openCell(cells[curRow+1][curCol-1]);
	}
	// mid-left
	if (curCol-1 >= 0) {
		this->_openCell(cells[curRow][curCol-1]);
	}
}

void GameBoard::toggleFlagCell(COORD pos) {
	short cellX = pos.X - this->_cellsRootPoint.X;
	short cellY = pos.Y - this->_cellsRootPoint.Y;
	CellPtr cell = this->_getCellAt(cellX, cellY);
	if (cell == NULL) return;
	
	if (cell->isOpen()) {
		// rippleOpen
	} else {
		cell->setFlag(! cell->isFlagged());
	}

	this->_redraw(cell);
	printf("Right(%d, %d); ", pos.X, pos.Y);
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

		gotoxy(fromPoint.X + BOARD_WIDTH, fromPoint.Y + h);
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
			COORD cellPos;
			cellPos.X = cellX;
			cellPos.Y = fromPoint.Y + y;
			
			if (x > 0) {
				--cellX;
			}
			gotoxy(cellX, cellPos.Y);
			if (x > 0) {
				setLightWhiteText();
				cout << CELL_VER_BAR;
			}

			CellPtr cell = this->_getCellAt(x, y);
			cell->setScreenCoord(cellPos);
			if (y == this->_highlightedY && x == this->_highlightedX) {
				cell->draw(true);
			}
			else {
				cell->draw();
			}
		}
	}
}

void GameBoard::_initCells() {
	this->_cells = new Cell**[BOARD_CELL_ROWS];
	for (short row = 0; row < BOARD_CELL_ROWS; ++row) {
		this->_cells[row] = new Cell*[BOARD_CELL_COLS];
		for (short col = 0; col < BOARD_CELL_COLS; ++col) {
			this->_cells[row][col] = new Cell(CELL_TYPE_EMPTY, row, col);
		}
	}
}

void GameBoard::_destroyCells() {
	for (short i = 0; i < BOARD_CELL_ROWS; ++i) {
		for (short j = 0; j < BOARD_CELL_COLS; ++j) {
			delete this->_cells[i][j];
		}
		delete[] this->_cells[i];
	}
	delete[] this->_cells;
}

void GameBoard::_setCellTypes() {
	// Iterate all cells
	// For each cell:
	//  - If is random bomb -> set bomb
	//  - else look around -> set number
	//         if number == 0 -> set empty
	this->_randomizeBombCells();
	for (short row = 0; row < BOARD_CELL_ROWS; ++row) {
		for (short col = 0; col < BOARD_CELL_COLS; ++col) {
			CellPtr cell = this->_cells[row][col];
			if (this->_bombExists(row, col)) {
				cell->makeBomb();
			}
		}
	}

	for (short row = 0; row < BOARD_CELL_ROWS; ++row) {
		for (short col = 0; col < BOARD_CELL_COLS; ++col) {
			CellPtr cell = this->_cells[row][col];

			if (!cell->isBomb()) {
				short bombCount = this->_countNeighborBombs(row, col);
				cell->setNumber(bombCount);
			}
		}
	}
}

short GameBoard::_countNeighborBombs(short row, short col) {
	short count = 0;
	CellMatrix cells = this->_cells;
	// top-left
	if (row-1 >= 0 && col-1 >= 0 && cells[row-1][col-1]->isBomb()) {
		++count;
	}
	// top-center
	if (row-1 >= 0 && cells[row-1][col]->isBomb()) {
		++count;
	}
	// top-right
	if (row-1 >= 0 && col+1 < BOARD_CELL_COLS && cells[row-1][col+1]->isBomb()) {
		++count;
	}
	// mid-right
	if (col+1 < BOARD_CELL_COLS && cells[row][col+1]->isBomb()) {
		++count;
	}
	// bottom-right
	if (row+1 < BOARD_CELL_ROWS && col+1 < BOARD_CELL_COLS && cells[row+1][col+1]->isBomb()) {
		++count;
	}
	// bottom-center
	if (row+1 < BOARD_CELL_ROWS && cells[row+1][col]->isBomb()) {
		++count;
	}
	// bottom-left
	if (row+1 < BOARD_CELL_ROWS && col-1 >= 0 && cells[row+1][col-1]->isBomb()) {
		++count;
	}
	// mid-left
	if (col-1 >= 0 && cells[row][col-1]->isBomb()) {
		++count;
	}
	return count;
}

void GameBoard::_randomizeBombCells() {
	this->_bombCells = new CELL_COORD[BOMB_COUNT];
	CELL_COORD bomb;
	int i = 0;

	while (i < BOMB_COUNT) {
		bomb.col = randomNumInRange(0, BOARD_CELL_COLS - 1);
		bomb.row = randomNumInRange(0, BOARD_CELL_ROWS - 1);

		if (this->_bombExists(bomb.row, bomb.col)) {
			continue; // randomize again!
		}
		else {
			this->_bombCells[i] = bomb;
			++this->_bombCellsLength;
			++i;
		}
	}
}

bool GameBoard::_bombExists(short row, short col) {
	for (int i = 0; i < this->_bombCellsLength; ++i) {
		if (row == this->_bombCells[i].row && col == this->_bombCells[i].col) {
			return true;
		}
	}
	return false;
}

CellPtr GameBoard::_getCellAt(short screenX, short screenY) {
	short col = this->_toCellCol(screenX);
	short row = screenY;
	if (col >= 0 && col < BOARD_CELL_COLS &&
		row >= 0 && row < BOARD_CELL_ROWS) {
		return this->_cells[row][col];
	}
	return NULL;
}

short GameBoard::_toCellCol(short screenX) {
	return screenX / 2;
}

