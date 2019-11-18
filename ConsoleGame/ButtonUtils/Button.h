#pragma once
#include "ButtonInterface.h"
#include "ButtonImpl.h"

inline void exampleOnHover(Button* button) {
}

inline void exampleOnClick(Button* button) {
}

const Button DEFAULT_BUTTON = { 0, 0, NULL, NULL, NULL,
	0, 0, 0, {0, 0}, {0, 0}, _isHovered, _initializeButton, exampleOnHover, exampleOnClick };

inline Button createButton(int x, int y, char* normal, char* hovered, char* clicked, int indexOfLayer, void (*onClick)(Button*)) {
	Button button = DEFAULT_BUTTON;
	button.x = x;
	button.y = y;
	button.normal = normal;
	button.hovered = hovered;
	button.clicked = clicked;
	button.initialize(&button);
	button.indexOfImageLayer = indexOfLayer;
	button.onClick = onClick;
	return button;
}

inline Button createCollider(int x, int y, char* normal, void(*onHover)(Button*)) {
	Button button = DEFAULT_BUTTON;
	button.x = x;
	button.y = y;
	button.normal = normal;
	button.hovered = NULL;
	button.clicked = NULL;
	button.initialize(&button);
	button.indexOfImageLayer = -1;
	button.onHover = onHover;
	return button;
}