#pragma once
#include <Windows.h>

typedef struct _Button {
	int x, y;
	char* normal, * hovered, * clicked;
	int _width, _height, indexOfImageLayer;
	COORD _start, _end;

	int (*isHovered)(struct _Button*, COORD);
	void (*initialize)(struct _Button*);
	void (*onHover)(struct _Button*);
	void (*onClick)(struct _Button*);
}Button;