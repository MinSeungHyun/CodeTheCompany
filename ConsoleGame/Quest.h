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

#define CONDITION_ENTER_ESTATE 0 //�ε��� ����
#define CONDITION_BUY_OFFICE 1 //�繫�� �����ϱ�
#define CONDITION_ENTER_OFFICE 2 //�繫�� ����
#define CONDITION_APP_UPDATE 3 //�� ������Ʈ �ϱ�
#define CONDITION_OUTWORK 4 //�����ϱ�
#define CONDITION_WIDE_OFFICE 5 //�繫�� �޽İ��� ����
#define CONDITION_BETTER_COMPUTER 6 //��ǻ�� ���׷��̵� �ϱ�
#define CONDITION_BUY_CASINO_TICKET 7 //ī���� ����� ����
#define CONDITION_PLAY_JACKPOT_JUST 8 //���� ������ �÷���
#define CONDITION_PLAY_JACKPOT_LOSE 9 //���� ������ �÷��� �ؼ� ����
#define CONDITION_PLAY_JACKPOT_WIN 10 //���� ������ �÷��� �ؼ� �̱��
#define CONDITION_HIRE 11 //���� ����ϱ�
#define CONDITION_PLAY_TRICKERY_JUST 12 //�߹��� ������ �÷���
#define CONDITION_PLAY_TRICKERY_LOSE 13 //�߹��� ������ �÷��� �ؼ� ����
#define CONDITION_PLAY_TRICKERY_WIN 14 //�߹��� ������ �÷��� �ؼ� �̱��
#define CONDITION_BUY_BUILDING 15 //�� �ǹ� ����

#define QUEST_COUNT 25 //����Ʈ ����
Quest quests[QUEST_COUNT];

inline void initQuests() {
	const char* des0[2] = { "ȸ�縦 ���������� ��Ϸ��� �繫���� �־�߰���...?","�繫���� �˾ƺ��� �ε��꿡 ����!" };
	quests[0] = (Quest){ 0, 1, "�ε��� ���� (%d/%d)", des0, 100000, 100, 0, 1, CONDITION_ENTER_ESTATE };

	const char* des1[3] = { "�� �տ� 10���� �ۿ� ����...", "��ħ 10���� ¥�� �繫���� ���ݾ�?!!!","���� �� �繫���� ��������!!" };
	quests[1] = (Quest){ 1, 1, "�� ù �繫�� (%d/%d)", des1, 20000, 300, 0, 1, CONDITION_BUY_OFFICE };

	const char* des2[3] = { "���� �� �繫���� ����٤ФФФ�", "���ϰ� ����ϴ��� ���ΰ� ��� ������ ���ߴµ�... ", "���� ������!" };
	quests[2] = (Quest){ 2, 2, "�繫�� ������ (%d/%d)", des2, 30000, 400, 0, 1, CONDITION_ENTER_OFFICE };

	const char* des3[3] = { "�繫���� ������ ���������� ������ �غ���! ", "������ �繫�Ǿ��� ��ǻ�͸� ������ �� �� �ִ�! ","ȸ�縦 ����� ���� �츮 ���� ������Ʈ ����." };
	quests[3] = (Quest){ 3, 2, "������ �սô� (%d/%d)", des3, 20000, 800, 0, 1, CONDITION_APP_UPDATE };

	const char* des4[3] = { "������Ʈ�δ� ���� ���� �� �� ���ڴ°�...", "�׷�! �� ���� ���ָ� �ٴ°ž�!!!","(���ִ� �繫�Ǿ��� ��ǻ�͸� ���� �� �� �ִ�.)" };
	quests[4] = (Quest){ 4, 3, "���ָ� �ݽô� (%d/%d)", des4, 45000, 2000, 0, 1, CONDITION_OUTWORK };

	const char* des5[1] = { "�� ������Ʈ�� '3��' �غ���" };
	quests[5] = (Quest){ 5, 4, "�����ϴ� ������(1) (%d/%d)", des5, 300000, 3000, 0, 3, CONDITION_APP_UPDATE };

	const char* des6[3] = { "�Ϸ����� ���߸� �ϰ� �����ϱ� �Ӹ��� �ʹ� �����٤Ф�", "�ٸ� ITȸ����� �޽İ����� �ִ���...", "�ε��꿡 ���� �繫���� �� ĭ �� ��������!" };
	quests[6] = (Quest){ 6, 5, "�ϸ��ϴ°� �����ڷν��� ������ �ƴ��� (%d/%d)", des6, 1000000, 4000, 0, 1, CONDITION_WIDE_OFFICE };

	const char* des7[3] = { "�繫���� �ٲ�����, �� �����ϰ� ����ϰ� ���� �� �� �����͸� ����!!", "���� ���ָ� ����!!!","���� ��� ���� ���ο� �������, ���ָ� '3��'�پ��." };
	quests[7] = (Quest){ 7, 6, "���ϱ� �� ���� �繫���̳� (%d/%d)", des7, 1000000, 4500, 0,3, CONDITION_OUTWORK };

	const char* des8[1] = { "�� ������Ʈ�� '6��' �غ���" };
	quests[8] = (Quest){ 8, 7, "�����ϴ� ������(2) (%d/%d)", des8, 100000, 5000, 0,6, CONDITION_APP_UPDATE };

	const char* des9[4] = { "�׵��� ��Ƽ�� ��ǻ�� ������ �����ϴ��� �ʹ� �������...", "���� �ֽ� ��ǻ�ͷ� ����Ÿ�ڤФФ�","��ħ �ε��꿡�� �ֽ��� ��ǻ�� Ǯ��Ʈ�� �Ǵٰ� �Ѵ�!!!", "�ٷ� �ε��꿡 ���� ��������!" };
	quests[9] = (Quest){ 9, 10, "���ϱ� �� ���� �繫���̳� (%d/%d)", des9, 50000, 8000, 0,1, CONDITION_BETTER_COMPUTER };

	const char* des10[1] = { "�� ������Ʈ�� '3��' �غ���" };
	quests[10] = (Quest){ 10, 16, "�����ϴ� ������(3) (%d/%d)", des10, 300000, 8000, 0,3, CONDITION_APP_UPDATE };

	const char* des11[1] = { "���� ��� ���� ���ο� �������, ���ָ� '2��'�پ��." };
	quests[11] = (Quest){ 11, 18, "�����ϴ� ������(4-1) (%d/%d)", des11, 100000, 3000, 0,2, CONDITION_OUTWORK };

	const char* des12[1] = { "�� ������Ʈ�� '2��' �غ���" };
	quests[12] = (Quest){ 12, 18, "�����ϴ� ������(4-2) (%d/%d)", des12, 300000, 3000, 0,2, CONDITION_APP_UPDATE };

	const char* des13[4] = { "��� �����ϸ鼭 ������ ������ϱ�....", "���� ������ ��ܾ����� �ʰھ�?!?", "�ε��꿡 ���� ī���� ������� ��������!!!", "(���� ������� �ѹ� ��� ��� �̿� �� �� �ִ�!)" };
	quests[13] = (Quest){ 13, 20, "���� ���� �����ڴ� (%d/%d)", des13, 2000000, 5000, 0,1, CONDITION_BUY_CASINO_TICKET };

	const char* des14[2] = { "������� ��µ� �� �Ȱ��� �� ����!", "ī���뿡 ���� '����'������ �غ���" };
	quests[14] = (Quest){ 14, 20, "���� ����Ƥ����� (%d/%d)", des14, 777777, 6789, 0,1, CONDITION_PLAY_JACKPOT_JUST };

	const char* des15[1] = { "ī���뿡�� '����'������ �ؼ� 7�� ���� �Ҿ��" };
	quests[15] = (Quest){ 15, 21, "���� ����� ��! (%d/%d)", des15, 99999, 9999, 0,7, CONDITION_PLAY_JACKPOT_LOSE };

	const char* des16[1] = { "ī���뿡�� '����'������ �ؼ� 7�� ���� ����" };
	quests[16] = (Quest){ 16, 21, "���� �̱⳪ (%d/%d)", des16, 77777, 7201, 0,7, CONDITION_PLAY_JACKPOT_WIN };

	const char* des17[3] = { "���ڿ��� ������� ������� �Ҿ�������� ���� �� ����...", "���� �ٽ� �������� ���ư��ڤФФ�",  "�� ������Ʈ�� '2��' �غ���" };
	quests[17] = (Quest){ 17, 22, "�ٽ� ��������(1) (%d/%d)", des17, 1000000, 5000, 0,2, CONDITION_APP_UPDATE };

	const char* des18[3] = { "���ڿ��� ������� ������� �Ҿ�������� ���� �� ����...", "���� �ٽ� �������� ���ư��ڤФФ�",  "���� ��� �������ο� �������, ���ָ� '1��' �پ��" };
	quests[18] = (Quest){ 18, 22, "�ٽ� ��������(2) (%d/%d)", des18, 1000000, 7000, 0,1, CONDITION_OUTWORK };

	const char* des19[2] = { "ȸ�簡 ���� Ŀ���ϱ� ���� ȥ�� ���ϱⰡ ���ſ�����...", "��ǻ�Ϳ� �� ���α��� ����Ʈ���� ������ '1��' ����غ���!" };
	quests[19] = (Quest){ 19, 30, "�Բ� ���� ����� ã���ϴ�(1) (%d/%d)", des19, 1000000, 20000, 0,1, CONDITION_HIRE };

	const char* des20[3] = { "������ ����ϴϱ� ȿ���� �ð� ���� �� �� �����ִ°� ������?!", "�����̳ʵ� ����ϰ�, �����ڵ� ����ϰ�, ȸ�赵.. �� ����ϰھ�!!!", "��ǻ�Ϳ� �� ���α��� ����Ʈ���� ������ '4��' ����غ���!" };
	quests[20] = (Quest){ 20, 35, "�Բ� ���� ����� ã���ϴ�(2) (%d/%d)", des20, 1000000, 10000, 0,4, CONDITION_HIRE };

	const char* des21[3] = { "ī���뿡 '�߹���'��� ������ ���� ���Դٰ� �Ѵ�!!!", "�� �Ȱ��� �� ����...����", "ī���뿡�� '�߹���' ������ �غ���" };
	quests[21] = (Quest){ 21, 40, "������ �߹��� (%d/%d)", des21, 777777, 32400, 0,1, CONDITION_PLAY_TRICKERY_JUST };

	const char* des22[1] = { "ī���뿡�� '�߹���'������ �ؼ� 7�� ���� �Ҿ��" };
	quests[22] = (Quest){ 22, 41, "���� ����� ��!(2) (%d/%d)", des22, 99999, 33000, 0,7, CONDITION_PLAY_TRICKERY_LOSE };

	const char* des23[1] = { "ī���뿡�� '�߹���'������ �ؼ� 7�� ���� ����" };
	quests[23] = (Quest){ 23, 42, "���� �̱⳪ (%d/%d)", des23, 7777777, 30000, 0,7, CONDITION_PLAY_TRICKERY_WIN };

	const char* des24[3] = { "ȸ�簡 �̷��� ���� �Ǵµ�...", "�ٸ� ������ó�� ���� ������ ��߰ڴ�!!!", "���� ���� �ε������� ���� ������ ��������!!!!!" };
	quests[24] = (Quest){ 24, 50, "�ǹ��ְ� �ǰ�;� (%d/%d)", des24, 37777, 0555555, 0, 1, CONDITION_BUY_BUILDING };

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