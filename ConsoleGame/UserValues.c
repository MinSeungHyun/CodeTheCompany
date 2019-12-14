#include "Defines.h"

//현재 레벨의 경험치를 반환함
BigInt getExpForLevel(int level) {
	return (BigInt)(400 * (pow(level, 2)));
}

//현재 레벨에서 다음 레벨까지 가기 위한 경험치를 반환함
BigInt getTotalExpForLevel(int level) {
	return getExpForLevel(level + 1) - getExpForLevel(level);
}

//현재 레벨에서 다음레벨까지 가기 위해 모은 경험치를 반환함
BigInt getAchievedExp() {
	return userExp - getExpForLevel(level);
}

//현재 레벨부터 다음 레벨까지의 진행도를 0부터 10까지 중에 반환함
int getProgressFromExp() {
	const BigInt totalExp = getTotalExpForLevel(level);
	const BigInt achievedExp = getAchievedExp();
	return (int)((long double)achievedExp / totalExp * 10);
}

//돈과, 경험치, 레벨, 초당 들어오는 돈을 갱신함
void updateUserValues() {
	loadMoneyAndExp(&money, &userExp);
	level = (int)sqrtl((long double)(userExp / 400));

	loadMPS(&mps);
}
