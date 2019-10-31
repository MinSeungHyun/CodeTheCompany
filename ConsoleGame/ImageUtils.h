#include <Windows.h>

typedef struct {
	int width, height;
}IMAGE_SIZE;

typedef struct {
	int x, y;
}OFFSET;

HWND getConsoleWindowHandle() {
	WCHAR title[2048] = { 0 };
	GetConsoleTitle(title, 2048);
	HWND hWnd = FindWindow(NULL, title);
	SetConsoleTitle(title);
	return hWnd;
}

int GetDPI(HWND hWnd) {
	HMODULE user32 = GetModuleHandle(TEXT("user32"));
	FARPROC func = GetProcAddress(user32, "GetDpiForWindow");
	if (func == NULL)
		return 96;
	return ((UINT(__stdcall*)(HWND))func)(hWnd);
}

void GetBMP(HDC hdc, HDC memdc, HBITMAP image) {
	BITMAP bitmap;
	HDC bitmapDC = CreateCompatibleDC(hdc);

	GetObject(image, sizeof(bitmap), &bitmap);
	SelectObject(bitmapDC, image);
	BitBlt(memdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapDC, 0, 0, SRCCOPY);

	DeleteDC(bitmapDC);
}

void paintImage(IMAGE_SIZE size, OFFSET offset, char* fileName) {
	int dpi;
	HBITMAP image;
	HWND hWnd = getConsoleWindowHandle();

	dpi = GetDPI(hWnd);

	image = (HBITMAP)LoadImage(NULL, (LPCWSTR)fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	int width = size.width;
	int height = size.height;
	int xOffset = offset.x * -1;
	int yOffset = offset.y * -1;

	HDC hdc = GetDC(hWnd);
	HDC memdc = CreateCompatibleDC(hdc);

	HBITMAP bitmap = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(memdc, bitmap);

	GetBMP(hdc, memdc, image);

	StretchBlt(hdc, 0, 0, width * 16, height * 16, memdc, xOffset, yOffset, width, height, SRCCOPY);

	DeleteDC(memdc);
	DeleteObject(bitmap);
	ReleaseDC(hWnd, hdc);
}

IMAGE_SIZE Size(int width, int height) {
	IMAGE_SIZE size = { width, height };
	return size;
}

OFFSET Offset(int x, int y) {
	OFFSET offset = { x, y };
	return offset;
}