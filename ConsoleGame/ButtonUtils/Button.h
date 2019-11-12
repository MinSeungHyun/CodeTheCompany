#pragma once
#include "ButtonInterface.h"
#include "ButtonImpl.h"

inline void exampleOnClick(Button* button) {
}

const Button DEFAULT_BUTTON = { 0, 0, NULL, NULL, NULL,
	0, 0, 0, {0, 0}, {0, 0}, _isHovered, _initializeButton, exampleOnClick };
