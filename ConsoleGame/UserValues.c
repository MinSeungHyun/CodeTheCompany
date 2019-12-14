#include "Defines.h"

//���� ������ ����ġ�� ��ȯ��
BigInt getExpForLevel(int level) {
	return (BigInt)(400 * (pow(level, 2)));
}

//���� �������� ���� �������� ���� ���� ����ġ�� ��ȯ��
BigInt getTotalExpForLevel(int level) {
	return getExpForLevel(level + 1) - getExpForLevel(level);
}

//���� �������� ������������ ���� ���� ���� ����ġ�� ��ȯ��
BigInt getAchievedExp() {
	return userExp - getExpForLevel(level);
}

//���� �������� ���� ���������� ���൵�� 0���� 10���� �߿� ��ȯ��
int getProgressFromExp() {
	const BigInt totalExp = getTotalExpForLevel(level);
	const BigInt achievedExp = getAchievedExp();
	return (int)((long double)achievedExp / totalExp * 10);
}

//����, ����ġ, ����, �ʴ� ������ ���� ������
void updateUserValues() {
	loadMoneyAndExp(&money, &userExp);
	level = (int)sqrtl((long double)(userExp / 400));

	loadMPS(&mps);
}
