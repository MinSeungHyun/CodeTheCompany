#include "Defines.h"

//퀘스트 상세 화면에서 버튼을 클릭하면 호출되는 함수
void onButtonInQuestDetailClicked(Button* clickedButton) {
	playSound(SOUND_BUTTON_CLICK);
	if (clickedButton->normal == FILE_QUEST_DETIAL_CLOSE_BUTTON) {
		beginQuestScreen();
	}
}

int questIndex;
//퀘스트 상세 화면에서 글자를 출력하기 위해 호출될 함수
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
	sprintf(rewardXP, "%s", commify(quest.rewardXP)); //commify함수는 동시에 호출하면 같은 값이 나오므로 미리 생성
	sprintf(rewardText, "보상 %s원 %sxp", commify(quest.rewardMoney), rewardXP);
	printText(hdc, 1440, 1050, 70, 400, QUEST_TEXT_COLOR, TA_CENTER, rewardText);
}

//퀘스트 상세 화면을 시작하는 함수
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