#include "Defines.h"

//레벨업 되었을 시 나오는 화면
void beginLevelUpScreen() {
	stopButtonListener();

	Image images[1] = {
		{FILE_LEVEL_UP_BACKGROUND, 0, 0}
	};
	layer.images = images;
	layer.applyToDC = NULL;
	layer.imageCount = 1;

	layer.renderAll(&layer);

	char levelText[100];
	sprintf(levelText, "Lv.%d", level);
	printText(layer._consoleDC, 1440, 568, 200, 0, RGB(0, 0, 0), TA_CENTER, levelText);	printText(layer._consoleDC, 1452, 982, 100, 0, RGB(251, 192, 45), TA_CENTER, "LEVEL UP!");
	Sleep(2000);
	beginMapScreen(0);
}