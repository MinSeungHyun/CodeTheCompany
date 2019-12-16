#include "Defines.h"

#define BUTTON_COUNT 2
#define IMAGE_COUNT (BUTTON_COUNT + 1)

void onButtonClick(Button* clickedButton) {
	playSound(SOUND_BUTTON_CLICK);
	char* clickedButtonName = clickedButton->normal;
	if (clickedButtonName == FILE_BACK_BUTTON) {
		beginMapScreen(0);
	}
	else if (clickedButtonName == FILE_OFFICE_COMPUTER) {

	}
}

void beginOfficeScreen() {
	stopButtonListener();
	Button backButton = createButton(70, 70, FILE_BACK_BUTTON, FILE_BACK_BUTTON_HOVER, FILE_BACK_BUTTON_CLICK, 1, onButtonClick);
	Button computerButton = createButton(2340, 1060, FILE_OFFICE_COMPUTER, FILE_OFFICE_COMPUTER_HOVER, FILE_OFFICE_COMPUTER_CLICK, 2, onButtonClick);
	Button buttons[BUTTON_COUNT] = { backButton, computerButton };

	Image images[IMAGE_COUNT] = {
		{ FILE_OFFICE_BACKGROUND, 0, 0 },
		{ backButton.normal, backButton.x, backButton.y },
		{ computerButton.normal, computerButton.x, computerButton.y }
	};
	layer.images = images;
	layer.imageCount = IMAGE_COUNT;
	layer.applyToDC = NULL;

	startButtonListener(buttons, BUTTON_COUNT, &layer);
}