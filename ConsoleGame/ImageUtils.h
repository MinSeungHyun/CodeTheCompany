#pragma once
#include <Windows.h>
#include "Initializer.h"
#define RESOLUTION_SCALE 16

inline HWND getConsoleWindowHandle() {
	WCHAR title[2048] = { 0 };
	GetConsoleTitle(title, 2048);
	const HWND hWnd = FindWindow(NULL, title);
	SetConsoleTitle(title);
	return hWnd;
}

inline int getDPI(HWND hWnd) {
	const HMODULE user32 = GetModuleHandle(TEXT("user32"));
	const FARPROC func = GetProcAddress(user32, "GetDpiForWindow");
	if (func == NULL)
		return 96;
	return ((UINT(__stdcall*)(HWND))func)(hWnd);
}

inline void getBMP(HDC hdc, HDC memdc, HBITMAP image) {
	BITMAP bitmap;
	const HDC bitmapDC = CreateCompatibleDC(hdc);

	GetObject(image, sizeof(bitmap), &bitmap);
	SelectObject(bitmapDC, image);
	BitBlt(memdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapDC, 0, 0, SRCCOPY);

	DeleteDC(bitmapDC);
}

inline void paintImage(int width, int height, int xOffset, int yOffset, wchar_t* fileName) {
	const HWND hWnd = getConsoleWindowHandle();
	int dpi = getDPI(hWnd);
	const HBITMAP image = (HBITMAP)LoadImage(NULL, (LPCWSTR)fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	xOffset *= -1;
	yOffset *= -1;

	const HDC hdc = GetDC(hWnd);
	const HDC memdc = CreateCompatibleDC(hdc);

	const HBITMAP bitmap = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(memdc, bitmap);

	getBMP(hdc, memdc, image);

	StretchBlt(hdc, 0, 0, CONSOLE_WIDTH * RESOLUTION_SCALE, CONSOLE_HEIGHT * RESOLUTION_SCALE,
		memdc, xOffset, yOffset, CONSOLE_WIDTH, CONSOLE_HEIGHT, SRCCOPY);

	DeleteDC(memdc);
	DeleteObject(bitmap);
	ReleaseDC(hWnd, hdc);
}