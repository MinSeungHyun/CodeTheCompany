#include "Defines.h"

int activeQuestCount;
int questButtonCount;
int* activeQuestIndex;
int firstQuestIndex = 0;
int questIdInList[4];

//퀘스트 목록 화면에서 인덱스별로 버튼의 Y값을 반환해주는 함수
inline int getQuestButtonY(int index) {
	return 551 + 144 * index;
}

//퀘스트 목록 화면에서 버튼을 클릭했을 때 호출되는 함수
void onButtonInQuestClicked(Button* clickedButton) {
	playSound(SOUND_BUTTON_CLICK);
	char* clickedButtonName = clickedButton->normal;

	if (clickedButtonName == FILE_BACK_BUTTON) {
		beginMapScreen(0);
	}
	else if (clickedButtonName == FILE_SCROLL_UP_BUTTON) {
		if (firstQuestIndex > 0)
			firstQuestIndex--;
	}
	else if (clickedButtonName == FILE_SCROLL_DOWN_BUTTON) {
		if (firstQuestIndex + 4 < activeQuestCount)
			firstQuestIndex++;
	}
	else if (clickedButtonName) {
		for (int i = 0; i < questButtonCount; i++) {
			if (clickedButton->y == getQuestButtonY(i)) {
				beginQuestDetailScreen(questIdInList[i]);
				break;
			}
		}
	}
}

//퀘스트 목록 화면에서 글자를 출력하기 위해 호출될 함수
void applyToDcInQuestScreen(HDC hdc) {
	printText(hdc, 1440, 280, 200, 0, QUEST_TEXT_COLOR, TA_CENTER, "QUEST");

	for (int i = 0; i < questButtonCount; i++) {
		const Quest tmp = quests[activeQuestIndex[i + firstQuestIndex]];
		const char* questTitle = tmp.title;
		questIdInList[i] = tmp.questID;
		char formatedTitle[100];
		sprintf(formatedTitle, questTitle, tmp.progress, tmp.maxProgress);
		printText(hdc, 800, 590 + 145 * i, 60, 0, RGB(0, 0, 0), TA_LEFT, formatedTitle);
	}
}

//퀘스트 목록 화면을 시작하는 함수
void beginQuestScreen() {
	stopButtonListener();
	activeQuestCount = updateAllQuestsActiveState(level);
	questButtonCount = activeQuestCount;
	if (activeQuestCount > 4) questButtonCount = 4;

	activeQuestIndex = (int*)malloc(sizeof(int) * activeQuestCount);

	for (int i = 0, index = 0; i < QUEST_COUNT; i++) {
		if (quests[i].isActivated) {
			activeQuestIndex[index] = i;
			index++;
		}
	}
	const int BUTTON_COUNT = questButtonCount + 3;

	Button* buttons = (Button*)malloc(sizeof(Button) * BUTTON_COUNT);

	const Button backButton = createButton(550, 315, FILE_BACK_BUTTON, FILE_BACK_BUTTON_HOVER, FILE_BACK_BUTTON_CLICK, 7, onButtonInQuestClicked);
	const Button upButton = createButton(2225, 650, FILE_SCROLL_UP_BUTTON, FILE_SCROLL_UP_BUTTON_HOVER, FILE_SCROLL_UP_BUTTON_CLICK, 8, onButtonInQuestClicked);
	const Button downButton = createButton(2225, 850, FILE_SCROLL_DOWN_BUTTON, FILE_SCROLL_DOWN_BUTTON_HOVER, FILE_SCROLL_DOWN_BUTTON_CLICK, 9, onButtonInQuestClicked);
	buttons[0] = backButton;
	buttons[1] = upButton;
	buttons[2] = downButton;
	for (int i = 0; i < questButtonCount; i++) {
		buttons[i + 3] = createButton(736, getQuestButtonY(i), FILE_QUEST_ITEM_BUTTON, FILE_QUEST_ITEM_BUTTON_HOVER, FILE_QUEST_ITEM_BUTTON_CLICK, i + 10, onButtonInQuestClicked);
	}

	Image firstOffice, myBuilding, casino, estate;
	getBuildingImages(&firstOffice, &myBuilding, &casino, &estate);

	Image images[14] = {
		{FILE_MAP, 0, 0}, //0
		firstOffice, myBuilding, casino, estate, //4
		{FILE_QUEST_OPEN, 450, 225},
		{FILE_QUEST_ITEMS_FRAME, 720, 535},
		{backButton.normal, backButton.x, backButton.y},
		{upButton.normal, upButton.x, upButton.y},
		{downButton.normal, downButton.x, downButton.y} //9
	};
	for (int i = 0; i < questButtonCount; i++) {
		Button tmp = buttons[i + 3];
		images[i + 10] = (Image){ tmp.normal, tmp.x, tmp.y };
	}
	layer.images = images;
	layer.applyToDC = applyToDcInQuestScreen;
	layer.imageCount = 10 + questButtonCount;

	startButtonListener(buttons, BUTTON_COUNT, &layer);
	free(activeQuestIndex);
	free(buttons);
}