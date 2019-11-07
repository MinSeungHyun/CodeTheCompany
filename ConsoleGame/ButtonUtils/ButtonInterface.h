#pragma once
#include <Windows.h>

typedef struct _Button {
	int x, y;
	unsigned short* normal, * hovered, * clicked;
	int _width, _height;
	COORD _start, _end;

	int (*isHovered)(struct _Button*, COORD);
	void (*initialize)(struct _Button*);
}Button;