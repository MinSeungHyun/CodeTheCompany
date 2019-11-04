#include "Initializer.h"
#include "MouseInput.h"
#include "ImageUtils/ImageLayer.h"
#include "ButtonUtils/Button.h"

ImageLayer layer;
Image images[10];
int MOUSE_STATE = 0;

void mainProcess() {
	Button button = DEFAULT_BUTTON;
	button.x = 200;
	button.y = 100;
	button.normal = L"button.bmp";
	button.hovered = L"button_hovered.bmp";
	button.clicked = L"button_clicked.bmp";

	button.initialize(&button);

	layer = DEFAULT_IMAGE_LAYER;
	layer.initialize(&layer);
	layer.imageCount = 1;
	images[0] = (Image){ button.normal, button.x, button.y };
	images[1] = (Image){ L"title.bmp", 300, 200 };
	layer.images = images;
	layer.renderAll(&layer);

	while (1) {
		if (button.isHovered(&button)) {
			if (isMouseClicked()) {
				layer.images[0].fileName = button.clicked;
				layer.imageCount = 2;
			}
			else {
				layer.images[0].fileName = button.hovered;
				layer.imageCount = 1;
			}
		}
		else {
			layer.images[0].fileName = button.normal;
			layer.imageCount = 1;
		}
		layer.renderAll(&layer);
	}
}

int main() {
	initialize();
	Sleep(300);

	mainProcess();

	getchar();
}