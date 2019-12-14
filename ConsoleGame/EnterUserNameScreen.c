#include "Defines.h"
#include <conio.h>

//사용자 이름 입력받는 화면 초기화
void initUserNameScreen(const int x) {
	layer.renderAll(&layer);
	printText(layer._consoleDC, 1440, 300, 80, 0, RGB(0, 0, 0), TA_CENTER, "성, 이름을 입력해주세요");
	printText(layer._consoleDC, x, 700, 60, 0, RGB(0, 0, 0), TA_LEFT, "  성 :");
	printText(layer._consoleDC, x, 800, 60, 0, RGB(0, 0, 0), TA_LEFT, "이름 :");
}

//사용자 이름 입력받는 화면을 시작함
void beginEnterUserNameScreen() {
	const int x = 1250;
	firstName[0] = '\0';
	lastName[0] = '\0';

	Image images[2] = { { FILE_COIN_BLUR, 0, 0 } };
	layer.images = images;
	layer.imageCount = 1;
	initUserNameScreen(x);

	char* editingText = lastName;
	int i = 0;
	while (1) {
		const int input = _getch();

		if (input == '\r') {
			if ((editingText == lastName && lastName[0] == '\0') || (editingText == firstName && firstName[0] == '\0')) continue;
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
