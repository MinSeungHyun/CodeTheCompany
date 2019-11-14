#include <conio.h>
#include "Initializer.h"
#include "resources.h"
#include "MouseInput.h"
#include "Utils.h"
#include "ButtonUtils/Button.h"
#include "SaveFileManager.h"

#define BigInt unsigned long long
#define QUEST_TEXT_COLOR RGB(141,110,99)
#define DEFAULT_MONEY 10000

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;
ImageLayer layer;

void initLayer();
void gotoXY(int, int);
Button createButton(int, int, char*, char*, char*, int, void(*onClick)(Button*));
void printText(HDC, int, int, int, int, COLORREF, int, char*);
void textPositionTester(int, int, COLORREF, int, char*);
void beginStartScreen();
void getUserName();
void beginMapScreen();
void beginStoryScreen();

char lastName[100], firstName[100];
BigInt money, userExp;
int level;

int main() {
	initialize();
	initLayer();
	Sleep(300);

	beginStartScreen();
	Sleep(500);

	if (!isFileExist(DIR_NAME)) {
		getUserName();
		Sleep(500);
	}
	loadName(lastName, firstName);

	if (!isFileExist(DIR_COMPANY_NAME)) {
		beginStoryScreen();
		Sleep(1000);
	}

	beginMapScreen();
}

void onButtonClick(Button* clickedButton) {
	if (clickedButton->normal == FILE_START_BUTTON) {
		layer.fadeOut(&layer, NULL);
		stopButtonListener();
	}
}

void beginStartScreen() {
	const Button startButton = createButton(1114, 1150, FILE_START_BUTTON, FILE_START_BUTTON_HOVER, FILE_START_BUTTON_CLICK, 2, onButtonClick);
	Button buttons[1] = { startButton };

	Image titleImages[3] = {
		{FILE_TITLE, 0, 0},
		{FILE_TITLE_TEXT, 638, 134},
		{startButton.normal, startButton.x, startButton.y}
	};
	layer.images = titleImages;
	layer.imageCount = 3;
	layer.renderAll(&layer);

	startButtonListener(buttons, 1, &layer);
}

void initUserNameScreen(const int x) {
	layer.renderAll(&layer);
	printText(layer._consoleDC, 1440, 300, 80, 0, RGB(0, 0, 0), TA_CENTER, "성, 이름을 입력해주세요");
	printText(layer._consoleDC, x, 700, 60, 0, RGB(0, 0, 0), TA_LEFT, "  성 :");
	printText(layer._consoleDC, x, 800, 60, 0, RGB(0, 0, 0), TA_LEFT, "이름 :");
}

void getUserName() {
	const int x = 1250;

	Image images[2] = { { FILE_COIN_BLUR, 0, 0 } };
	layer.images = images;
	layer.imageCount = 1;
	initUserNameScreen(x);

	char* editingText = lastName;
	int i = 0;
	while (1) {
		const int input = _getch();

		if (input == '\r') {
			if (editingText == lastName) {
				i = 0;
				editingText = firstName;
				continue;
			}
			break;
		}
		if (input == '\b') {
			if (editingText[i - 1] < -1) i -= 3;
			else i -= 2;
			if (i < -1) i = -1;
			initUserNameScreen(x);
		}
		else if (i >= 6 || input == ' ' || input == '\\') continue;
		else {
			editingText[i] = input;
			if (input >= 128) {
				editingText[++i] = _getch();
			}
		}
		editingText[i + 1] = '\0';
		printText(layer._consoleDC, x + 210, 700, 60, 0, RGB(0, 0, 0), TA_LEFT, lastName);
		printText(layer._consoleDC, x + 210, 800, 60, 0, RGB(0, 0, 0), TA_LEFT, firstName);

		i++;
	}
	layer.images[0].fileName = "";
	layer.renderAll(&layer);
	saveName(trim(lastName), trim(firstName));
}

void printStoryStartText(HDC hdc) {
	char name[100];
	sprintf(name, "23살 1인 앱 개발자 %s%s...", lastName, firstName);
	printText(hdc, 1440, 750, 60, 0, RGB(255, 255, 255), TA_CENTER, name);
}

void printStory1Text(HDC hdc) {
	printText(hdc, 100, 100, 60, 0, RGB(0, 0, 0), TA_LEFT, "밥 먹고 코딩하는 게 일상이었던 나...");
	printText(hdc, 100, 200, 60, 0, RGB(0, 0, 0), TA_LEFT, "여느 때와 다름없이 오늘도 앱을 개발하고 스토어에 올렸다.");
}

void printStoryAfterText(HDC hdc) {
	printText(hdc, 1440, 750, 60, 0, RGB(255, 255, 255), TA_CENTER, TEXT("한달 후..."));
}

void printStory2Text(HDC hdc) {
	const int x = 2800, y = 1250;
	printText(hdc, x, y, 60, 0, RGB(0, 0, 0), TA_RIGHT, TEXT("이게 뭐야!!!!"));
	printText(hdc, x, y + 70, 60, 0, RGB(0, 0, 0), TA_RIGHT, TEXT("평소에는 며칠이 지나도 오르지 않던 다운로드 수 그래프가"));
	printText(hdc, x, y + 140, 60, 0, RGB(0, 0, 0), TA_RIGHT, TEXT("가파른 상승곡선을 이루고 있었다!!"));
}

void printStory3Text(HDC hdc) {
	printText(hdc, 1000, 250, 60, 0, RGB(0, 0, 0), TA_LEFT, TEXT("좋았어 이제 회사를 차려보자!!"));
}

void beginStoryScreen() {
	Image images[1] = { {"", 0, 0} };
	layer.imageCount = 1;
	layer.images = images;

	layer.images[0].fileName = "";
	layer.fadeIn(&layer, printStoryStartText);
	Sleep(2000);
	layer.fadeOut(&layer, printStoryStartText);

	layer.images[0].fileName = FILE_STORY_1;
	layer.fadeIn(&layer, printStory1Text);
	Sleep(2000);
	layer.fadeOut(&layer, printStory1Text);

	layer.images[0].fileName = "";
	layer.fadeIn(&layer, printStoryAfterText);
	Sleep(500);
	layer.fadeOut(&layer, printStoryAfterText);

	layer.images[0].fileName = FILE_STORY_2;
	layer.fadeIn(&layer, printStory2Text);
	Sleep(3000);
	layer.fadeOut(&layer, printStory2Text);

	layer.images[0].fileName = FILE_STORY_3;
	layer.fadeIn(&layer, printStory3Text);
	Sleep(2000);
	layer.images[0].fileName = "";
	layer.renderAll(&layer);
}

void initGetCompanyNameScreen() {
	layer.images[5] = (Image){ FILE_QUEST_WINDOW_NO_TITLE, 730, 380 };
	layer.imageCount = 6;
	layer.renderAll(&layer);

	printText(layer._consoleDC, 1440, 500, 70, 0, QUEST_TEXT_COLOR, TA_CENTER, "회사 이름을 입력해주세요");
}

void getCompanyNameIfNotExist() {
	if (isFileExist(DIR_COMPANY_NAME)) return;
	initGetCompanyNameScreen();

	char companyName[100];
	int i = 0;
	while (1) {
		const int input = _getch();

		if (input == '\r') {
			break;
		}
		if (input == '\b') {
			if (companyName[i - 1] < -1) i -= 3;
			else i -= 2;
			if (i < -1) i = -1;
		}
		else if (i >= 30 || input == ' ' || input == '\\') continue;
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

void updateUserValues() {
	loadMoneyAndExp(&money, &userExp);
	level = (int)sqrtl((long double)(userExp / 400));
}

BigInt getExpForLevel(int level) {
	return (BigInt)(400 * (pow(level, 2)));
}

BigInt getTotalExpForLevel(int level) {
	return getExpForLevel(level + 1) - getExpForLevel(level);
}

BigInt getAchievedExp() {
	return userExp - getExpForLevel(level);
}

int getProgressFromExp() {
	const BigInt totalExp = getTotalExpForLevel(level);
	const BigInt achievedExp = getAchievedExp();
	return (int)((long double)achievedExp / totalExp * 10);
}

void initUserValues() {
	if (!isFileExist(DIR_MONEY_AND_EXP))
		saveMoneyAndExp(DEFAULT_MONEY, 0);
	updateUserValues();

	char LEVEL_PROGRESS_FILE_NAME[100];
	sprintf(LEVEL_PROGRESS_FILE_NAME, FILE_LEVEL_PROGRESS, getProgressFromExp());

	const Image levelBackground = { FILE_LEVEL_BACKGROUND, 65, 65 };
	const Image levelProgress = { LEVEL_PROGRESS_FILE_NAME, 455,65 };
	const Image moneyBackground = { FILE_MONEY_BACKGROUND, 1250, 65 };

	layer.images[5] = levelBackground;
	layer.images[6] = levelProgress;
	layer.images[7] = moneyBackground;
	layer.imageCount = 8;
	layer.renderAll(&layer);

	printText(layer._consoleDC, 1450, 90, 50, 0, RGB(255, 255, 255), TA_RIGHT, "원");
}

void displayUserValues() {
	char LEVEL_PROGRESS_FILE_NAME[100];
	sprintf(LEVEL_PROGRESS_FILE_NAME, FILE_LEVEL_PROGRESS, getProgressFromExp());
	layer.images[6].fileName = LEVEL_PROGRESS_FILE_NAME;
	layer.renderAll(&layer);

	char levelString[10];
	sprintf(levelString, "Lv.%d", level);
	printText(layer._consoleDC, 242, 125, 100, 0, RGB(0, 0, 0), TA_CENTER, levelString);

	char moneyString[100];
	sprintf(moneyString, "%lld", money);
	printText(layer._consoleDC, 1390, 90, 70, 0, RGB(255, 255, 255), TA_LEFT, moneyString);
	printText(layer._consoleDC, 2080, 100, 50, 0, RGB(255, 255, 255), TA_RIGHT, "원");
}

void onButtonInMapClicked(Button* clickedButton) {

}

void beginMapScreen() {
	void initMapScreen(Button*, Image*);
	Button buttons[4];
	Image images[10];
	initMapScreen(buttons, images);

	getCompanyNameIfNotExist();
	char companyName[100];
	loadCompanyName(companyName);

	initUserValues();

	updateUserValues();
	displayUserValues();

	Button levelProgressCollider = createButton(455, 65, FILE_LEVEL_PROGRESS_DEFAULT, NULL, NULL, -1, NULL);
	int isExpShowed = 0;
	while (1) {
		if (levelProgressCollider.isHovered(&levelProgressCollider, getMousePosition())) {
			if (isExpShowed) continue;
			printText(layer._consoleDC, 540, 100, 50, 10, RGB(255, 255, 255), TA_LEFT, "10,000/123,456");
			isExpShowed = 1;
		}
		else {
			if (!isExpShowed) continue;
			displayUserValues();
			isExpShowed = 0;
		}
	}
}

void initMapScreen(Button* buttons, Image* images) {
	const Button firstOffice = createButton(370, 370, FILE_FIRST_OFFICE, FILE_FIRST_OFFICE_HOVER, FILE_FIRST_OFFICE_CLICK, 1, onButtonInMapClicked);
	const Button myBuilding = createButton(800, 400, FILE_MY_BUILDING, FILE_MY_BUILDING_HOVER, FILE_MY_BUILDING_CLICK, 2, onButtonInMapClicked);
	const Button estate = createButton(1368, 284, FILE_ESTATE, FILE_ESTATE_HOVER, FILE_ESTATE_CLICK, 3, onButtonInMapClicked);
	const Button casino = createButton(2094, 688, FILE_CASINO, FILE_CASINO_HOVER, FILE_CASINO_CLICK, 4, onButtonInMapClicked);

	buttons[0] = firstOffice;
	buttons[1] = myBuilding;
	buttons[2] = estate;
	buttons[3] = casino;

	images[0] = (Image){ FILE_MAP, 0, 0 };
	images[1] = (Image){ firstOffice.normal, firstOffice.x, firstOffice.y };
	images[2] = (Image){ myBuilding.normal, myBuilding.x,myBuilding.y };
	images[3] = (Image){ estate.normal, estate.x, estate.y };
	images[4] = (Image){ casino.normal, casino.x, casino.y };

	layer.images = images;
	layer.imageCount = 5;
	layer.fadeIn(&layer, NULL);
}

void printText(HDC hdc, int x, int y, int size, int weight, COLORREF textColor, int align, char* text) {
	if (weight == 0) weight = 900;
	size = (int)(size * RESOLUTION_MULTIPLIER);
	const HFONT font = CreateFont(size, 0, 0, 0, weight, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("둥근모꼴"));

	SelectObject(hdc, font);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, textColor);
	SetTextAlign(hdc, align);

	x = (int)(x * RESOLUTION_MULTIPLIER);
	y = (int)(y * RESOLUTION_MULTIPLIER);
	TextOut(hdc, x, y, text, lstrlen(text));

	PAINTSTRUCT paint;
	EndPaint(WINDOW_HANDLE, &paint);

	DeleteObject(font);
}

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

Button createButton(int x, int y, char* normal, char* hovered, char* clicked, int indexOfLayer, void (*onClick)(Button*)) {
	Button button = DEFAULT_BUTTON;
	button.x = x;
	button.y = y;
	button.normal = normal;
	button.hovered = hovered;
	button.clicked = clicked;
	button.initialize(&button);
	button.indexOfImageLayer = indexOfLayer;
	button.onClick = onClick;
	return button;
}

void gotoXY(int x, int y) {
	gotoxy((COORD) { x, y });
}

void initLayer() {
	layer = DEFAULT_IMAGE_LAYER;
	layer.initialize(&layer);
	layer.transparentColor = RGB(0, 255, 25);
}