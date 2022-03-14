#include <iostream>

#include "console.h"
#include "Minesweeper.h"

int main(int argc, char** argv) {
	setLargeFont();
	Minesweeper game;
	game.start();
	return 0;
}
