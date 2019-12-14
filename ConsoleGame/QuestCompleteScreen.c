#include "Defines.h"

//퀘스트를 완료했을 때 나오는 창이다.
void beginQuestCompleteScreen(int completedQuestIndex) {
	const Quest completedQuest = quests[completedQuestIndex];
	stopButtonListener();

	Image firstOffice, myBuilding, casino, estate;
	getBuildingImages(&firstOffice, &myBuilding, &casino, &estate);
	Image images[6] = {
		{FILE_MAP, 0, 0}, //0
		firstOffice, myBuilding, casino, estate, //4
		{FILE_QUEST_WINDOW_NO_TITLE, 712, 404}
	};
	layer.images = images;
	layer.applyToDC = NULL;
	layer.imageCount = 6;

	layer.renderAll(&layer);
	printText(layer._consoleDC, 1440, 492, 120, 0, QUEST_TEXT_COLOR, TA_CENTER, "Misson Complete");
	char questTitle[100];
	sprintf(questTitle, completedQuest.title, completedQuest.progress, completedQuest.maxProgress);
	printText(layer._consoleDC, 1440, 800, 80, 0, QUEST_TEXT_COLOR, TA_CENTER, questTitle);
	money += completedQuest.rewardMoney;
	userExp += completedQuest.rewardXP;
	saveMoneyAndExp(money, userExp);
	Sleep(1500);
	beginMapScreen(0);
}