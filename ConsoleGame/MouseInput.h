#pragma once
#include <stdio.h> 
#include <Windows.h>
#include "Utils.h"

inline int hasInput() {
	INPUT_RECORD input_record;
	DWORD input_count;

	PeekConsoleInput(CONSOLE_INPUT, &input_record, 1, &input_count);
	return input_count;
}

inline int getInput(COORD* pos) {
	INPUT_RECORD input_record;
	DWORD input_count;

	ReadConsoleInput(CONSOLE_INPUT, &input_record, 1, &input_count);
	if (input_record.EventType == MOUSE_EVENT &&
		input_record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(CONSOLE_OUTPUT, &csbi);

		*pos = input_record.Event.MouseEvent.dwMousePosition;
		pos->X -= csbi.srWindow.Left;
		pos->Y -= csbi.srWindow.Top;

		return MOUSE_EVENT;
	}
	return 0;
}

inline int isMouseClicked(COORD* position) {
	if (hasInput() && getInput(position)) {
		return 1;
	}
	return 0;
}

inline COORD getMousePosition() {
	POINT cursorPosition;
	GetCursorPos(&cursorPosition);
	ScreenToClient(WINDOW_HANDLE, &cursorPosition);
	return Coord(cursorPosition.x * 2, cursorPosition.y);
}