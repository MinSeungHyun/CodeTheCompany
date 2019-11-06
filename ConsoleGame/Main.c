#include "Initializer.h"
#include "resources.h"
#include "ImageUtils/ImageLayer.h"
#include "ButtonUtils/Button.h"

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;
ImageLayer layer;

void initLayer();
Button createButton(int, int, wchar_t*, wchar_t*, wchar_t*);
void beginStartScreen();

int main() {
	initialize();
	initLayer();
	Sleep(300);

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

	while (1) {
		isMouseClicked();
		if (startButton.isHovered(&startButton)) {
			if (isMouseClicked()) {
				layer.images[2].fileName = startButton.clicked;
				Sleep(100);
				layer.fadeOut(&layer);
				break;
			}
			layer.images[2].fileName = startButton.hovered;
		}
		else layer.images[2].fileName = startButton.normal;

		layer.renderAll(&layer);
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