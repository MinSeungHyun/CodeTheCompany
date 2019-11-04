#pragma once
#include <Windows.h>

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;

inline void gotoxy(COORD position) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}