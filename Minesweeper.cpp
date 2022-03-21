#include "Controller.h"
#include "GameBoard.h"
#include "Minesweeper.h"


Minesweeper::Minesweeper() {
	this->board = new GameBoard();
	this->controller = new Controller();
}

Minesweeper::~Minesweeper() {
	delete this->board;
	delete this->controller;
}

void Minesweeper::start() {
	this->board->draw();
	this->controller->start();
}


Minesweeper* game;

void onLeftClick(MouseClickEvent event) {
	printf("Left mouse event! ");
}

void onRightClick(MouseClickEvent event) {
	printf("Right mouse event! ");
}

void initializeGame() {
	game->controller->onMouseLeftClick(onLeftClick);
	game->controller->onMouseRightClick(onRightClick);
}

void createNewGame() {
	if (game != NULL) {
		delete game;
	}
	game = new Minesweeper();
	initializeGame();
}

void startGame() {
	game->start();
}

