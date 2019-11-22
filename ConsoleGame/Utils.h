#pragma once
#include <Windows.h>
#include <time.h>
#include <process.h>
#include "ImageUtils/ImageLayer.h"

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;

//커서 위치를 옮겨주는 함수 (파라미터  COORD)
inline void gotoxy(COORD position) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

//커서 위치를 옮겨주는 함수  (파라미터 int x, int y)
inline void gotoXY(int x, int y) {
	gotoxy((COORD) { x, y });
}

//문자열의 왼쪽 공백을 없에주는 함수
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

//문자열의 오른쪽 공백을 없에주는 함수
inline char* rtrim(char* str) {
	const char* seps = "\t\n\v\f\r ";
	int i = strlen(str) - 1;
	while (i >= 0 && strchr(seps, str[i]) != NULL) {
		str[i] = '\0';
		i--;
	}
	return str;
}

//문자열의 좌우 공백을 모두 제거해주는 함수
inline char* trim(char* str) {
	return ltrim(rtrim(str));
}

//파일이 존재하는지 확인하는 함수
inline int isFileExist(char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) return 0;
	fclose(file);
	return 1;
}

//파일이 존재하지 않는다면 새로 만드는 함수
inline void makeFileIfNotExist(char* fileName) {
	if (isFileExist(fileName)) return;
	fclose(fopen(fileName, "w"));
}

//현재 시간을 반환
inline struct tm* getCurrentTime() {
	time_t rawTime;
	time(&rawTime);
	struct tm* timeInfo = localtime(&rawTime);
	return timeInfo;
}

//현재 시간에서 초만 반환
inline int getCurrentSecond() {
	return getCurrentTime()->tm_sec;
}

int isSecondClockRunning = 0;

//매 초마다 특정 함수를 실행시켜주는 함수
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

//timerThread 함수를 thread로 실행시켜줌
inline void startSecondClock(_beginthread_proc_type callback) {
	isSecondClockRunning = 1;
	_beginthread(timerThread, 0, callback);
}

//timerThread 함수의 루프를 멈춤
inline void stopSecondClock() {
	isSecondClockRunning = 0;
}

//hdc에 텍스트를 출력하는 함수(파라미터에 각도도 있음)
inline void printTextWithAngle(HDC hdc, int x, int y, int size, int weight, int angle, COLORREF textColor, int align, char* text) {
	if (weight == 0) weight = 900;
	size = (int)(size * RESOLUTION_MULTIPLIER);
	const HFONT font = CreateFont(size, 0, angle, 0, weight, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("둥근모꼴"));

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

//printTextWithAngle 함수와 동일하나 파라미터에 각도가 없음
inline void printText(HDC hdc, int x, int y, int size, int weight, COLORREF textColor, int align, char* text) {
	printTextWithAngle(hdc, x, y, size, weight, 0, textColor, align, text);
}