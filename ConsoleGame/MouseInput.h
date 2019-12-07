#pragma once
#include <stdio.h> 
#include <Windows.h>
#include "Utils.h"
#include "ImageUtils/ImageLayer.h"

#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H

//콘솔에서 어떤 입력이든 있는지 확인함
inline int hasInput() {
	INPUT_RECORD input_record;
	DWORD input_count;

	PeekConsoleInput(CONSOLE_INPUT, &input_record, 1, &input_count);
	return input_count;
}

static INPUT_RECORD rec;
static DWORD dwNOER;
//마우스가 클릭되었는지 확인함
inline int isMouseClicked() {
	ReadConsoleInput(CONSOLE_INPUT, &rec, 1, &dwNOER);
	if (rec.EventType == MOUSE_EVENT) {
		const DWORD buttonState = rec.Event.MouseEvent.dwButtonState;
		if (buttonState & FROM_LEFT_1ST_BUTTON_PRESSED)	return 1;
		else if (buttonState & RIGHTMOST_BUTTON_PRESSED) return 2;
	}
	return 0;
}

//현재 마우스 커서의 위치를 반환
inline COORD getMousePosition() {
	POINT cursorPosition;
	GetCursorPos(&cursorPosition);
	ScreenToClient(WINDOW_HANDLE, &cursorPosition);
	return (COORD) { (SHORT)cursorPosition.x * 2, (SHORT)cursorPosition.y * 2 };
}

//이미지의 적절한 위치를 쉽게 알기 위하여 만든 함수
inline void imagePositionTester(ImageLayer* layer, int testingIndex) {
	while (1) {
		if (isMouseClicked()) {
			const COORD position = getMousePosition();
			layer->images[testingIndex].x = position.X;
			layer->images[testingIndex].y = position.Y;
			layer->renderAll(layer);

			gotoxy((COORD) { 0, 0 });
			printf("%5d %5d", position.X, position.Y);
		}
	}
}

#endif