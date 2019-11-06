#pragma once
#pragma comment (lib, "Msimg32.lib")
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
	return bitmapSize;
}

inline HDC createNewBackDC(HDC compatibleDC) {
	const HDC backDC = CreateCompatibleDC(compatibleDC);
	const HBITMAP backBitmap = CreateCompatibleBitmap(compatibleDC, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(backDC, backBitmap);
	DeleteObject(backBitmap);
	return backDC;
}

inline void putBitmapToBackDC(HDC backDC, Image image, UINT transparentColor) {
	const HDC bitmapDC = CreateCompatibleDC(backDC);
	const HBITMAP bitmap = (HBITMAP)LoadImage(NULL, (LPCWSTR)image.fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(bitmapDC, bitmap);

	double scale = image.scale;
	if (scale == 0) scale = 16;

	const Size bitmapSize = getBitmapSize(bitmap);
	TransparentBlt(backDC, image.x, image.y, bitmapSize.width * scale, bitmapSize.height * scale,
		bitmapDC, 0, 0, bitmapSize.width, bitmapSize.height, transparentColor);

	DeleteObject(bitmap);
	DeleteDC(bitmapDC);
}

inline void applyToConsoleDC(HDC consoleDC, HDC srcDC) {
	BitBlt(consoleDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		srcDC, 0, 0, SRCCOPY);
}

inline void _initialize(ImageLayer* self) {
	self->_windowHandle = GetConsoleWindow();
	self->_consoleDC = GetDC(self->_windowHandle);
}

inline HDC getRenderedBackDC(ImageLayer* self) {
	const HDC backDC = createNewBackDC(self->_consoleDC);

	for (int i = 0; i < self->imageCount; i++) {
		putBitmapToBackDC(backDC, self->images[i], self->transparentColor);
	}
	return backDC;
}

inline void _renderAll(ImageLayer* self) {
	const HDC backDC = getRenderedBackDC(self);
	applyToConsoleDC(self->_consoleDC, backDC);
	DeleteDC(backDC);
}

inline BLENDFUNCTION getBlendFunction() {
	BLENDFUNCTION bf;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = 0;
	return bf;
}

inline void _renderAndFadeIn(ImageLayer* self) {
	const HDC consoleDC = self->_consoleDC;
	const HDC backDC = getRenderedBackDC(self);

	const HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(consoleDC, blackBrush);

	BLENDFUNCTION bf = getBlendFunction();
	bf.SourceConstantAlpha = 12;

	Rectangle(consoleDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	for (int i = 0; i < 20; i++) {
		AlphaBlend(consoleDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			backDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, bf);
	}
	applyToConsoleDC(consoleDC, backDC);
	DeleteObject(blackBrush);
	DeleteDC(backDC);
}

inline void _renderAndFadeOut(ImageLayer* self) {
	const HDC consoleDC = self->_consoleDC;
	const HDC backDC = getRenderedBackDC(self);
	applyToConsoleDC(consoleDC, backDC);

	const HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(consoleDC, blackBrush);

	BLENDFUNCTION bf = getBlendFunction();

	for (int i = 255; i > 0; i -= 20) {
		Rectangle(consoleDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		bf.SourceConstantAlpha = i;
		AlphaBlend(consoleDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			backDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, bf);
		Sleep(100);
	}
	Rectangle(consoleDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	DeleteObject(blackBrush);
	DeleteDC(backDC);
}