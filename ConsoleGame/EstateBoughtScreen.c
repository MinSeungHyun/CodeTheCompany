#include "Defines.h"

//�ε��꿡�� �������� ������ �� �ߴ� ȭ��
void beginEstateBoughtScreen(int buyItemIndex) {
	stopButtonListener();

	Image firstOffice, myBuilding, casino, estate;
	getBuildingImages(&firstOffice, &myBuilding, &casino, &estate);
	Image images[6] = {
		{FILE_MAP, 0, 0}, //0
		firstOffice, myBuilding, casino, estate, //4
		{FILE_QUEST_WINDOW_NO_TITLE, 712, 404}
	};
	layer.images = images;
	layer.applyToDC = NULL;
	layer.imageCount = 6;

	int buySuccess = 0;
	if (money > estateItems[buyItemIndex].price) {
		money -= estateItems[buyItemIndex].price;
		saveMoneyAndExp(money, userExp);
		buySuccess = 1;

	}
	if (buySuccess) {
		switch (buyItemIndex) {
		case 0:
			isFirstOfficeEnabled = 1;
			saveBuildingState(isFirstOfficeEnabled, isMyBuildingEnabled, isCasinoEnabled);
		}
	}

	char resultText[100];
	if (buySuccess) {
		sprintf(resultText, "%s", "�����ϼ̽��ϴ�.");
	}
	else sprintf(resultText, "%s", "���� �����մϴ�.");

	layer.renderAll(&layer);
	printText(layer._consoleDC, 1440, 712, 100, 0, QUEST_TEXT_COLOR, TA_CENTER, resultText);
	Sleep(1500);

	const int currentQuest = 1;
	updateQuestActiveState(&quests[currentQuest], level);
	if (quests[currentQuest].isActivated) {
		quests[currentQuest].progress++;
		saveQuestsProgress(quests[currentQuest]);
		updateQuestActiveState(&quests[currentQuest], level);
		beginQuestCompleteScreen(currentQuest);
	}
	else {
		beginMapScreen(0);
	}
}
