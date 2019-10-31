#pragma once
#include <Windows.h>

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;

void gotoxy(COORD position) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

COORD newCOORD(int x, int y) {
	COORD result = { x, y };
	return result;
}