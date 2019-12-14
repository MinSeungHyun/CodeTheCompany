#include "Defines.h"

//���丮 ù��° ȭ�� ����
void printStoryStartText(HDC hdc) {
	char name[100];
	sprintf(name, "23�� 1�� �� ������ %s%s...", lastName, firstName);
	printText(hdc, 1440, 750, 60, 0, RGB(255, 255, 255), TA_CENTER, name);
}

//���丮 ù��° ȭ�� ����
void printStory1Text(HDC hdc) {
	printText(hdc, 100, 100, 60, 0, RGB(0, 0, 0), TA_LEFT, "�� �԰� �ڵ��ϴ� �� �ϻ��̾��� ��...");
	printText(hdc, 100, 200, 60, 0, RGB(0, 0, 0), TA_LEFT, "���� ���� �ٸ����� ���õ� ���� �����ϰ� ���� �÷ȴ�.");
}

//���丮 ù��° ȭ�� ����
void printStoryAfterText(HDC hdc) {
	printText(hdc, 1440, 750, 60, 0, RGB(255, 255, 255), TA_CENTER, TEXT("�Ѵ� ��..."));
}

//���丮 �ι�° ȭ�� ����
void printStory2Text(HDC hdc) {
	const int x = 2800, y = 1250;
	printText(hdc, x, y, 60, 0, RGB(0, 0, 0), TA_RIGHT, TEXT("�̰� ����!!!!"));
	printText(hdc, x, y + 70, 60, 0, RGB(0, 0, 0), TA_RIGHT, TEXT("��ҿ��� ��ĥ�� ������ ������ �ʴ� �ٿ�ε� �� �׷�����"));
	printText(hdc, x, y + 140, 60, 0, RGB(0, 0, 0), TA_RIGHT, TEXT("���ĸ� ��°�� �̷�� �־���!!"));
}

//���丮 ����° ȭ�� ����
void printStory3Text(HDC hdc) {
	printText(hdc, 1000, 250, 60, 0, RGB(0, 0, 0), TA_LEFT, TEXT("���Ҿ� ���� ȸ�縦 ��������!!"));
}

//���丮 ȭ�� ����
void beginStoryScreen() {
	playBGM(SOUND_STORY_BGM);
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
	stopBGM();
}