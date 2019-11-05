#pragma once
#include <Windows.h>

typedef struct {
	unsigned short* fileName;
	int x, y;
	double scale;
}Image;

typedef struct _ImageLayer {
	//��� ����
	Image* images;
	int imageCount;
	UINT transparentColor;

	HWND _windowHandle;
	HDC _consoleDC;

	//�Լ�
	void (*initialize)(struct _ImageLayer*);
	void (*renderAll)(struct _ImageLayer*);
}ImageLayer;