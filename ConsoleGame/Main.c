/*
 * ���� : �ν���(����), ������(������)
 * https://github.com/MinSeungHyun/console-game
 * ���� �̸� : Code The Company
 * ���� ȸ�縦 �濵�ϰ�, Ű���� �� �ִ� �����̴�.
 * �̸��� ȸ�� �̸��� �Է��ϴ� �κ��� �����ϰ� ��� ������ ���콺�θ� �̷������,
 * Ŭ���� �� �ִ� �κ��� ���콺�� �ø��� �����ȴ�.
 */

#include "Defines.h"

#define ENABLE_DEVELOPMENT_MODE 0

//������ ���� �����̴�. (���߿� ���� �ٽý����� �� �ʿ��ؼ� �и��ߴ�.)
void mainProcess() {
	initialize();
	_mkdir(DIR_SAVE);
	initLayer();
	initQuests();
	initEstateItems();
	Sleep(300);

	if (ENABLE_DEVELOPMENT_MODE) {
		beginMapScreen(0);
	}
	else {
		beginStartScreen();
		Sleep(500);

		if (!isFileExist(DIR_NAME)) {
			beginEnterUserNameScreen();
			Sleep(500);
		}
		loadName(lastName, firstName);

		if (!isFileExist(DIR_COMPANY_NAME)) {
			beginStoryScreen();
			Sleep(1000);
		}
		beginMapScreen(1);
	}
}

/*
 * mainProcess�Լ��� �����Ų��.
 * mainProcess������ ������ �ϱ� ���� �⺻ ������ �� ��, ���� ȭ����� �������� ����Ǵµ�,
 * beginMapScreen���� ���� ȭ���� ������Ե� �� ���ʹ� ������� �Է¿� �°� ����Ǿ�� �ϹǷ�
 * ���� �Լ����� ������ ����Ǵ� ���� �ƴ϶� ������ ȭ�鿡�� ������� �Է¿� �°� ����ȴ�.
 */
int main() {
	mainProcess();
}
