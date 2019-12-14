#pragma once
#pragma comment (lib, "Msimg32.lib")
#include <Windows.h>
#include "ImageLayer.h"

#ifndef IMAGE_LAYER_IMPL_H
#define IMAGE_LAYER_IMPL_H

#define CONSOLE_WIDTH 180
#define CONSOLE_HEIGHT 48

#define DEFAULT_RESOLUTION_SCALE 16
static double RESOLUTION_MULTIPLIER = 1;
static int WINDOW_WIDTH = 0;
static int WINDOW_HEIGHT = 0;

typedef struct {
	int width, height;
}Size;

//ȭ���� dpi���� ��ȯ
inline int getDPI(HWND hWnd) {
	const HANDLE user32 = GetModuleHandle(TEXT("user32"));
	const FARPROC func = GetProcAddress((HMODULE)user32, "GetDpiForWindow");
	if (func == NULL)
		return 96;
	return ((UINT(__stdcall*)(HWND))func)(hWnd);
}

//��Ʈ���� ũ�⸦ ��ȯ
inline Size getBitmapSize(HBITMAP bitmap) {
	BITMAP tmpBitmap;
	GetObject(bitmap, sizeof(BITMAP), &tmpBitmap);
	const Size bitmapSize = { tmpBitmap.bmWidth, tmpBitmap.bmHeight };
	return bitmapSize;
}

//�������� ��DC�� ��ȯ
inline HDC createNewBackDC(HDC compatibleDC) {
	const HDC backDC = CreateCompatibleDC(compatibleDC);
	const HBITMAP backBitmap = CreateCompatibleBitmap(compatibleDC, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(backDC, backBitmap);
	DeleteObject(backBitmap);
	return backDC;
}

//DC�� �̹����� �־���
inline void putBitmapToBackDC(HDC backDC, Image image, UINT transparentColor) {
	const HDC bitmapDC = CreateCompatibleDC(backDC);
	const HBITMAP bitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)image.fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(bitmapDC, bitmap);

	double scale = image.scale * RESOLUTION_MULTIPLIER;
	if (scale == 0) scale = DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER;

	const int x = (int)(image.x * RESOLUTION_MULTIPLIER);
	const int y = (int)(image.y * RESOLUTION_MULTIPLIER);
	const Size bitmapSize = getBitmapSize(bitmap);
	const int width = (int)(bitmapSize.width * scale);
	const int height = (int)(bitmapSize.height * scale);
	TransparentBlt(backDC, x, y, width, height,
		bitmapDC, 0, 0, bitmapSize.width, bitmapSize.height, transparentColor);

	DeleteObject(bitmap);
	DeleteDC(bitmapDC);
}

//��ǥDC�� �ҽ�DC�� ������
inline void applyToDC(HDC dstDC, HDC srcDC) {
	BitBlt(dstDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		srcDC, 0, 0, SRCCOPY);
}

//�̹��� ���̾ �ʱ�ȭ ����
inline void _initialize(ImageLayer* self) {
	self->_windowHandle = GetConsoleWindow();
	self->_consoleDC = GetDC(self->_windowHandle);

	const int dpi = getDPI(self->_windowHandle);
	RESOLUTION_MULTIPLIER = dpi / 192.0;
	WINDOW_WIDTH = (int)(CONSOLE_WIDTH * DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER);
	WINDOW_HEIGHT = (int)(CONSOLE_HEIGHT * 2 * DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER);
}

//��� �̹������� �� DC�� ��ȯ
inline HDC getRenderedBackDC(ImageLayer* self) {
	const HDC backDC = createNewBackDC(self->_consoleDC);

	for (int i = 0; i < self->imageCount; i++) {
		if (!self->images[i].isHide)
			putBitmapToBackDC(backDC, self->images[i], self->transparentColor);
	}
	return backDC;
}

//ȭ�鿡 �̹��� ���̾ �������
inline void _renderAll(ImageLayer* self) {
	const HDC backDC = getRenderedBackDC(self);
	if (self->applyToDC != NULL) self->applyToDC(backDC);
	applyToDC(self->_consoleDC, backDC);
	DeleteDC(backDC);
}

#endif