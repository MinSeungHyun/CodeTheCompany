#include "Defines.h"

//스토리 첫번째 화면 시작
void printStoryStartText(HDC hdc) {
	char name[100];
	sprintf(name, "23살 1인 앱 개발자 %s%s...", lastName, firstName);
	printText(hdc, 1440, 750, 60, 0, RGB(255, 255, 255), TA_CENTER, name);
}

//스토리 첫번째 화면 시작
void printStory1Text(HDC hdc) {
	printText(hdc, 100, 100, 60, 0, RGB(0, 0, 0), TA_LEFT, "밥 먹고 코딩하는 게 일상이었던 나...");
	printText(hdc, 100, 200, 60, 0, RGB(0, 0, 0), TA_LEFT, "여느 때와 다름없이 오늘도 앱을 개발하고 스토어에 올렸다.");
}

//스토리 첫번째 화면 시작
void printStoryAfterText(HDC hdc) {
	printText(hdc, 1440, 750, 60, 0, RGB(255, 255, 255), TA_CENTER, TEXT("한달 후..."));
}

//스토리 두번째 화면 시작
void printStory2Text(HDC hdc) {
	const int x = 2800, y = 1250;
	printText(hdc, x, y, 60, 0, RGB(0, 0, 0), TA_RIGHT, TEXT("이게 뭐야!!!!"));
	printText(hdc, x, y + 70, 60, 0, RGB(0, 0, 0), TA_RIGHT, TEXT("평소에는 며칠이 지나도 오르지 않던 다운로드 수 그래프가"));
	printText(hdc, x, y + 140, 60, 0, RGB(0, 0, 0), TA_RIGHT, TEXT("가파른 상승곡선을 이루고 있었다!!"));
}

//스토리 세번째 화면 시작
void printStory3Text(HDC hdc) {
	printText(hdc, 1000, 250, 60, 0, RGB(0, 0, 0), TA_LEFT, TEXT("좋았어 이제 회사를 차려보자!!"));
}

//스토리 화면 시작
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