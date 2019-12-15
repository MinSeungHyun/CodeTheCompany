#pragma once
#include <Windows.h>
#include <process.h>
#include "Button.h"
#include "../ImageUtils/ImageLayer.h"
#include "../MouseInput.h"

#ifndef BUTTON_IMPL_H
#define BUTTON_IMPL_H

//버튼의 크기를 받아줌
inline void getButtonSize(char* fileName, int* width, int* height) {
	const HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bitmap;
	GetObject(hbitmap, sizeof(BITMAP), &bitmap);
	*width = bitmap.bmWidth;
	*height = bitmap.bmHeight;
}

//버튼위에 마우스가 있는 상태인지 반환
inline int _isHovered(Button* self, COORD mousePosition) {
	const int startX = self->_start.X, startY = self->_start.Y;
	const int endX = self->_end.X, endY = self->_end.Y;

	if (mousePosition.X >= startX && mousePosition.X <= endX
		&& mousePosition.Y >= startY && mousePosition.Y <= endY) {
		return 1;
	}
	else {
		return 0;
	}

}

//버튼을 초기화 해줌
inline void _initializeButton(Button* self) {
	getButtonSize(self->normal, &self->_width, &self->_height);
	self->_start.X = self->x;
	self->_start.Y = self->y;
	self->_end.X = self->x + self->_width * 16;
	self->_end.Y = self->y + self->_height * 16;
}

//버튼중에서 hover상태인 버튼의 인덱스를 반환해준다
inline int getHoveredButtonIndex(Button* buttons, int buttonCount) {
	COORD mousePosition = (COORD) { 0,0 };
	for (int i = 0; i < buttonCount; i++) {
		mousePosition = getMousePosition();
		if (buttons[i].isHovered(&buttons[i], mousePosition)) {
			return i;
		}
	}
	return -1;
}

//Must be declared in .c file
extern int isMouseDown;
extern int isMouseUp;
extern int isListening;

//마우스가 클릭된 상태일 때 호출되어 값을 업데이트 해줌
inline void onMouseDown() {
	isMouseDown = 1;
}

//마우스가 클릭 되었다가 때었을 때 호출되어 값을 업데이트 해줌
inline void onMouseUp() {
	isMouseDown = 0;
	isMouseUp = 1;
}

//쓰레드에서 마우스의 클릭 상태를 계속 확인하는 함수이다
inline void checkMouseStateThread(void* param) {
	while (isListening) {
		if (hasInput() && isMouseClicked()) {
			onMouseDown();
			while (isMouseClicked());
			onMouseUp();
		}
	}
}

//버튼들의 상태에 따라 알맞은 동작을 하도록 반복시켜주는 함수이다
inline void startButtonListener(Button* buttons, int buttonCount, ImageLayer* layer) {
	if (isListening) return;
	isListening = 1;

	_beginthread(checkMouseStateThread, 0, NULL);

	while (isListening) {
		int isMouseUpListened = 0;
		if (isMouseUp) {
			isMouseUp = 0;
			isMouseUpListened = 1;
		}

		const int hoveredButtonIndex = getHoveredButtonIndex(buttons, buttonCount);
		for (int i = 0; i < buttonCount; i++) {
			const int indexOfLayer = buttons[i].indexOfImageLayer;
			if (indexOfLayer == -1) continue;
			layer->images[buttons[i].indexOfImageLayer].fileName = buttons[i].normal;
		}
		if (hoveredButtonIndex == -1) {
			layer->renderAll(layer);
			continue;
		}
		const int indexOfLayer = buttons[hoveredButtonIndex].indexOfImageLayer;

		if (indexOfLayer != -1) {
			if (isMouseDown) layer->images[indexOfLayer].fileName = buttons[hoveredButtonIndex].clicked;
			else layer->images[indexOfLayer].fileName = buttons[hoveredButtonIndex].hovered;
		}

		layer->renderAll(layer);
		buttons[hoveredButtonIndex].onHover(&buttons[hoveredButtonIndex]);

		if (isMouseUpListened) {
			isMouseUpListened = 0;
			buttons[hoveredButtonIndex].onClick(&buttons[hoveredButtonIndex]);
		}
	}
}

//startButtonListener에서 실행한 쓰레드와 반복문을 종료한다.
inline void stopButtonListener() {
	isListening = 0;
}

#endif