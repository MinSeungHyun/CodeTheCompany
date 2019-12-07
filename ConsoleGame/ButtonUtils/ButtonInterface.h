#pragma once
#include <Windows.h>

#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H

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

#endif