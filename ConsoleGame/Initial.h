#pragma once
#include <stdio.h>
#include <Windows.h>

#define CONSOLE_WIDTH 180
#define CONSOLE_HEIGHT 48


void clearCursor() {
	CONSOLE_CURSOR_INFO c;
	c.bVisible = FALSE;
	c.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}

void resizeConsole(int w, int h) {
	char temp[100];
	sprintf(temp, "mode con cols=%d lines=%d", w, h);
	system(temp);
}

void initialize() {
	resizeConsole(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	clearCursor();
}