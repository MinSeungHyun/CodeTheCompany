#include "Defines.h"

//����â���� �۾��� ����ϱ� ���� ȣ��Ǵ� �Լ�
void applyToDcInSetting(HDC hdc) {
	printText(hdc, 1135, 850, 60, 0, RGB(255, 255, 255), TA_CENTER, "���� �ʱ�ȭ");
	printText(hdc, 1670, 850, 60, 0, RGB(255, 255, 255), TA_CENTER, "���� ������");
}

//����â���� ��ư�� Ŭ���Ǹ� ȣ��Ǵ� �Լ�
void onButtonInSettingClicked(Button* clickedButton) {
	playSound(SOUND_BUTTON_CLICK);
	char* clickedButtonName = clickedButton->normal;
	if (clickedButtonName == FILE_SETTING_CLOSE_BUTTON) {
		beginMapScreen(0);
	}
	else if (clickedButtonName == FILE_RESET_BUTTON) {
		stopButtonListener();
		stopSecondClock();
		firstName[0] = '\0';
		lastName[0] = '\0';
		layer.fadeOut(&layer, NULL);
		system("RD /S /Q \"saves/\" ");
		mainProcess();
	}
	else if (clickedButtonName == FILE_CLOSE_GAME_BUTTON) {
		exit(0);
	}
}

//����â�� �����ϴ� �Լ�
void beginSettingScreen() {
	stopButtonListener();

	const Button closeButton = createButton(2006, 460, FILE_SETTING_CLOSE_BUTTON, FILE_SETTING_CLOSE_BUTTON_HOVER, FILE_SETTING_CLOSE_BUTTON_CLICK, 6, onButtonInSettingClicked);
	const Button resetButton = createButton(1058, 630, FILE_RESET_BUTTON, FILE_RESET_BUTTON_HOVER, FILE_RESET_BUTTON_CLICK, 7, onButtonInSettingClicked);
	const Button closeGameButton = createButton(1610, 630, FILE_CLOSE_GAME_BUTTON, FILE_CLOSE_GAME_BUTTON_HOVER, FILE_CLOSE_GAME_BUTTON_CLICK, 8, onButtonInSettingClicked);
	Button buttons[3] = { closeButton, resetButton, closeGameButton };

	Image firstOffice, myBuilding, casino, estate;
	getBuildingImages(&firstOffice, &myBuilding, &casino, &estate);
	Image images[9] = {
		{FILE_MAP, 0, 0}, //0
		firstOffice, myBuilding, casino, estate, //4
		{FILE_SETTING_WINDOW, 700, 382},
		{closeButton.normal, closeButton.x, closeButton.y},
		{resetButton.normal, resetButton.x, resetButton.y},
		{closeGameButton.normal, closeGameButton.x, closeGameButton.y}
	};
	layer.images = images;
	layer.applyToDC = applyToDcInSetting;
	layer.imageCount = 9;

	startButtonListener(buttons, 3, &layer);
}