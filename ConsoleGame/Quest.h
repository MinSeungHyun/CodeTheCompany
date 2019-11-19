#pragma once
#define Title char*
#define Description char**
#define BigInt unsigned long long
#define getDescriptionLineCount(des) (sizeof(des) / sizeof((des)[0]))

typedef struct Quest {
	int questID;
	int level;
	Title title;
	Description descriptions;
	BigInt rewardMoney;
	BigInt rewardXP;

	int progress;
	int maxProgress;
	int completeCondition;
}Quest;

#define CONDITION_ENTER_ESTATE 0
#define QUEST_COUNT 10
Quest quests[10];

inline void initQuests() {
	char* des0[2] = { "ȸ�縦 ���������� ��Ϸ��� �繫���� �־�߰���...?","�繫���� �˾ƺ��� �ε��꿡 ����!" };
	quests[0] = (Quest){ 0, 1, "�ε��� ���� (%d/%d)", des0, 100000, 100, 0, 1, CONDITION_ENTER_ESTATE };
}