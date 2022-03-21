#include <tchar.h>
#include <stdexcept>
#include <stdio.h>
#include <windows.h>

#include "Controller.h"

#define INPUT_BUFFER_SIZE 128

Controller::Controller() {
}

void Controller::onMouseLeftClick(MouseClickHandlerFn handler) {
	this->_leftClickHandler = handler;
}

void Controller::onMouseRightClick(MouseClickHandlerFn handler) {
	this->_rightClickHandler = handler;
}

void Controller::start() {
	HANDLE hStdin = this->_getStandardInputHandle();
	this->_setConsoleMode(hStdin);

	DWORD eventReadCount;
	// https://docs.microsoft.com/en-us/windows/console/input-record-str
	INPUT_RECORD* arrInputBuffer = new INPUT_RECORD[INPUT_BUFFER_SIZE];
    while (true) {
    	this->_waitMouseEvent(hStdin, arrInputBuffer, &eventReadCount);
    	this->_emitAllEvents(arrInputBuffer, eventReadCount);
    }
}

HANDLE Controller::_getStandardInputHandle() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE) {
    	throw std::runtime_error("Failed to GetStdHandle");
	}
}

void Controller::_setConsoleMode(HANDLE hStdin) {	
    DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS;
    if (!SetConsoleMode(hStdin, fdwMode)) {
    	throw std::runtime_error("Failed to SetConsoleMode");
	}
}

void Controller::_waitMouseEvent(HANDLE hStdin, INPUT_RECORD* arrInputBuffer, DWORD* ptrEventReadCount) {
	// https://docs.microsoft.com/en-us/windows/console/readconsoleinput
	BOOL readSuccess = ReadConsoleInput(hStdin, arrInputBuffer, INPUT_BUFFER_SIZE, ptrEventReadCount);
	if (!readSuccess) {
        throw std::runtime_error("Failed to ReadConsoleInput");
	}
}

void Controller::_emitAllEvents(INPUT_RECORD* arrInputBuffer, DWORD eventReadCount) {
	for (int i = 0; i < eventReadCount; i++) {
        if (arrInputBuffer[i].EventType == MOUSE_EVENT) {
            this->_emitMouseEvents(arrInputBuffer[i].Event.MouseEvent);
		}
    }
}

void Controller::_emitMouseEvents(MOUSE_EVENT_RECORD nativeEvent) {
	// https://docs.microsoft.com/en-us/windows/console/mouse-event-record-str
	MouseClickEvent mouseClickEvent;
	mouseClickEvent.buttonState = nativeEvent.dwButtonState;
	mouseClickEvent.mousePosition = nativeEvent.dwMousePosition;
	if (nativeEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
		this->_leftClickHandler(mouseClickEvent);
	}
	else if (nativeEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
		this->_rightClickHandler(mouseClickEvent);
	}
}

