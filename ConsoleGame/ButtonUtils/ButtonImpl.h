#pragma once
#include <Windows.h>
#include "Button.h"

inline void getButtonSize(unsigned short* fileName, int* width, int* height) {
	const HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, (LPCWSTR)fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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