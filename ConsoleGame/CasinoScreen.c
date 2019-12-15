#include "Defines.h"

#define CASINO_BUTTON_COUNT 3
#define CASINO_IMAGE_COUNT (CASINO_BUTTON_COUNT + 2)

void applyToDcInCasino(HDC hdc) {
	printText(hdc, 1990, 75, 70, 0, RGB(255, 255, 255), TA_LEFT, commify(money));
	printText(hdc, 2680, 85, 50, 0, RGB(255, 255, 255), TA_RIGHT, "¿ø");
}

void onButtonInCasinoClick(Button* clickedButton) {
	char* buttonName = clickedButton->normal;
	if (buttonName == FILE_BACK_BUTTON) {
		beginMapScreen(0);
	}
	else if (buttonName == FILE_CASINO_JACKPOT_BUTTON) {
		beginJackpotScreen();
	}
	else if (buttonName == FILE_CASINO_TRICKERY_BUTTON) {

	}
}

void beginCasinoScreen() {
	stopButtonListener();
	updateUserValues();

	Button backButton = createButton(100, 50, FILE_BACK_BUTTON, FILE_BACK_BUTTON_HOVER, FILE_BACK_BUTTON_CLICK, 2, onButtonInCasinoClick);
	Button jackpotButton = createButton(400, 140, FILE_CASINO_JACKPOT_BUTTON, FILE_CASINO_JACKPOT_BUTTON_HOVER, FILE_CASINO_JACKPOT_BUTTON_CLICK, 3, onButtonInCasinoClick);
	Button trickeryButton = createButton(1500, 590, FILE_CASINO_TRICKERY_BUTTON, FILE_CASINO_TRICKERY_BUTTON_HOVER, FILE_CASINO_TRICKERY_BUTTON_CLICK, 4, onButtonInCasinoClick);
	Button buttons[CASINO_BUTTON_COUNT] = { backButton, jackpotButton, trickeryButton };

	Image images[CASINO_IMAGE_COUNT] = {
		{ FILE_CASINO_BACKGROUND, 0, 0 },
		{ FILE_MONEY_BACKGROUND, 1850, 50 },
		{ backButton.normal, backButton.x, backButton.y },
		{ jackpotButton.normal, jackpotButton.x, jackpotButton.y },
		{ trickeryButton.normal, trickeryButton.x, trickeryButton.y }
	};
	layer.images = images;
	layer.imageCount = CASINO_IMAGE_COUNT;
	layer.applyToDC = applyToDcInCasino;

	startButtonListener(buttons, CASINO_BUTTON_COUNT, &layer);
}
