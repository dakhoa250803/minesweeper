#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <windows.h>
#include <tchar.h>
#include <stdio.h>


struct MouseClickEvent {
	COORD mousePosition;
	DWORD buttonState;
};

typedef void (*MouseClickHandlerFn)(MouseClickEvent);

class Controller {
	public:
		Controller();
		void start();
		void onMouseLeftClick(MouseClickHandlerFn handler);
		void onMouseRightClick(MouseClickHandlerFn handler);

	private:
		MouseClickHandlerFn _leftClickHandler;
		MouseClickHandlerFn _rightClickHandler;

		HANDLE _getStandardInputHandle();
		void _setConsoleMode(HANDLE hStdin);
		void _waitMouseEvent(HANDLE hStdin, INPUT_RECORD* irInBuf, DWORD* ptrNumRead);
		void _emitAllEvents(INPUT_RECORD* arrInputBuffer, DWORD eventReadCount);
		void _emitMouseEvents(MOUSE_EVENT_RECORD nativeMouseEvent);
};

#endif
