#pragma once
#include <stdio.h> 
#include <Windows.h>
#include "Utils.h"

int hasInput() {
	INPUT_RECORD input_record;
	DWORD input_count;

	PeekConsoleInput(CONSOLE_INPUT, &input_record, 1, &input_count);
	return input_count;
}

int getInput(COORD* pos) {
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

int isMouseClicked(COORD* position) {
	if (hasInput() && getInput(position)) {
		return 1;
	}
	return 0;
}