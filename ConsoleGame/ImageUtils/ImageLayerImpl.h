#pragma once
#include <Windows.h>
#include "ImageLayer.h"

#define CONSOLE_WIDTH 180
#define CONSOLE_HEIGHT 48

#define RESOLUTION_SCALE 16
#define WINDOW_WIDTH (CONSOLE_WIDTH * RESOLUTION_SCALE)
#define WINDOW_HEIGHT (CONSOLE_HEIGHT * RESOLUTION_SCALE*2)

typedef struct {
	int width, height;
}Size;

inline Size getBitmapSize(HBITMAP bitmap) {
	BITMAP tmpBitmap;
	GetObject(bitmap, sizeof(BITMAP), &tmpBitmap);
	const Size bitmapSize = { tmpBitmap.bmWidth, tmpBitmap.bmHeight };
	//free(&tmpBitmap);
	return bitmapSize;
}

inline HDC createNewBackDC(HDC compatibleDC) {
	const HDC backDC = CreateCompatibleDC(compatibleDC);
	const HBITMAP backBitmap = CreateCompatibleBitmap(compatibleDC, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(backDC, backBitmap);
	DeleteObject(backBitmap);
	return backDC;
}

inline void putBitmapToBackDC(HDC backDC, Image image) {
	const HDC bitmapDC = CreateCompatibleDC(backDC);
	const HBITMAP bitmap = (HBITMAP)LoadImage(NULL, (LPCWSTR)image.fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(bitmapDC, bitmap);

	const Size bitmapSize = getBitmapSize(bitmap);
	StretchBlt(backDC, image.x, image.y, bitmapSize.width * RESOLUTION_SCALE, bitmapSize.height * RESOLUTION_SCALE,
		bitmapDC, 0, 0, bitmapSize.width, bitmapSize.height, SRCCOPY);
	
	DeleteObject(bitmap);
	DeleteDC(bitmapDC);
}

inline void applyToConsoleDC(HDC consoleDC, HDC srcDC) {
	BitBlt(consoleDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, srcDC, 0, 0, SRCCOPY);
}

inline void _initialize(ImageLayer* self) {
	self->_windowHandle = GetConsoleWindow();
	self->_consoleDC = GetDC(self->_windowHandle);
}

inline void _renderAll(ImageLayer* self) {
	const HDC backDC = createNewBackDC(self->_consoleDC);

	for (int i = 0; i < self->imageCount; i++) {
		putBitmapToBackDC(backDC, self->images[i]);
	}

	applyToConsoleDC(self->_consoleDC, backDC);
	DeleteDC(backDC);
}