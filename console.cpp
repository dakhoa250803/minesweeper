#include <cwchar>
#include <windows.h>
#include <WinCon.h>

void setColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void setWhiteText() {
	setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void setLightWhiteText() {
	setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void setBlackText() {
	setColor(0);
}

void setYellowText() {
	setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void setLightYellowText() {
	setColor(FOREGROUND_GREEN | FOREGROUND_RED);
}

void setGreenText() {
	setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void setLightGreenText() {
	setColor(FOREGROUND_GREEN);
}

void setLightRedText() {
	setColor(FOREGROUND_RED);
}

void setLargeFont() {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                  // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);	
}
