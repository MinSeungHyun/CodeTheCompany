/*
 * ���� : �ν���(����), ������(������)
 * https://github.com/MinSeungHyun/console-game
 * ���� �̸� : Code The Company
 * ���� ȸ�縦 �濵�ϰ�, Ű���� �� �ִ� �����̴�.
 * �̸��� ȸ�� �̸��� �Է��ϴ� �κ��� �����ϰ� ��� ������ ���콺�θ� �̷������,
 * Ŭ���� �� �ִ� �κ��� ���콺�� �ø��� �����ȴ�.
 */

#include "Defines.h"
#include <conio.h>

void initLayer();
void textPositionTester(int, int, COLORREF, int, char*);
void beginMapScreen(int);
void beginEstateScreen();
void beginQuestScreen();
void begindQuestDetailScreen(int);
void beginSettingScreen();

//������ ���� �����̴�. (���߿� ���� �ٽý����� �� �ʿ��ؼ� �и��ߴ�.)
void mainProcess() {
	initialize();
	_mkdir(DIR_SAVE);
	initLayer();
	initQuests();
	initEstateItems();
	Sleep(300);

	if (ENABLE_DEVELOPMENT_MODE) {
		beginMapScreen(0);
	}
	else {
		beginStartScreen();
		Sleep(500);

		if (!isFileExist(DIR_NAME)) {
			beginEnterUserNameScreen();
			Sleep(500);
		}
		loadName(lastName, firstName);

		if (!isFileExist(DIR_COMPANY_NAME)) {
			beginStoryScreen();
			Sleep(1000);
		}
		beginMapScreen(1);
	}
}

/*
 * mainProcess�Լ��� �����Ų��.
 * mainProcess������ ������ �ϱ� ���� �⺻ ������ �� ��, ���� ȭ����� �������� ����Ǵµ�,
 * beginMapScreen���� ���� ȭ���� ������Ե� �� ���ʹ� ������� �Է¿� �°� ����Ǿ�� �ϹǷ�
 * ���� �Լ����� ������ ����Ǵ� ���� �ƴ϶� ������ ȭ�鿡�� ������� �Է¿� �°� ����ȴ�.
 */
int main() {
	mainProcess();
}

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

//ȸ�� �̸� �Է¹޴� ȭ���� �ʱ�ȭ��
void initGetCompanyNameScreen() {
	layer.images[5] = (Image){ FILE_QUEST_WINDOW_NO_TITLE, 730, 380 };
	layer.imageCount = 6;
	layer.renderAll(&layer);

	printText(layer._consoleDC, 1440, 500, 70, 0, QUEST_TEXT_COLOR, TA_CENTER, "ȸ�� �̸��� �Է����ּ���");
}

//ȸ�� �̸� �Է¹޴� ȭ�� ����
void getCompanyNameIfNotExist() {
	if (isFileExist(DIR_COMPANY_NAME)) return;
	initGetCompanyNameScreen();

	char companyName[100];
	companyName[0] = '\0';
	int i = 0;
	while (1) {
		const int input = _getch();

		if (input == '\r') {
			if (companyName[0] == '\0') continue;
			break;
		}
		if (input == '\b') {
			if (companyName[i - 1] < -1) i -= 3;
			else i -= 2;
			if (i < -1) i = -1;
		}
		else if (i >= COMPANY_NAME_MAX_LENGTH || input == ' ' || input == '\\') continue;
		else {
			companyName[i] = input;
			if (input >= 128) {
				companyName[++i] = _getch();
			}
		}
		companyName[i + 1] = '\0';
		initGetCompanyNameScreen();
		printText(layer._consoleDC, 1440, 830, 70, 0, QUEST_TEXT_COLOR, TA_CENTER, companyName);

		i++;
	}

	saveCompanyName(companyName);
}

//����, ����ġ, �ʴ� ������ ���� ������
void updateUserValues() {
	loadMoneyAndExp(&money, &userExp);
	level = (int)sqrtl((long double)(userExp / 400));

	loadMPS(&mps);
}

//���� ������ ����ġ�� ��ȯ��
BigInt getExpForLevel(int level) {
	return (BigInt)(400 * (pow(level, 2)));
}

//���� �������� ���� �������� ���� ���� ����ġ�� ��ȯ��
BigInt getTotalExpForLevel(int level) {
	return getExpForLevel(level + 1) - getExpForLevel(level);
}

//���� �������� ������������ ���� ���� ���� ����ġ�� ��ȯ��
BigInt getAchievedExp() {
	return userExp - getExpForLevel(level);
}

//���� �������� ���� ���������� ���൵�� 0���� 10���� �߿� ��ȯ����
int getProgressFromExp() {
	const BigInt totalExp = getTotalExpForLevel(level);
	const BigInt achievedExp = getAchievedExp();
	return (int)((long double)achievedExp / totalExp * 10);
}

//����ȭ�鿡�� ����ġ�� ���� ���콺�� �ø��� ȣ��Ǿ� ��ġ�� ��Ÿ���ִ� �Լ�
void displayExpDetail(HDC hdc) {
	char expText[100];
	sprintf(expText, "%lld/%lld", getAchievedExp(), getTotalExpForLevel(level));
	printText(hdc, 540, 100, 50, 10, RGB(255, 255, 255), TA_LEFT, expText);
}

int isExpDetailShow = 0;
//����ȭ�鿡�� ȭ�鿡 �۾��� ����ϱ� ���� ȣ��Ǵ� �Լ�
void applyUserValuesToDC(HDC hdc) {
	static char LEVEL_PROGRESS_FILE_NAME[100];
	sprintf(LEVEL_PROGRESS_FILE_NAME, FILE_LEVEL_PROGRESS, getProgressFromExp());
	layer.images[LEVEL_PROGRESS_INDEX].fileName = LEVEL_PROGRESS_FILE_NAME;

	char levelString[10];
	sprintf(levelString, "Lv.%d", level);
	printText(hdc, 242, 125, 100, 0, RGB(0, 0, 0), TA_CENTER, levelString);

	char moneyString[100];
	sprintf(moneyString, "%lld", money);
	printText(hdc, 1390, 90, 70, 0, RGB(255, 255, 255), TA_LEFT, moneyString);
	printText(hdc, 2080, 100, 50, 0, RGB(255, 255, 255), TA_RIGHT, "��");

	char mpsString[100];
	sprintf(mpsString, "%lld��/��", mps);
	printText(hdc, 2080, 200, 40, 300, RGB(255, 255, 255), TA_RIGHT, mpsString);

	if (isExpDetailShow) {
		displayExpDetail(hdc);
		isExpDetailShow = 0;
	}

	printTextWithAngle(hdc, 2000, 1280, 70, 0, -100, RGB(0, 0, 0), TA_CENTER, companyName);
}

Button buttons[MAP_BUTTON_COUNT];

//�����ٿ� ���콺�� �÷��� �� ȣ��Ǵ� �Լ�
void onButtonInMapHovered(Button* hoveredButton) {
	if (hoveredButton->normal == FILE_LEVEL_PROGRESS_DEFAULT) isExpDetailShow = 1;
}

//���� ȭ�鿡 �ִ� ��ư�� Ŭ������ �� ȣ��Ǵ� �Լ�
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
}

//���� ȭ�鿡�� UI�� �ʱ�ȭ �ϱ� ���� �Լ� 
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

	printText(layer._consoleDC, 1450, 90, 50, 0, RGB(255, 255, 255), TA_RIGHT, "��");

	layer.applyToDC = applyUserValuesToDC;
}

//�ǹ����� ��� ���� ���¸� ������Ʈ �ϴ� �Լ�
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

//�� �ʸ��� ȣ��Ǿ� ���� ������Ű�� �Լ�
void onEverySecond(void* cnt) {
	money += mps;
	saveMoneyAndExp(money, userExp);
}

//���� ȭ���� �ʱ�ȭ �ϴ� �Լ�
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

//���� ȭ���� �����ϴ� �Լ�
void beginMapScreen(int isFirstShow) {
	stopButtonListener();
	layer.applyToDC = NULL;
	Image images[MAP_IMAGE_COUNT];
	initMapScreen(images, isFirstShow);

	getCompanyNameIfNotExist();
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

#define BACK_BUTTON_INDEX_OF_LAYER 1
#define ESTATE_BUTTON_COUNT 2
#define ESTATE_IMAGE_COUNT 5

//�ε��� ȭ�鿡 �ִ� ��ư�� Ŭ������ �� ȣ���
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

//�ε��� ȭ�鿡�� �۾��� ����ϱ� ���� ȣ��Ǵ� �Լ�
void applyToDcInEstate(HDC hdc) {
	char firstOfficePrice[100] = "�̹� ������";
	if (!isFirstOfficeEnabled) sprintf(firstOfficePrice, "%lld��", estateItems[0].price);
	printText(hdc, 1440, 1220, 80, 0, RGB(255, 255, 255), TA_CENTER, firstOfficePrice);
	printText(hdc, 1440, 950, 60, 0, RGB(0, 0, 0), TA_CENTER, estateItems[0].itemName);
}

//�ε��� ȭ���� �����ϴ� �Լ�
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

//������ �̹������� ������� ���¿� �°� ������ִ� �Լ�
void getBuildingImages(Image* firstOffice, Image* myBuilding, Image* casino, Image* estate) {
	if (isFirstOfficeEnabled) *firstOffice = (Image){ FILE_FIRST_OFFICE, 370, 370 };
	else *firstOffice = (Image){ FILE_FIRST_OFFICE_LOCKED, 370, 370 };

	if (isMyBuildingEnabled) *myBuilding = (Image){ FILE_MY_BUILDING, 800, 400 };
	else *myBuilding = (Image){ FILE_MY_BUILDING_LOCKED, 800, 400 };

	if (isCasinoEnabled) *casino = (Image){ FILE_CASINO, 2094, 688 };
	else *casino = (Image){ FILE_CASINO_LOCKED, 2094, 688 };

	*estate = (Image){ FILE_ESTATE, 1368, 284 };
}

//����Ʈ ��� ȭ�鿡�� �ε������� ��ư�� Y���� ��ȯ���ִ� �Լ�
inline int getQuestButtonY(int index) {
	return 551 + 144 * index;
}

int activeQuestCount;
int questButtonCount;
int* activeQuestIndex;
int firstQuestIndex = 0;
int questIdInList[4];

//����Ʈ ��� ȭ�鿡�� ��ư�� Ŭ������ �� ȣ��Ǵ� �Լ�
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
				begindQuestDetailScreen(questIdInList[i]);
				break;
			}
		}
	}
}

//����Ʈ ��� ȭ�鿡�� ���ڸ� ����ϱ� ���� ȣ��� �Լ�
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

//����Ʈ ��� ȭ���� �����ϴ� �Լ�
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
	sprintf(rewardText, "���� %lld��, %lldxp", quest.rewardMoney, quest.rewardXP);
	printText(hdc, 1440, 1050, 70, 400, QUEST_TEXT_COLOR, TA_CENTER, rewardText);
}

//����Ʈ �� ȭ���� �����ϴ� �Լ�
void begindQuestDetailScreen(int index) {
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

//imagePositionTesteró�� ������ �۾� ��ġ�� ã�� ���� ���� �Լ�
void textPositionTester(int size, int weight, COLORREF textColor, int align, char* text) {
	while (1) {
		if (isMouseClicked()) {
			const COORD position = getMousePosition();
			layer.renderAll(&layer);
			printText(layer._consoleDC, position.X, position.Y, size, weight, textColor, align, text);

			gotoXY(0, 0);
			printf("%5d %5d", position.X, position.Y);
		}
	}
}

//�̹��� ���̾� ��ü�� �ʱ�ȭ ���ִ� �Լ�
void initLayer() {
	layer = DEFAULT_IMAGE_LAYER;
	layer.initialize(&layer);
	layer.transparentColor = RGB(0, 255, 25);
}