#pragma once
#include <Windows.h>

typedef struct {
	unsigned short* fileName;
	int x, y;
}Image;

typedef struct _ImageLayer {
	//��� ����
	Image* images;
	int imageCount;

	HWND _windowHandle;
	HDC _consoleDC;

	//�Լ�
	void (*initialize)(struct _ImageLayer*);
	void (*renderAll)(struct _ImageLayer*);
}ImageLayer;