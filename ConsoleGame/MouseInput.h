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

INPUT_RECORD rec;
DWORD dwNOER;
inline int isMouseClicked() {
	ReadConsoleInput(CONSOLE_INPUT, &rec, 1, &dwNOER);
	if (rec.EventType == MOUSE_EVENT) {
		const DWORD buttonState = rec.Event.MouseEvent.dwButtonState;
		if (buttonState & FROM_LEFT_1ST_BUTTON_PRESSED)	return 1;
		else if (buttonState & RIGHTMOST_BUTTON_PRESSED) return 2;
	}
	return 0;
}

inline COORD getMousePosition() {
	POINT cursorPosition;
	GetCursorPos(&cursorPosition);
	ScreenToClient(WINDOW_HANDLE, &cursorPosition);
	return (COORD) { (SHORT)cursorPosition.x * 2, (SHORT)cursorPosition.y * 2 };
}