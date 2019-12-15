#include "Defines.h"

//����Ʈ �� ȭ�鿡�� ��ư�� Ŭ���ϸ� ȣ��Ǵ� �Լ�
void onButtonInQuestDetailClicked(Button* clickedButton) {
	playSound(SOUND_BUTTON_CLICK);
	if (clickedButton->normal == FILE_QUEST_DETIAL_CLOSE_BUTTON) {
		beginQuestScreen();
	}
}

int questIndex;
//����Ʈ �� ȭ�鿡�� ���ڸ� ����ϱ� ���� ȣ��� �Լ�
void applyToDcInQuestDetail(HDC hdc) {
	const Quest quest = quests[questIndex];
	char title[100];
	sprintf(title, quest.title, quest.progress, quest.maxProgress);

	printText(hdc, 1440, 590, 69, 0, QUEST_TEXT_COLOR, TA_CENTER, title);

	for (int i = 0; i < quest.descriptionLineCount; i++) {
		const int descriptionIndex = quest.descriptionLineCount - i - 1;
		printText(hdc, 1440, 900 - i * 60, 50, 400, QUEST_TEXT_COLOR, TA_CENTER, (char*)quest.descriptions[descriptionIndex]);
	}

	char rewardText[100];
	char rewardXP[30];
	sprintf(rewardXP, "%s", commify(quest.rewardXP)); //commify�Լ��� ���ÿ� ȣ���ϸ� ���� ���� �����Ƿ� �̸� ����
	sprintf(rewardText, "���� %s�� %sxp", commify(quest.rewardMoney), rewardXP);
	printText(hdc, 1440, 1050, 70, 400, QUEST_TEXT_COLOR, TA_CENTER, rewardText);
}

//����Ʈ �� ȭ���� �����ϴ� �Լ�
void beginQuestDetailScreen(int index) {
	stopButtonListener();
	questIndex = index;

	const Button closeButton = createButton(2140, 428, FILE_QUEST_DETIAL_CLOSE_BUTTON, FILE_QUEST_DETIAL_CLOSE_BUTTON_HOVER, FILE_QUEST_DETIAL_CLOSE_BUTTON_CLICK, 6, onButtonInQuestDetailClicked);
	Button buttons[1] = { closeButton };

	Image firstOffice, myBuilding, casino, estate;
	getBuildingImages(&firstOffice, &myBuilding, &casino, &estate);
	Image images[7] = {
		{FILE_MAP, 0, 0}, //0
		firstOffice, myBuilding, casino, estate, //4
		{FILE_QUEST_DETAIL, 566, 326, 19},
		{closeButton.normal, closeButton.x, closeButton.y}
	};
	layer.images = images;
	layer.applyToDC = applyToDcInQuestDetail;
	layer.imageCount = 7;

	startButtonListener(buttons, 1, &layer);
}