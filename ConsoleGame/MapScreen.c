#include "Defines.h"

#define MAP_IMAGE_COUNT 10
#define MAP_BUTTON_COUNT 7
#define MAP_INDEX 0
#define FIRST_OFFICE_INDEX 1
#define MY_BUILDING_INDEX 2
#define ESTATE_INDEX 3
#define CASINO_INDEX 4
#define LEVEL_BACKGROUND_INDEX 5
#define LEVEL_PROGRESS_INDEX 6
#define MONEY_BACKGROUND_INDEX 7
#define BUILDING_BUTTON_INDEX_OFFSET (-1)
#define EXP_DETAIL_COLLIDER_INDEX 4
#define QUEST_BUTTON_INDEX_IN_LAYER 8
#define QUEST_BUTTON_INDEX_IN_BUTTON 5
#define SETTING_BUTTON_INDEX_IN_LAYER 9
#define SETTING_BUTTON_INDEX_IN_BUTTON 6

//메인화면에서 경험치바 위에 마우스를 올리면 호출되어 수치를 나타내주는 함수
void displayExpDetail(HDC hdc) {
	char expText[100];
	char totalExp[30];
	sprintf(totalExp, "%s", commify(getTotalExpForLevel(level)));
	sprintf(expText, "%s/%s", commify(getAchievedExp()), totalExp);
	printText(hdc, 540, 100, 50, 10, RGB(255, 255, 255), TA_LEFT, expText);
}

int isExpDetailShow = 0;
//메인화면에서 화면에 글씨를 출력하기 위해 호출되는 함수
void applyUserValuesToDC(HDC hdc) {
	static char LEVEL_PROGRESS_FILE_NAME[100];
	sprintf(LEVEL_PROGRESS_FILE_NAME, FILE_LEVEL_PROGRESS, getProgressFromExp());
	layer.images[LEVEL_PROGRESS_INDEX].fileName = LEVEL_PROGRESS_FILE_NAME;

	char levelString[10];
	sprintf(levelString, "Lv.%d", level);
	printText(hdc, 242, 125, 100, 0, RGB(0, 0, 0), TA_CENTER, levelString);

	printText(hdc, 1390, 90, 70, 0, RGB(255, 255, 255), TA_LEFT, commify(money));
	printText(hdc, 2080, 100, 50, 0, RGB(255, 255, 255), TA_RIGHT, "원");

	char mpsString[100];
	sprintf(mpsString, "%s원/초", commify(mps));
	printText(hdc, 2080, 200, 40, 300, RGB(255, 255, 255), TA_RIGHT, mpsString);

	if (isExpDetailShow) {
		displayExpDetail(hdc);
		isExpDetailShow = 0;
	}

	printTextWithAngle(hdc, 2000, 1280, 70, 0, -100, RGB(0, 0, 0), TA_CENTER, companyName);
}

Button buttons[MAP_BUTTON_COUNT];

//레벨바에 마우스를 올렸을 때 호출되는 함수
void onButtonInMapHovered(Button* hoveredButton) {
	if (hoveredButton->normal == FILE_LEVEL_PROGRESS_DEFAULT) isExpDetailShow = 1;
}

//메인 화면에 있는 버튼을 클릭했을 때 호출되는 함수
void onButtonInMapClicked(Button* clickedButton) {
	playSound(SOUND_BUTTON_CLICK);
	char* clickedButtonName = clickedButton->normal;
	if (clickedButtonName == FILE_ESTATE) {
		updateQuestActiveState(&quests[0], level);
		if (quests[0].isActivated) {
			quests[0].progress++;
			saveQuestsProgress(quests[0]);
			updateQuestActiveState(&quests[0], level);
			beginQuestCompleteScreen(0);
		}
		else {
			beginEstateScreen();
		}
	}
	else if (clickedButtonName == FILE_QUEST_BUTTON) {
		beginQuestScreen();
	}
	else if (clickedButtonName == FILE_SETTING_BUTTON) {
		beginSettingScreen();
	}
	else if (clickedButtonName == FILE_FIRST_OFFICE) {
		beginOfficeScreen();
	}
	else if (clickedButtonName == FILE_CASINO) {
		beginCasinoScreen();
	}
}

//메인 화면에서 UI를 초기화 하기 위한 함수 
void initMapUI() {
	if (!isFileExist(DIR_MONEY_AND_EXP))
		saveMoneyAndExp(DEFAULT_MONEY, DEFAULT_EXP);
	if (!isFileExist(DIR_MPS))
		saveMPS(DEFAULT_MPS);
	updateUserValues();

	char LEVEL_PROGRESS_FILE_NAME[100];
	sprintf(LEVEL_PROGRESS_FILE_NAME, FILE_LEVEL_PROGRESS, getProgressFromExp());

	const Button questButton = createButton(100, 1200, FILE_QUEST_BUTTON, FILE_QUEST_BUTTON_HOVER, FILE_QUEST_BUTTON_CLICK, QUEST_BUTTON_INDEX_IN_LAYER, onButtonInMapClicked);
	const Button settingButton = createButton(2600, 65, FILE_SETTING_BUTTON, FILE_SETTING_BUTTON_HOVER, FILE_SETTING_BUTTON_CLICK, SETTING_BUTTON_INDEX_IN_LAYER, onButtonInMapClicked);
	buttons[QUEST_BUTTON_INDEX_IN_BUTTON] = questButton;
	buttons[SETTING_BUTTON_INDEX_IN_BUTTON] = settingButton;

	const Image levelBackground = { FILE_LEVEL_BACKGROUND, 65, 65 };
	const Image levelProgress = { LEVEL_PROGRESS_FILE_NAME, 455,65 };
	const Image moneyBackground = { FILE_MONEY_BACKGROUND, 1250, 65 };
	const Image questButtonImage = { questButton.normal, 100, 1200 };
	const Image settingButtonImage = { settingButton.normal, 2600, 65 };

	layer.images[LEVEL_BACKGROUND_INDEX] = levelBackground;
	layer.images[LEVEL_PROGRESS_INDEX] = levelProgress;
	layer.images[MONEY_BACKGROUND_INDEX] = moneyBackground;
	layer.images[QUEST_BUTTON_INDEX_IN_LAYER] = questButtonImage;
	layer.images[SETTING_BUTTON_INDEX_IN_LAYER] = settingButtonImage;
	layer.imageCount = MAP_IMAGE_COUNT;
	layer.renderAll(&layer);

	printText(layer._consoleDC, 1450, 90, 50, 0, RGB(255, 255, 255), TA_RIGHT, "원");

	layer.applyToDC = applyUserValuesToDC;
}

//건물들의 잠금 해제 상태를 업데이트 하는 함수
void updateBuildingState() {
	if (!isFileExist(DIR_BUILDING_STATE)) {
		saveBuildingState(0, 0, 0);
	}
	loadBuildingState(&isFirstOfficeEnabled, &isMyBuildingEnabled, &isCasinoEnabled);
	const int offset = BUILDING_BUTTON_INDEX_OFFSET;

	if (isFirstOfficeEnabled) {
		buttons[FIRST_OFFICE_INDEX + offset].normal = FILE_FIRST_OFFICE;
		buttons[FIRST_OFFICE_INDEX + offset].hovered = FILE_FIRST_OFFICE_HOVER;
		buttons[FIRST_OFFICE_INDEX + offset].clicked = FILE_FIRST_OFFICE_CLICK;
	}
	else {
		buttons[FIRST_OFFICE_INDEX + offset].normal = FILE_FIRST_OFFICE_LOCKED;
		buttons[FIRST_OFFICE_INDEX + offset].hovered = FILE_FIRST_OFFICE_LOCKED;
		buttons[FIRST_OFFICE_INDEX + offset].clicked = FILE_FIRST_OFFICE_LOCKED;
	}
	if (isMyBuildingEnabled) {
		buttons[MY_BUILDING_INDEX + offset].normal = FILE_MY_BUILDING;
		buttons[MY_BUILDING_INDEX + offset].hovered = FILE_MY_BUILDING_HOVER;
		buttons[MY_BUILDING_INDEX + offset].clicked = FILE_MY_BUILDING_CLICK;
	}
	else {
		buttons[MY_BUILDING_INDEX + offset].normal = FILE_MY_BUILDING_LOCKED;
		buttons[MY_BUILDING_INDEX + offset].hovered = FILE_MY_BUILDING_LOCKED;
		buttons[MY_BUILDING_INDEX + offset].clicked = FILE_MY_BUILDING_LOCKED;
	}
	if (isCasinoEnabled) {
		buttons[CASINO_INDEX + offset].normal = FILE_CASINO;
		buttons[CASINO_INDEX + offset].hovered = FILE_CASINO_HOVER;
		buttons[CASINO_INDEX + offset].clicked = FILE_CASINO_CLICK;
	}
	else {
		buttons[CASINO_INDEX + offset].normal = FILE_CASINO_LOCKED;
		buttons[CASINO_INDEX + offset].hovered = FILE_CASINO_LOCKED;
		buttons[CASINO_INDEX + offset].clicked = FILE_CASINO_LOCKED;
	}
}

//메 초마다 호출되어 돈을 증가시키는 함수
void onEverySecond(void* cnt) {
	money += mps;
	saveMoneyAndExp(money, userExp);
}

//메인 화면을 초기화 하는 함수
void initMapScreen(Image* images, int isFirstShow) {
	const Button firstOffice = createButton(370, 370, FILE_FIRST_OFFICE, FILE_FIRST_OFFICE_HOVER, FILE_FIRST_OFFICE_CLICK, FIRST_OFFICE_INDEX, onButtonInMapClicked);
	const Button myBuilding = createButton(800, 400, FILE_MY_BUILDING, FILE_MY_BUILDING_HOVER, FILE_MY_BUILDING_CLICK, MY_BUILDING_INDEX, onButtonInMapClicked);
	const Button estate = createButton(1368, 284, FILE_ESTATE, FILE_ESTATE_HOVER, FILE_ESTATE_CLICK, ESTATE_INDEX, onButtonInMapClicked);
	const Button casino = createButton(2094, 688, FILE_CASINO, FILE_CASINO_HOVER, FILE_CASINO_CLICK, CASINO_INDEX, onButtonInMapClicked);
	const Button expDetailCollider = createCollider(455, 65, FILE_LEVEL_PROGRESS_DEFAULT, onButtonInMapHovered);

	int offset = BUILDING_BUTTON_INDEX_OFFSET;
	buttons[FIRST_OFFICE_INDEX + offset] = firstOffice;
	buttons[MY_BUILDING_INDEX + offset] = myBuilding;
	buttons[ESTATE_INDEX + offset] = estate;
	buttons[CASINO_INDEX + offset] = casino;
	buttons[EXP_DETAIL_COLLIDER_INDEX] = expDetailCollider;

	updateBuildingState();

	images[MAP_INDEX] = (Image){ FILE_MAP, 0, 0 };
	images[FIRST_OFFICE_INDEX] = (Image){ buttons[FIRST_OFFICE_INDEX + offset].normal,firstOffice.x, firstOffice.y };
	images[MY_BUILDING_INDEX] = (Image){ buttons[MY_BUILDING_INDEX + offset].normal, myBuilding.x,myBuilding.y };
	images[ESTATE_INDEX] = (Image){ buttons[ESTATE_INDEX + offset].normal, estate.x, estate.y };
	images[CASINO_INDEX] = (Image){ buttons[CASINO_INDEX + offset].normal, casino.x, casino.y };

	layer.images = images;
	layer.imageCount = 5;
	if (isFirstShow) layer.fadeIn(&layer, NULL);
	else layer.renderAll(&layer);
}

//메인 화면을 시작하는 함수
void beginMapScreen(int isFirstShow) {
	stopButtonListener();
	layer.applyToDC = NULL;
	Image images[MAP_IMAGE_COUNT];
	initMapScreen(images, isFirstShow);

	beginEnterCompanyNameScreen();
	loadCompanyName(companyName);

	const int previousLevel = level;
	initMapUI();
	updateUserValues();
	if (!isFirstShow && level != previousLevel) {
		beginLevelUpScreen();
	}
	else {
		if (isFirstShow) {
			startSecondClock(onEverySecond);
			playBGM(SOUND_MAIN_BGM);
		}

		startButtonListener(buttons, MAP_BUTTON_COUNT, &layer);
	}
}
