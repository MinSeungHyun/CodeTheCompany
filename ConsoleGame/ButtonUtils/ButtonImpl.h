#pragma once
#include <Windows.h>
#include <process.h>
#include "Button.h"
#include "../ImageUtils/ImageLayer.h"
#include "../MouseInput.h"

#ifndef BUTTON_IMPL_H
#define BUTTON_IMPL_H

//��ư�� ũ�⸦ �޾���
inline void getButtonSize(char* fileName, int* width, int* height) {
	const HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bitmap;
	GetObject(hbitmap, sizeof(BITMAP), &bitmap);
	*width = bitmap.bmWidth;
	*height = bitmap.bmHeight;
}

//��ư���� ���콺�� �ִ� �������� ��ȯ
inline int _isHovered(Button* self, COORD mousePosition) {
	const int startX = self->_start.X, startY = self->_start.Y;
	const int endX = self->_end.X, endY = self->_end.Y;

	if (mousePosition.X >= startX && mousePosition.X <= endX
		&& mousePosition.Y >= startY && mousePosition.Y <= endY) {
		return 1;
	}
	else {
		return 0;
	}

}

//��ư�� �ʱ�ȭ ����
inline void _initializeButton(Button* self) {
	getButtonSize(self->normal, &self->_width, &self->_height);
	self->_start.X = self->x;
	self->_start.Y = self->y;
	self->_end.X = self->x + self->_width * 16;
	self->_end.Y = self->y + self->_height * 16;
}

//��ư�߿��� hover������ ��ư�� �ε����� ��ȯ���ش�
inline int getHoveredButtonIndex(Button* buttons, int buttonCount) {
	COORD mousePosition = (COORD) { 0,0 };
	for (int i = 0; i < buttonCount; i++) {
		mousePosition = getMousePosition();
		if (buttons[i].isHovered(&buttons[i], mousePosition)) {
			return i;
		}
	}
	return -1;
}

//Must be declared in .c file
extern int isMouseDown;
extern int isMouseUp;
extern int isListening;

//���콺�� Ŭ���� ������ �� ȣ��Ǿ� ���� ������Ʈ ����
inline void onMouseDown() {
	isMouseDown = 1;
}

//���콺�� Ŭ�� �Ǿ��ٰ� ������ �� ȣ��Ǿ� ���� ������Ʈ ����
inline void onMouseUp() {
	isMouseDown = 0;
	isMouseUp = 1;
}

//�����忡�� ���콺�� Ŭ�� ���¸� ��� Ȯ���ϴ� �Լ��̴�
inline void checkMouseStateThread(void* param) {
	while (isListening) {
		if (hasInput() && isMouseClicked()) {
			onMouseDown();
			while (isMouseClicked());
			onMouseUp();
		}
	}
}

//��ư���� ���¿� ���� �˸��� ������ �ϵ��� �ݺ������ִ� �Լ��̴�
inline void startButtonListener(Button* buttons, int buttonCount, ImageLayer* layer) {
	if (isListening) return;
	isListening = 1;

	_beginthread(checkMouseStateThread, 0, NULL);

	while (isListening) {
		int isMouseUpListened = 0;
		if (isMouseUp) {
			isMouseUp = 0;
			isMouseUpListened = 1;
		}

		const int hoveredButtonIndex = getHoveredButtonIndex(buttons, buttonCount);
		for (int i = 0; i < buttonCount; i++) {
			const int indexOfLayer = buttons[i].indexOfImageLayer;
			if (indexOfLayer == -1) continue;
			layer->images[buttons[i].indexOfImageLayer].fileName = buttons[i].normal;
		}
		if (hoveredButtonIndex == -1) {
			layer->renderAll(layer);
			continue;
		}
		const int indexOfLayer = buttons[hoveredButtonIndex].indexOfImageLayer;

		if (indexOfLayer != -1) {
			if (isMouseDown) layer->images[indexOfLayer].fileName = buttons[hoveredButtonIndex].clicked;
			else layer->images[indexOfLayer].fileName = buttons[hoveredButtonIndex].hovered;
		}

		layer->renderAll(layer);
		buttons[hoveredButtonIndex].onHover(&buttons[hoveredButtonIndex]);

		if (isMouseUpListened) {
			isMouseUpListened = 0;
			buttons[hoveredButtonIndex].onClick(&buttons[hoveredButtonIndex]);
		}
	}
}

//startButtonListener���� ������ ������� �ݺ����� �����Ѵ�.
inline void stopButtonListener() {
	isListening = 0;
}

#endif