#pragma once
#include <Windows.h>
#include <process.h>
#include "Button.h"

inline void getButtonSize(char* fileName, int* width, int* height) {
	const HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bitmap;
	GetObject(hbitmap, sizeof(BITMAP), &bitmap);
	*width = bitmap.bmWidth;
	*height = bitmap.bmHeight;
}

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

inline void _initializeButton(Button* self) {
	getButtonSize(self->normal, &self->_width, &self->_height);
	self->_start.X = self->x;
	self->_start.Y = self->y;
	self->_end.X = self->x + self->_width * 16;
	self->_end.Y = self->y + self->_height * 16;
}

inline int getHoveredButtonIndex(Button* buttons, int buttonCount) {
	COORD mousePosition = { 0,0 };
	for (int i = 0; i < buttonCount; i++) {
		mousePosition = getMousePosition();
		if (buttons[i].isHovered(&buttons[i], mousePosition)) {
			return i;
		}
	}
	return -1;
}

int isMouseDown = 0;
int isMouseUp = 0;
int isListening = 0;

inline void onMouseDown() {
	isMouseDown = 1;
}

inline void onMouseUp() {
	isMouseDown = 0;
	isMouseUp = 1;
}

inline void checkMouseStateThread() {
	while (isListening) {
		if (hasInput() && isMouseClicked()) {
			onMouseDown();
			while (isMouseClicked());
			onMouseUp();
		}
	}
}

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
		if (hoveredButtonIndex == -1) {
			for (int i = 0; i < buttonCount; i++)
				layer->images[buttons[i].indexOfImageLayer].fileName = buttons[i].normal;
			layer->renderAll(layer);
			continue;
		}
		const int indexOfLayer = buttons[hoveredButtonIndex].indexOfImageLayer;

		if (isMouseDown)
			layer->images[indexOfLayer].fileName = buttons[hoveredButtonIndex].clicked;
		else
			layer->images[indexOfLayer].fileName = buttons[hoveredButtonIndex].hovered;

		layer->renderAll(layer);

		if (isMouseUpListened) {
			isMouseUpListened = 0;
			buttons[hoveredButtonIndex].onClick(&buttons[hoveredButtonIndex]);
		}
	}
}

inline void stopButtonListener() {
	isListening = 0;
}