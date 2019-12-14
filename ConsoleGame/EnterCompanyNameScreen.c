#include "Defines.h"
#include <conio.h>

//회사 이름 입력받는 화면을 초기화함
void initGetCompanyNameScreen() {
	layer.images[5] = (Image){ FILE_QUEST_WINDOW_NO_TITLE, 730, 380 };
	layer.imageCount = 6;
	layer.renderAll(&layer);

	printText(layer._consoleDC, 1440, 500, 70, 0, QUEST_TEXT_COLOR, TA_CENTER, "회사 이름을 입력해주세요");
}

//회사 이름 입력받는 화면 시작
void beginEnterCompanyNameScreen() {
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
