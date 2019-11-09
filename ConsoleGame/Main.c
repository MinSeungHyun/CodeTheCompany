#include <locale.h>
#include "Initializer.h"
#include "resources.h"
#include "process.h"
#include "MouseInput.h"
#include "ImageUtils/ImageLayer.h"
#include "ButtonUtils/Button.h"

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;
ImageLayer layer;

void initLayer();
void gotoXY(int, int);
Button createButton(int, int, wchar_t*, wchar_t*, wchar_t*);
void onMouseDown();
void onMouseUp();
void checkMouseStateThread();
void printText(HDC, int, int, int, COLORREF, int, LPCWSTR);
void beginStartScreen();
void getUserName(char*, char*);
void beginStoryScreen();

int isMouseDown = 0;
int isMouseUp = 0;

char lastName[100], firstName[100];

int main() {
	initialize();
	initLayer();
	Sleep(300);

	_beginthread(checkMouseStateThread, 0, NULL);

	beginStartScreen();
	Sleep(200);
	getUserName(lastName, firstName);
	Sleep(200);
	beginStoryScreen();
}

void beginStartScreen() {
	Button startButton = createButton(1114, 1150, FILE_START_BUTTON, FILE_START_BUTTON_HOVER, FILE_START_BUTTON_CLICK);

	Image titleImages[3] = {
		{FILE_TITLE, 0, 0},
		{FILE_TITLE_TEXT, 638, 134},
		{startButton.normal, startButton.x, startButton.y}
	};
	layer.images = titleImages;
	layer.imageCount = 3;
	layer.renderAll(&layer);

	COORD mousePosition = { 0, 0 };
	int isStartButtonHovered = 0;
	while (1) {
		mousePosition = getMousePosition();
		isStartButtonHovered = startButton.isHovered(&startButton, mousePosition);

		if (isStartButtonHovered) {
			if (isMouseDown) {
				layer.images[2].fileName = startButton.clicked;
			}
			else {
				layer.images[2].fileName = startButton.hovered;
			}
		}
		else
			layer.images[2].fileName = startButton.normal;

		if (isMouseUp) {
			isMouseUp = 0;
			if (isStartButtonHovered) {
				layer.fadeOut(&layer, NULL);
				break;
			}
		}

		layer.renderAll(&layer);
	}
}

void getUserName(char* lastName, char* firstName) {
	system("cls");
	gotoXY(CONSOLE_WIDTH / 2 - 10, CONSOLE_HEIGHT / 2 - 2);
	printf("��, �̸��� �Է����ּ���");
	gotoXY(CONSOLE_WIDTH / 2 - 10, CONSOLE_HEIGHT / 2 + 2);
	printf("�� : ");
	scanf("%s", lastName);
	gotoXY(CONSOLE_WIDTH / 2 - 10, CONSOLE_HEIGHT / 2 + 3);
	printf("�̸� : ");
	scanf("%s", firstName);
	system("cls");
}

void printStoryStartText(HDC hdc) {
	char name[100];
	sprintf(name, "23�� 1�� �� ������ %s%s...", lastName, firstName);

	wchar_t wText[100];
	setlocale(LC_ALL, "");
	mbstowcs(wText, name, strlen(name) + 1);
	printText(hdc, 1440, 750, 60, RGB(255, 255, 255), TA_CENTER, (LPCWSTR)wText);
}

void printStory1Text(HDC hdc) {
	printText(hdc, 100, 100, 60, RGB(0, 0, 0), TA_LEFT, TEXT("�� �԰� �ڵ��ϴ� �� �ϻ��̾��� ��..."));
	printText(hdc, 100, 200, 60, RGB(0, 0, 0), TA_LEFT, TEXT("���� ���� �ٸ����� ���õ� ���� �����ϰ� ���� �÷ȴ�."));
}

void printStoryAfterText(HDC hdc) {
	printText(hdc, 1440, 750, 60, RGB(255, 255, 255), TA_CENTER, TEXT("�Ѵ� ��..."));
}

void printStory2Text(HDC hdc) {
	const int x = 2800, y = 1250;
	printText(hdc, x, y, 60, RGB(0, 0, 0), TA_RIGHT, TEXT("�̰� ����!!!!"));
	printText(hdc, x, y + 70, 60, RGB(0, 0, 0), TA_RIGHT, TEXT("��ҿ��� ��ĥ�� ������ ������ �ʴ� �ٿ�ε� �� �׷�����"));
	printText(hdc, x, y + 140, 60, RGB(0, 0, 0), TA_RIGHT, TEXT("���ĸ� ��°�� �̷�� �־���!!"));
}

void printStory3Text(HDC hdc) {
	printText(hdc, 1000, 250, 60, RGB(0, 0, 0), TA_LEFT, TEXT("���Ҿ� ���� ȸ�縦 ��������!!"));
}

void beginStoryScreen() {
	Image images[1] = { {L"", 0, 0} };
	layer.imageCount = 1;
	layer.images = images;

	layer.images[0].fileName = L"";
	layer.fadeIn(&layer, printStoryStartText);
	Sleep(2000);
	layer.fadeOut(&layer, printStoryStartText);

	layer.images[0].fileName = FILE_STORY_1;
	layer.fadeIn(&layer, printStory1Text);
	Sleep(2000);
	layer.fadeOut(&layer, printStory1Text);

	layer.images[0].fileName = L"";
	layer.fadeIn(&layer, printStoryAfterText);
	Sleep(500);
	layer.fadeOut(&layer, printStoryAfterText);

	layer.images[0].fileName = FILE_STORY_2;
	layer.fadeIn(&layer, printStory2Text);
	Sleep(4000);
	layer.fadeOut(&layer, printStory2Text);

	layer.images[0].fileName = FILE_STORY_3;
	layer.fadeIn(&layer, printStory3Text);
	Sleep(2000);
	layer.fadeOut(&layer, printStory3Text);
}

void onMouseDown() {
	isMouseDown = 1;
}

void onMouseUp() {
	isMouseDown = 0;
	isMouseUp = 1;
}

void checkMouseStateThread() {
	while (1) {
		if (hasInput() && isMouseClicked()) {
			onMouseDown();
			while (isMouseClicked());
			onMouseUp();
		}
	}
}

void printText(HDC hdc, int x, int y, int size, COLORREF textColor, int align, LPCWSTR text) {
	size = (int)(size * RESOLUTION_MULTIPLIER);
	const HFONT font = CreateFont(size, 0, 0, 0, 900, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�ձٸ��"));

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

Button createButton(int x, int y, wchar_t* normal, wchar_t* hovered, wchar_t* clicked) {
	Button button = DEFAULT_BUTTON;
	button.x = x;
	button.y = y;
	button.normal = normal;
	button.hovered = hovered;
	button.clicked = clicked;
	button.initialize(&button);
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