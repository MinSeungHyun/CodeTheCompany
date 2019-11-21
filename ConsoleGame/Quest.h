#pragma once
#include <direct.h>
#define Title char*
#define Description const char**
#define BigInt unsigned long long
#define getDescriptionLineCount(des) (sizeof(des) / sizeof((des)[0]))

typedef struct Quest {
	int questID;
	int level;
	const Title title;
	Description descriptions;
	BigInt rewardMoney;
	BigInt rewardXP;

	int progress;
	int maxProgress;
	int completeCondition;

	int isActivated;
}Quest;

inline void loadAllQuestsProgress();
inline int updateAllQuestsActiveState(int);

#define CONDITION_ENTER_ESTATE 0 //부동산 들어가기
#define CONDITION_BUY_OFFICE 1 //사무실 구입하기
#define CONDITION_ENTER_OFFICE 2 //사무실 들어가기
#define CONDITION_APP_UPDATE 3 //앱 업데이트 하기
#define CONDITION_OUTWORK 4 //외주하기
#define CONDITION_WIDE_OFFICE 5 //사무실 휴식공간 구입
#define CONDITION_BETTER_COMPUTER 6 //컴퓨터 업그레이드 하기
#define CONDITION_BUY_CASINO_TICKET 7 //카지노 입장권 구입
#define CONDITION_PLAY_JACKPOT_JUST 8 //잭팟 게임을 플레이
#define CONDITION_PLAY_JACKPOT_LOSE 9 //잭팟 게임을 플레이 해서 지기
#define CONDITION_PLAY_JACKPOT_WIN 10 //잭팟 게임을 플레이 해서 이기기
#define CONDITION_HIRE 11 //직원 고용하기
#define CONDITION_PLAY_TRICKERY_JUST 12 //야바위 게임을 플레이
#define CONDITION_PLAY_TRICKERY_LOSE 13 //야바위 게임을 플레이 해서 지기
#define CONDITION_PLAY_TRICKERY_WIN 14 //야바위 게임을 플레이 해서 이기기
#define CONDITION_BUY_BUILDING 15 //내 건물 구입

#define QUEST_COUNT 25 //퀘스트 개수
Quest quests[QUEST_COUNT];

inline void initQuests() {
	const char* des0[2] = { "회사를 본격적으로 운영하려면 사무실이 있어야겠지...?","사무실을 알아보러 부동산에 들어가자!" };
	quests[0] = (Quest){ 0, 1, "부동산 들어가기 (%d/%d)", des0, 100000, 100, 0, 1, CONDITION_ENTER_ESTATE };

	const char* des1[3] = { "내 손엔 10만원 밖에 없다...", "마침 10만원 짜리 사무실이 있잖아?!!!","빨리 저 사무실을 구매하자!!" };
	quests[1] = (Quest){ 1, 1, "내 첫 사무실 (%d/%d)", des1, 20000, 300, 0, 1, CONDITION_BUY_OFFICE };

	const char* des2[3] = { "드디어 내 사무실이 생겼다ㅠㅠㅠㅠ", "급하게 계약하느라 내부가 어떤지 보지도 못했는데... ", "당장 들어가보자!" };
	quests[2] = (Quest){ 2, 2, "사무실 집들이 (%d/%d)", des2, 30000, 400, 0, 1, CONDITION_ENTER_OFFICE };

	const char* des3[3] = { "사무실을 샀으니 본격적으로 개발을 해보자! ", "개발은 사무실안의 컴퓨터를 누르면 할 수 있다! ","회사를 세우게 해준 우리 앱을 업데이트 하자." };
	quests[3] = (Quest){ 3, 2, "개발을 합시다 (%d/%d)", des3, 20000, 800, 0, 1, CONDITION_APP_UPDATE };

	const char* des4[3] = { "업데이트로는 돈을 빨리 벌 수 없겠는걸...", "그래! 앱 개발 외주를 뛰는거야!!!","(외주는 사무실안의 컴퓨터를 눌러 할 수 있다.)" };
	quests[4] = (Quest){ 4, 3, "외주를 뜁시다 (%d/%d)", des4, 45000, 2000, 0, 1, CONDITION_OUTWORK };

	const char* des5[1] = { "앱 업데이트를 '3번' 해보자" };
	quests[5] = (Quest){ 5, 4, "열일하는 개발자(1) (%d/%d)", des5, 300000, 3000, 0, 3, CONDITION_APP_UPDATE };

	const char* des6[3] = { "하루종일 개발만 하고 있으니까 머리가 너무 아프다ㅠㅠ", "다른 IT회사들은 휴식공간도 있던데...", "부동산에 가서 사무실을 한 칸 더 구매하자!" };
	quests[6] = (Quest){ 6, 5, "일만하는건 개발자로써의 도리가 아니지 (%d/%d)", des6, 1000000, 4000, 0, 1, CONDITION_WIDE_OFFICE };

	const char* des7[3] = { "사무실을 바꿨으니, 더 쾌적하고 편안하게 일을 할 수 있을것만 같다!!", "당장 외주를 뛰자!!!","외주 계약 성공 여부에 상관없이, 외주를 '3번'뛰어보자." };
	quests[7] = (Quest){ 7, 6, "일하기 딱 좋은 사무실이네 (%d/%d)", des7, 1000000, 4500, 0,3, CONDITION_OUTWORK };

	const char* des8[1] = { "앱 업데이트를 '6번' 해보자" };
	quests[8] = (Quest){ 8, 7, "열일하는 개발자(2) (%d/%d)", des8, 100000, 5000, 0,6, CONDITION_APP_UPDATE };

	const char* des9[4] = { "그동안 펜티엄 컴퓨터 가지고 개발하느라 너무 힘들었다...", "이젠 최신 컴퓨터로 갈아타자ㅠㅠㅠ","마침 부동산에서 최신형 컴퓨터 풀세트를 판다고 한다!!!", "바로 부동산에 가서 구매하자!" };
	quests[9] = (Quest){ 9, 10, "일하기 딱 좋은 사무실이네 (%d/%d)", des9, 50000, 8000, 0,1, CONDITION_BETTER_COMPUTER };

	const char* des10[1] = { "앱 업데이트를 '3번' 해보자" };
	quests[10] = (Quest){ 10, 16, "열일하는 개발자(3) (%d/%d)", des10, 300000, 8000, 0,3, CONDITION_APP_UPDATE };

	const char* des11[1] = { "외주 계약 성공 여부에 상관없이, 외주를 '2번'뛰어보자." };
	quests[11] = (Quest){ 11, 18, "열일하는 개발자(4-1) (%d/%d)", des11, 100000, 3000, 0,2, CONDITION_OUTWORK };

	const char* des12[1] = { "앱 업데이트를 '2번' 해보자" };
	quests[12] = (Quest){ 12, 18, "열일하는 개발자(4-2) (%d/%d)", des12, 300000, 3000, 0,2, CONDITION_APP_UPDATE };

	const char* des13[4] = { "계속 개발하면서 열심히 살았으니까....", "이제 여가도 즐겨야하지 않겠어?!?", "부동산에 가서 카지노 입장권을 구입하자!!!", "(조금 비싸지만 한번 사면 평생 이용 할 수 있다!)" };
	quests[13] = (Quest){ 13, 20, "돈도 많이 벌었겠다 (%d/%d)", des13, 2000000, 5000, 0,1, CONDITION_BUY_CASINO_TICKET };

	const char* des14[2] = { "입장권을 샀는데 또 안가볼 수 없지!", "카지노에 들어가서 '잭팟'게임을 해보자" };
	quests[14] = (Quest){ 14, 20, "도박 가즈아ㅏㅏㅏ (%d/%d)", des14, 777777, 6789, 0,1, CONDITION_PLAY_JACKPOT_JUST };

	const char* des15[1] = { "카지노에서 '잭팟'게임을 해서 7번 돈을 잃어보자" };
	quests[15] = (Quest){ 15, 21, "묻고 더블로 가! (%d/%d)", des15, 99999, 9999, 0,7, CONDITION_PLAY_JACKPOT_LOSE };

	const char* des16[1] = { "카지노에서 '잭팟'게임을 해서 7번 돈을 얻어보자" };
	quests[16] = (Quest){ 16, 21, "누가 이기나 (%d/%d)", des16, 77777, 7201, 0,7, CONDITION_PLAY_JACKPOT_WIN };

	const char* des17[3] = { "도박에만 빠져살면 전재산을 잃어버릴수도 있을 것 같다...", "이제 다시 현생으로 돌아가자ㅠㅠㅠ",  "앱 업데이트를 '2번' 해보자" };
	quests[17] = (Quest){ 17, 22, "다시 현생으로(1) (%d/%d)", des17, 1000000, 5000, 0,2, CONDITION_APP_UPDATE };

	const char* des18[3] = { "도박에만 빠져살면 전재산을 잃어버릴수도 있을 것 같다...", "이제 다시 현생으로 돌아가자ㅠㅠㅠ",  "외주 계약 성공여부에 상관없이, 외주를 '1번' 뛰어보자" };
	quests[18] = (Quest){ 18, 22, "다시 현생으로(2) (%d/%d)", des18, 1000000, 7000, 0,1, CONDITION_OUTWORK };

	const char* des19[2] = { "회사가 점점 커지니까 이제 혼자 일하기가 버거워진다...", "컴퓨터에 들어가 구인구직 사이트에서 직원을 '1명' 고용해보자!" };
	quests[19] = (Quest){ 19, 30, "함께 일할 사람을 찾습니다(1) (%d/%d)", des19, 1000000, 20000, 0,1, CONDITION_HIRE };

	const char* des20[3] = { "직원을 고용하니까 효율도 늘고 돈도 더 잘 벌수있는것 같은걸?!", "디자이너도 고용하고, 개발자도 고용하고, 회계도.. 다 고용하겠어!!!", "컴퓨터에 들어가 구인구직 사이트에서 직원을 '4명' 고용해보자!" };
	quests[20] = (Quest){ 20, 35, "함께 일할 사람을 찾습니다(2) (%d/%d)", des20, 1000000, 10000, 0,4, CONDITION_HIRE };

	const char* des21[3] = { "카지노에 '야바위'라는 게임이 새로 들어왔다고 한다!!!", "또 안가볼 수 없지...ㅎㅎ", "카지노에서 '야바위' 게임을 해보자" };
	quests[21] = (Quest){ 21, 40, "위험한 야바위 (%d/%d)", des21, 777777, 32400, 0,1, CONDITION_PLAY_TRICKERY_JUST };

	const char* des22[1] = { "카지노에서 '야바위'게임을 해서 7번 돈을 잃어보자" };
	quests[22] = (Quest){ 22, 41, "묻고 더블로 가!(2) (%d/%d)", des22, 99999, 33000, 0,7, CONDITION_PLAY_TRICKERY_LOSE };

	const char* des23[1] = { "카지노에서 '야바위'게임을 해서 7번 돈을 얻어보자" };
	quests[23] = (Quest){ 23, 42, "누가 이기나 (%d/%d)", des23, 7777777, 30000, 0,7, CONDITION_PLAY_TRICKERY_WIN };

	const char* des24[3] = { "회사가 이렇게 많이 컸는데...", "다른 대기업들처럼 나도 빌딩을 사야겠다!!!", "지금 당장 부동산으로 가서 빌딩을 구매하자!!!!!" };
	quests[24] = (Quest){ 24, 50, "건물주가 되고싶어 (%d/%d)", des24, 37777, 0555555, 0, 1, CONDITION_BUY_BUILDING };

	loadAllQuestsProgress();
}

#define DIR_QUESTS_FOLDER "saves/quests"
#define DIR_QUESTS "saves/quests/%d.ctc"

inline void saveQuestsProgress(Quest quest) {
	char dirName[30];
	sprintf(dirName, DIR_QUESTS, quest.questID);
	FILE* file = fopen(dirName, "w");
	fprintf(file, "%d", quest.progress);
	fclose(file);
}

inline void saveAllQuestsProgress() {
	_mkdir(DIR_QUESTS_FOLDER);

	for (int i = 0; i < QUEST_COUNT; i++) {
		saveQuestsProgress(quests[i]);
	}
}

inline int loadQuestProgress(Quest* quest) {
	char dirName[30];
	sprintf(dirName, DIR_QUESTS, quest->questID);
	FILE* file = fopen(dirName, "r");
	if (file == NULL) return 0;
	fscanf(file, "%d", &quest->progress);
	fclose(file);
	return 1;
}

inline void loadAllQuestsProgress() {
	char dirName[30];
	sprintf(dirName, DIR_QUESTS, quests[0].questID);
	if (!isFileExist(dirName)) saveAllQuestsProgress();

	for (int i = 0; i < QUEST_COUNT; i++) {
		loadQuestProgress(&quests[i]);
	}
}

inline int isQuestCompleted(Quest quest) {
	return quest.progress >= quest.maxProgress;
}

inline int isQuestNotCompleted(Quest quest) {
	return !isQuestCompleted(quest);
}

inline int isQuestUnlocked(Quest quest, int level) {
	return level >= quest.level;
}

inline int updateQuestActiveState(Quest* quest, int level) {
	quest->isActivated = isQuestNotCompleted(*quest) && isQuestUnlocked(*quest, level);
	return quest->isActivated;
}

inline int updateAllQuestsActiveState(int level) {
	int activatedQuestCount = 0;
	for (int i = 0; i < QUEST_COUNT; i++) {
		if (updateQuestActiveState(&quests[i], level))
			activatedQuestCount++;
	}
	return activatedQuestCount;
}