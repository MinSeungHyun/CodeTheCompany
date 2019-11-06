#include "Initializer.h"
#include "ImageUtils/ImageLayer.h"
#include "resources.h"

int main() {
	initialize();
	Sleep(500);

	ImageLayer layer = DEFAULT_IMAGE_LAYER;
	layer.initialize(&layer);

	Image images[2] = {
		{FILE_STORY_1, 0, 0},
		{FILE_STORY_2, 100, 200, 2}
	};
	layer.images = images;
	layer.imageCount = 2;
	layer.transparentColor = RGB(0, 255, 25);

	layer.renderAll(&layer);

	layer.fadeIn()

	getchar();
}