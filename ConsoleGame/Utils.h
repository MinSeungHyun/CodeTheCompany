#pragma once
#include <Windows.h>
#include <time.h>
#include <process.h>

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;

inline void gotoxy(COORD position) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

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

inline char* rtrim(char* str) {
	const char* seps = "\t\n\v\f\r ";
	int i = strlen(str) - 1;
	while (i >= 0 && strchr(seps, str[i]) != NULL) {
		str[i] = '\0';
		i--;
	}
	return str;
}

inline char* trim(char* str) {
	return ltrim(rtrim(str));
}

inline int isFileExist(char* fileName) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) return 0;
	fclose(file);
	return 1;
}

inline void makeFileIfNotExist(char* fileName) {
	if (isFileExist(fileName)) return;
	fclose(fopen(fileName, "w"));
}

inline struct tm* getCurrentTime() {
	time_t rawTime;
	time(&rawTime);
	struct tm* timeInfo = localtime(&rawTime);
	return timeInfo;
}

inline int getCurrentSecond() {
	return getCurrentTime()->tm_sec;
}

inline void timerThread(void* param) {
	const _beginthread_proc_type onAlarm = (_beginthread_proc_type)param;
	int second = 0, cnt = 0;
	int previousSecond = -1;
	while (1) {
		second = getCurrentSecond();
		if (second != previousSecond)
			_beginthread(onAlarm, 0, (void*)cnt++);
		previousSecond = second;
	}
}

inline void startSecondClock(_beginthread_proc_type callback) {
	_beginthread(timerThread, 0, callback);
}