#include "Initializer.h"
#include "resources.h"
#include "process.h"
#include "MouseInput.h"
#include "ImageUtils/ImageLayer.h"
#include "ButtonUtils/Button.h"

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;
ImageLayer layer;

void initLayer();
Button createButton(int, int, wchar_t*, wchar_t*, wchar_t*);
void onMouseDown();
void onMouseUp();
void checkMouseStateThread();
void beginStartScreen();

int isMouseDown = 0;
int isMouseUp = 0;

int main() {
	initialize();
	initLayer();
	Sleep(300);

	_beginthread(checkMouseStateThread, 0, NULL);

	beginStartScreen();
}

void beginStartScreen() {
	Button startButton = createButton(1114, 1150, FILE_START_BUTTON, FILE_START_BUTTON_HOVER, FILE_START_BUTTON_CLICK);

	Image titleImages[3] = {
		{FILE_TITLE, 0, 0},
		{FILE_TITLE_TEXT, 638, 134},
		{startButton.normal, startButton.x, startButton.y}
	};
	layer.images = titleImages;
	layer.imageCount = 3;
	layer.renderAll(&layer);

	COORD mousePosition = { 0, 0 };
	int isStartButtonHovered = 0;
	while (1) {
		mousePosition = getMousePosition();
		isStartButtonHovered = startButton.isHovered(&startButton, mousePosition);

		if (isStartButtonHovered) {
			if (isMouseDown) {
				layer.images[2].fileName = startButton.clicked;
			}
			else {
				layer.images[2].fileName = startButton.hovered;
			}
		}
		else
			layer.images[2].fileName = startButton.normal;

		if (isMouseUp) {
			isMouseUp = 0;
			if (isStartButtonHovered) {
				layer.fadeOut(&layer);
				break;
			}
		}

		layer.renderAll(&layer);
	}
}

void onMouseDown() {
	isMouseDown = 1;
}

void onMouseUp() {
	isMouseDown = 0;
	isMouseUp = 1;
}

void checkMouseStateThread() {
	while (1) {
		if (hasInput() && isMouseClicked()) {
			onMouseDown();
			while (isMouseClicked());
			onMouseUp();
		}
	}
}

Button createButton(int x, int y, wchar_t* normal, wchar_t* hovered, wchar_t* clicked) {
	Button button = DEFAULT_BUTTON;
	button.x = x;
	button.y = y;
	button.normal = normal;
	button.hovered = hovered;
	button.clicked = clicked;
	button.initialize(&button);
	return button;
}

void initLayer() {
	layer = DEFAULT_IMAGE_LAYER;
	layer.initialize(&layer);
	layer.transparentColor = RGB(0, 255, 25);
}