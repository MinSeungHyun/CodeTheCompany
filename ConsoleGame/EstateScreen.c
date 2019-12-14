#include "Defines.h"

#define BACK_BUTTON_INDEX_OF_LAYER 1
#define ESTATE_BUTTON_COUNT 2
#define ESTATE_IMAGE_COUNT 5

//부동산 화면에 있는 버튼을 클릭했을 때 호출됨
void onButtonInEstateClicked(Button* button) {
	playSound(SOUND_BUTTON_CLICK);
	char* clickedButtonName = button->normal;
	if (clickedButtonName == FILE_BACK_BUTTON) {
		beginMapScreen(0);
	}
	else if (clickedButtonName == FILE_ESTATE_BUY_BUTTON) {
		beginEstateBoughtScreen(0);
	}
}

//부동산 화면에서 글씨를 출력하기 위해 호출되는 함수
void applyToDcInEstate(HDC hdc) {
	char firstOfficePrice[100] = "이미 구매함";
	if (!isFirstOfficeEnabled) sprintf(firstOfficePrice, "%lld원", estateItems[0].price);
	printText(hdc, 1440, 1220, 80, 0, RGB(255, 255, 255), TA_CENTER, firstOfficePrice);
	printText(hdc, 1440, 950, 60, 0, RGB(0, 0, 0), TA_CENTER, estateItems[0].itemName);
}

//부동산 화면을 시작하는 함수
void beginEstateScreen() {
	stopButtonListener();

	const Button backButton = createButton(100, 1280, FILE_BACK_BUTTON, FILE_BACK_BUTTON_HOVER, FILE_BACK_BUTTON_CLICK, BACK_BUTTON_INDEX_OF_LAYER, onButtonInEstateClicked);
	Button buyButton;

	if (isFirstOfficeEnabled)
		buyButton = createButton(1176, 1180, FILE_ESTATE_BOUGHT_BUTTON, FILE_ESTATE_BOUGHT_BUTTON, FILE_ESTATE_BOUGHT_BUTTON, 4, onButtonInEstateClicked);
	else
		buyButton = createButton(1176, 1180, FILE_ESTATE_BUY_BUTTON, FILE_ESTATE_BUY_BUTTON_HOVER, FILE_ESTATE_BUY_BUTTON_CLICK, 4, onButtonInEstateClicked);

	Button buttons[ESTATE_BUTTON_COUNT] = { backButton, buyButton };

	Image images[ESTATE_IMAGE_COUNT] = {
		{FILE_ESTATE_BACKGROUND, 0, 0},
		{backButton.normal, backButton.x, backButton.y},
		{FILE_ESTATE_ITEM_BACKGROUND_UNLOCKED, 1090, 614},
		{FILE_FIRST_OFFICE, 1270, 620},
		{buyButton.normal, buyButton.x, buyButton.y} //4
	};
	layer.images = images;
	layer.imageCount = ESTATE_IMAGE_COUNT;
	layer.applyToDC = applyToDcInEstate;
	layer.renderAll(&layer);

	startButtonListener(buttons, ESTATE_BUTTON_COUNT, &layer);
}
