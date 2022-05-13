#include "utils.h"

enum KeyCode {
	KEY_NONE = 0,
	KEY_ENTER = 13,
	KEY_ESC = 27,
	KEY_A = 97,
	KEY_D = 100,
	KEY_S = 115,
	KEY_W = 119,
};

KeyCode getKeyPressed();
void waitForEnter();
