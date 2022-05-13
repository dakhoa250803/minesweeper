#include <conio.h>
#include <iostream>
#include "keyboard.h"

KeyCode getKeyPressed() {
	return (KeyCode)_getch();
}

void waitForEnter(){
	KeyCode key;
	while((key = getKeyPressed()) != KEY_ENTER);
}
