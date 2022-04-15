#include "Controller.h"
#include "GameBoard.h"
#include "Minesweeper.h"


GameBoard* board;
Controller* controller;

void onLeftClick(MouseClickEvent event) {
	COORD pos = event.mousePosition;
	printf("Left(%d, %d); ", pos.X, pos.Y);
	board->tryOpenCell(pos);
	board->draw();
}

void onRightClick(MouseClickEvent event) {
	COORD pos = event.mousePosition;
	board->toggleFlagCell(pos);
	board->draw();
}

void initializeGame() {
	board = new GameBoard();
	controller = new Controller();
	controller->onMouseLeftClick(onLeftClick);
	controller->onMouseRightClick(onRightClick);
}

void resetGame() {
	delete board;
	board = NULL;
	delete controller;
	controller = NULL;
}

void startGame() {
	board->draw();
	controller->start();
}

void createNewGame() {
	if (board != NULL) {
		resetGame();
	}
	initializeGame();
}

