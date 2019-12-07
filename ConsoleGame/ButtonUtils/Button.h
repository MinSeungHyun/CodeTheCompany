#pragma once
#include "ButtonInterface.h"
#include "ButtonImpl.h"

#ifndef BUTTON_H
#define BUTTON_H

//��ư�� onHover�Լ� �����Ϳ� ���� �⺻���̴�
inline void exampleOnHover(Button* button) {
}

//��ư�� onClick�Լ� �����Ϳ� ���� �⺻���̴�
inline void exampleOnClick(Button* button) {
}

static const Button DEFAULT_BUTTON = { 0, 0, NULL, NULL, NULL,
	0, 0, 0, {0, 0}, {0, 0}, _isHovered, _initializeButton, exampleOnHover, exampleOnClick };

//��ư�� ������ִ� �Լ�
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

//�浹 ������ �ϴ� ��ư�� ������ִ� �Լ�
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

#endif