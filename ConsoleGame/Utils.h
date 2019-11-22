#pragma once
#include <Windows.h>
#include <time.h>
#include <process.h>
#include "ImageUtils/ImageLayer.h"

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;

//Ŀ�� ��ġ�� �Ű��ִ� �Լ� (�Ķ����  COORD)
inline void gotoxy(COORD position) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

//Ŀ�� ��ġ�� �Ű��ִ� �Լ�  (�Ķ���� int x, int y)
inline void gotoXY(int x, int y) {
	gotoxy((COORD) { x, y });
}

//���ڿ��� ���� ������ �����ִ� �Լ�
inline char* ltrim(char* str) {
	const char* seps = "\t\n\v\f\r ";
	const size_t totrim = strspn(str, seps);
	if (totrim > 0) {
		const size_t len = strlen(str);
		if (totrim == len) {
			str[0] = '\0';
		}
		else {
			memmove(str, str + totrim, len + 1 - totrim);
		}
	}
	return str;
}

//���ڿ��� ������ ������ �����ִ� �Լ�
inline char* rtrim(char* str) {
	const char* seps = "\t\n\v\f\r ";
	int i = strlen(str) - 1;
	while (i >= 0 && strchr(seps, str[i]) != NULL) {
		str[i] = '\0';
		i--;
	}
	return str;
}

//���ڿ��� �¿� ������ ��� �������ִ� �Լ�
inline char* trim(char* str) {
	return ltrim(rtrim(str));
}

//������ �����ϴ��� Ȯ���ϴ� �Լ�
inline int isFileExist(char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) return 0;
	fclose(file);
	return 1;
}

//������ �������� �ʴ´ٸ� ���� ����� �Լ�
inline void makeFileIfNotExist(char* fileName) {
	if (isFileExist(fileName)) return;
	fclose(fopen(fileName, "w"));
}

//���� �ð��� ��ȯ
inline struct tm* getCurrentTime() {
	time_t rawTime;
	time(&rawTime);
	struct tm* timeInfo = localtime(&rawTime);
	return timeInfo;
}

//���� �ð����� �ʸ� ��ȯ
inline int getCurrentSecond() {
	return getCurrentTime()->tm_sec;
}

int isSecondClockRunning = 0;

//�� �ʸ��� Ư�� �Լ��� ��������ִ� �Լ�
inline void timerThread(void* param) {
	const _beginthread_proc_type onAlarm = (_beginthread_proc_type)param;
	int second = 0, cnt = 0;
	int previousSecond = -1;
	while (isSecondClockRunning) {
		second = getCurrentSecond();
		if (second != previousSecond)
			_beginthread(onAlarm, 0, (void*)cnt++);
		previousSecond = second;
	}
}

//timerThread �Լ��� thread�� ���������
inline void startSecondClock(_beginthread_proc_type callback) {
	isSecondClockRunning = 1;
	_beginthread(timerThread, 0, callback);
}

//timerThread �Լ��� ������ ����
inline void stopSecondClock() {
	isSecondClockRunning = 0;
}

//hdc�� �ؽ�Ʈ�� ����ϴ� �Լ�(�Ķ���Ϳ� ������ ����)
inline void printTextWithAngle(HDC hdc, int x, int y, int size, int weight, int angle, COLORREF textColor, int align, char* text) {
	if (weight == 0) weight = 900;
	size = (int)(size * RESOLUTION_MULTIPLIER);
	const HFONT font = CreateFont(size, 0, angle, 0, weight, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�ձٸ��"));

	SelectObject(hdc, font);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, textColor);
	SetTextAlign(hdc, align);

	x = (int)(x * RESOLUTION_MULTIPLIER);
	y = (int)(y * RESOLUTION_MULTIPLIER);
	TextOut(hdc, x, y, text, lstrlen(text));

	PAINTSTRUCT paint;
	EndPaint(WINDOW_HANDLE, &paint);

	DeleteObject(font);
}

//printTextWithAngle �Լ��� �����ϳ� �Ķ���Ϳ� ������ ����
inline void printText(HDC hdc, int x, int y, int size, int weight, COLORREF textColor, int align, char* text) {
	printTextWithAngle(hdc, x, y, size, weight, 0, textColor, align, text);
}