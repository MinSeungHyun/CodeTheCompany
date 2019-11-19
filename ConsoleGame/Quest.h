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
	char* des0[2] = { "회사를 본격적으로 운영하려면 사무실이 있어야겠지...?","사무실을 알아보러 부동산에 들어가자!" };
	quests[0] = (Quest){ 0, 1, "부동산 들어가기 (%d/%d)", des0, 100000, 100, 0, 1, CONDITION_ENTER_ESTATE };
}