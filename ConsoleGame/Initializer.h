#pragma once
#include <stdio.h>
#include <Windows.h>
#include "Utils.h"

#ifndef INITIALIZER_H
#define INITIALIZER_H

#define CONSOLE_WIDTH 180
#define CONSOLE_HEIGHT 48

//�ʿ��� �ڵ��� �Ҵ���
inline void getHandle() {
	CONSOLE_INPUT = GetStdHandle(STD_INPUT_HANDLE);
	CONSOLE_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	WINDOW_HANDLE = GetConsoleWindow();
}

//�ܼ��� Ŀ���� ������
inline void clearCursor() {
	CONSOLE_CURSOR_INFO c;
	c.bVisible = FALSE;
	c.dwSize = 1;
	SetConsoleCursorInfo(CONSOLE_OUTPUT, &c);
}

//�ܼ��� ũ�⸦ �ٲ���
inline void resizeConsole(int w, int h) {
	char temp[100];
	sprintf(temp, "mode con cols=%d lines=%d", w, h);
	system(temp);
}

//�ֿܼ��� ���콺 �Է��� �����ϰ� ����
inline void enableMouseInput() {
	DWORD mode;
	GetConsoleMode(CONSOLE_INPUT, &mode);
	SetConsoleMode(CONSOLE_INPUT, mode | ENABLE_MOUSE_INPUT);
}

//���� �ִ� �Լ���� ������ �ʱ�ȭ ����
inline void initialize() {
	getHandle();
	resizeConsole(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	clearCursor();
	enableMouseInput();
}

#endif