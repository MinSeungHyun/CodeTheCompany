#include "Defines.h"

#define getArrowPositionX(slot) ((slot - 1) * 380 + 862)
#define ARROW_INDEX 4
#define JACKPOT_BUTTON_COUNT 2
#define JACKPOT_IMAGE_COUNT (JACKPOT_BUTTON_COUNT + 3)

void onButtonInJackpotClicked(Button* clickedButton) {
	char* buttonName = clickedButton->normal;
	if (buttonName == FILE_BACK_BUTTON) {
		beginCasinoScreen();
	}
}

void applyToDcInJackpot(HDC hdc) {
	char moneyString[100];
	sprintf(moneyString, "%lld", money);
	printText(hdc, 1990, 75, 70, 0, RGB(255, 255, 255), TA_LEFT, moneyString);
	printText(hdc, 2680, 85, 50, 0, RGB(255, 255, 255), TA_RIGHT, "¿ø");
}

void beginJackpotScreen() {
	stopButtonListener();
	Button backButton = createButton(100, 50, FILE_BACK_BUTTON, FILE_BACK_BUTTON_HOVER, FILE_BACK_BUTTON_CLICK, 2, onButtonInJackpotClicked);
	Button leverButton = createButton(2048, 434, FILE_JACKPOT_LEVER_BUTTON, FILE_JACKPOT_LEVER_BUTTON_HOVER, FILE_JACKPOT_LEVER_BUTTON_CLICK, 3, onButtonInJackpotClicked);
	Button buttons[JACKPOT_BUTTON_COUNT] = { backButton, leverButton };
	Image images[JACKPOT_IMAGE_COUNT] = {
		{ FILE_JACKPOT_BACKGROUND, 0, 0 },
		{ FILE_MONEY_BACKGROUND, 1850, 50 },
		{ backButton.normal, backButton.x, backButton.y },
		{ leverButton.normal, leverButton.x, leverButton.y },
		{ FILE_JACKPOT_ARROW, getArrowPositionX(1), 680 }
	};
	layer.images = images;
	layer.imageCount = JACKPOT_IMAGE_COUNT;
	layer.applyToDC = applyToDcInJackpot;
	images[ARROW_INDEX].isHide = 1;

	startButtonListener(buttons, JACKPOT_BUTTON_COUNT, &layer);
}
