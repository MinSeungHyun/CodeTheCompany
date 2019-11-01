#pragma once
#include <Windows.h>

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;

inline void gotoxy(COORD position) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

inline COORD Coord(int x, int y) {
	const COORD result = { x, y };
	return result;
}