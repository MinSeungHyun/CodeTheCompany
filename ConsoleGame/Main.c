#include <locale.h>
#include "Initializer.h"
#include "resources.h"
#include "MouseInput.h"
#include "ImageUtils/ImageLayer.h"
#include "ButtonUtils/Button.h"

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;
ImageLayer layer;

void initLayer();
void gotoXY(int, int);
Button createButton(int, int, char*, char*, char*, int, void(*onClick)(Button*));
void printText(HDC, int, int, int, int, COLORREF, int, char*);
void beginStartScreen();
void getUserName(char*, char*);
void beginStoryScreen();

char lastName[100], firstName[100];

int main() {
	initialize();
	initLayer();
	Sleep(300);

	beginStartScreen();
	Sleep(200);
	getUserName(lastName, firstName);
	Sleep(200);
	beginStoryScreen();
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

void getUserName(char* lastName, char* firstName) {
	system("cls");
	gotoXY(CONSOLE_WIDTH / 2 - 10, CONSOLE_HEIGHT / 2 - 2);
	printf("성, 이름을 입력해주세요");
	gotoXY(CONSOLE_WIDTH / 2 - 10, CONSOLE_HEIGHT / 2 + 2);
	printf("성 : ");
	scanf("%s", lastName);
	gotoXY(CONSOLE_WIDTH / 2 - 10, CONSOLE_HEIGHT / 2 + 3);
	printf("이름 : ");
	scanf("%s", firstName);
	system("cls");
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
	layer.fadeOut(&layer, printStory3Text);
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