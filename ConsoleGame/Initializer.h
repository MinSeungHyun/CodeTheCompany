#pragma once
#include <stdio.h>
#include <Windows.h>
#include "Utils.h"

#ifndef INITIALIZER_H
#define INITIALIZER_H

#define CONSOLE_WIDTH 180
#define CONSOLE_HEIGHT 48

//필요한 핸들을 할당함
inline void getHandle() {
	CONSOLE_INPUT = GetStdHandle(STD_INPUT_HANDLE);
	CONSOLE_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	WINDOW_HANDLE = GetConsoleWindow();
}

//콘솔의 커서를 없에줌
inline void clearCursor() {
	CONSOLE_CURSOR_INFO c;
	c.bVisible = FALSE;
	c.dwSize = 1;
	SetConsoleCursorInfo(CONSOLE_OUTPUT, &c);
}

//콘솔의 크기를 바꿔줌
inline void resizeConsole(int w, int h) {
	char temp[100];
	sprintf(temp, "mode con cols=%d lines=%d", w, h);
	system(temp);
}

//콘솔에서 마우스 입력을 가능하게 해줌
inline void enableMouseInput() {
	DWORD mode;
	GetConsoleMode(CONSOLE_INPUT, &mode);
	SetConsoleMode(CONSOLE_INPUT, mode | ENABLE_MOUSE_INPUT);
}

//위에 있는 함수들로 게임을 초기화 해줌
inline void initialize() {
	getHandle();
	resizeConsole(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	clearCursor();
	enableMouseInput();
}

#endif