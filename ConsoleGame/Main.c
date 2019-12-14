/*
 * 제작 : 민승현(개발), 이혜원(디자인)
 * https://github.com/MinSeungHyun/console-game
 * 게임 이름 : Code The Company
 * 직접 회사를 경영하고, 키워갈 수 있는 게임이다.
 * 이름과 회사 이름을 입력하는 부분을 제외하고 모든 조작은 마우스로만 이루어지며,
 * 클릭할 수 있는 부분은 마우스를 올리면 강조된다.
 */

#include "Defines.h"

#define ENABLE_DEVELOPMENT_MODE 0

//게임의 메인 진행이다. (나중에 게임 다시시작할 때 필요해서 분리했다.)
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
 * mainProcess함수를 실행시킨다.
 * mainProcess에서는 게임을 하기 위한 기본 설정을 한 뒤, 시작 화면부터 차근차근 진행되는데,
 * beginMapScreen으로 메인 화면이 띄어지게된 후 부터는 사용자의 입력에 맞게 진행되어야 하므로
 * 메인 함수에서 게임이 진행되는 것이 아니라 각각의 화면에서 사용자의 입력에 맞게 진행된다.
 */
int main() {
	mainProcess();
}
