#include "Defines.h"

#define OFFICE_BUTTON_COUNT 2
#define OFFICE_IMAGE_COUNT (OFFICE_BUTTON_COUNT + 1)

void onButtonInOfficeClick(Button* clickedButton) {
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
	Button backButton = createButton(70, 70, FILE_BACK_BUTTON, FILE_BACK_BUTTON_HOVER, FILE_BACK_BUTTON_CLICK, 1, onButtonInOfficeClick);
	Button computerButton = createButton(2340, 1060, FILE_OFFICE_COMPUTER, FILE_OFFICE_COMPUTER_HOVER, FILE_OFFICE_COMPUTER_CLICK, 2, onButtonInOfficeClick);
	Button buttons[OFFICE_BUTTON_COUNT] = { backButton, computerButton };

	Image images[OFFICE_IMAGE_COUNT] = {
		{ FILE_OFFICE_BACKGROUND, 0, 0 },
		{ backButton.normal, backButton.x, backButton.y },
		{ computerButton.normal, computerButton.x, computerButton.y }
	};
	layer.images = images;
	layer.imageCount = OFFICE_IMAGE_COUNT;
	layer.applyToDC = NULL;

	startButtonListener(buttons, OFFICE_BUTTON_COUNT, &layer);
}