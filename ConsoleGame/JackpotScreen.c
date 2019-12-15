#include "Defines.h"
#include <conio.h>

#define WAITING_MESSAGE "레버를 눌러주세요. (비용 30,000원)"
#define PLAING_MESSAGE "키보드의 1, 2, 3을 눌러 슬롯을 멈춰주세요!"
#define SUCCESS_MESSAGE "당첨되었습니다! %s원 획득!"
#define FAILED_MESSAGE "아쉽지만 다음 기회에~"
#define MONEY_LACK_MESSAGE "돈이 부족합니다."
#define DELAY_AFTER_FINISHED 2000

#define DEFAULT_REWARD 0
#define JACKPOT_PLAY_PRICE 30000

#define getSlotCharPositionX(slot) ((slot - 1) * 380 + 924)
#define LEVER_INDEX 3
#define JACKPOT_BUTTON_COUNT 2
#define JACKPOT_IMAGE_COUNT (JACKPOT_BUTTON_COUNT + 2)

#define SLOT_COUNT 3
#define SLOT_CHAR_COUNT 7
#define SLOT_CHANGING_DELAY 30

#define STATE_SPINNING 0
#define STATE_STOPPED 1

char* mainText = WAITING_MESSAGE;
void applyToDcInJackpot(HDC hdc) {
	printText(hdc, 1990, 75, 70, 0, RGB(255, 255, 255), TA_LEFT, commify(money));
	printText(hdc, 2680, 85, 50, 0, RGB(255, 255, 255), TA_RIGHT, "원");
	printText(hdc, 1380, 365, 70, 0, RGB(255, 255, 255), TA_CENTER, mainText);
}

char AVAILABLE_CHARS[SLOT_CHAR_COUNT][3] = { "$", "7", "@", "♠", "♣", "◆", "♥" };
BigInt REWARDS[SLOT_CHAR_COUNT] = { 100000000, 10000000, 1000000, 100000, 100000, 100000, 100000 };
int slotCharIndex[SLOT_COUNT], slotState[SLOT_COUNT];

int isGameEnd() {
	return slotState[0] == STATE_STOPPED
		&& slotState[1] == STATE_STOPPED
		&& slotState[2] == STATE_STOPPED;
}

BigInt getReward() {
	if (slotCharIndex[0] == slotCharIndex[1] && slotCharIndex[1] == slotCharIndex[2])
		return REWARDS[slotCharIndex[0]];
	return DEFAULT_REWARD;
}

void changeSlotItemThread(void* slotNumber) {
	int index = (int)slotNumber - 1;
	slotCharIndex[index] = index * 2;
	while (slotState[index] == STATE_SPINNING) {
		if (slotCharIndex[index] >= SLOT_CHAR_COUNT - 1) slotCharIndex[index] = 0;
		else slotCharIndex[index]++;
		Sleep(SLOT_CHANGING_DELAY);
	}
}

void printSlotText(HDC hdc) {
	applyToDcInJackpot(hdc);
	for (int i = 0; i < SLOT_COUNT; i++)
		printText(hdc, getSlotCharPositionX(i + 1), 780, 400, 0, RGB(0, 0, 0), TA_CENTER, AVAILABLE_CHARS[slotCharIndex[i]]);
}

void initJacpotGame() {
	layer.images[LEVER_INDEX].fileName = FILE_JACKPOT_LEVER_SPINNING;
	layer.applyToDC = printSlotText;
	mainText = PLAING_MESSAGE;
	for (int i = 0; i < SLOT_COUNT; i++) {
		slotState[i] = STATE_SPINNING;
		_beginthread(changeSlotItemThread, 0, (void*)(i + 1));
	}
}

void startJackpotGame() {
	stopButtonListener();
	initJacpotGame();

	while (1) {
		if (_kbhit()) {
			char input = _getch();
			switch (input) {
			case '1':
				slotState[0] = STATE_STOPPED;
				break;
			case '2':
				slotState[1] = STATE_STOPPED;
				break;
			case '3':
				slotState[2] = STATE_STOPPED;
				break;
			}
		}
		if (isGameEnd()) break;
		layer.renderAll(&layer);
	}

	BigInt reward = getReward();
	if (reward == 0) mainText = FAILED_MESSAGE;
	else {
		char tmp[50];
		sprintf(tmp, SUCCESS_MESSAGE, commify(reward));
		mainText = tmp;
	}
	layer.renderAll(&layer);
	Sleep(DELAY_AFTER_FINISHED);
	money += reward;
	saveMoneyAndExp(money, userExp);

	beginJackpotScreen();
}

void whenMoneyLack(void* param) {
	mainText = MONEY_LACK_MESSAGE;
	Sleep(1000);
	mainText = WAITING_MESSAGE;
}

void onButtonInJackpotClicked(Button* clickedButton) {
	char* buttonName = clickedButton->normal;
	if (buttonName == FILE_BACK_BUTTON) {
		beginCasinoScreen();
	}
	else if (buttonName == FILE_JACKPOT_LEVER_BUTTON) {
		if (money >= JACKPOT_PLAY_PRICE) {
			money -= JACKPOT_PLAY_PRICE;
			saveMoneyAndExp(money, userExp);
			startJackpotGame();
		}
		else {
			_beginthread(whenMoneyLack, 0, NULL);
		}
	}
}

void beginJackpotScreen() {
	stopButtonListener();
	Button backButton = createButton(100, 50, FILE_BACK_BUTTON, FILE_BACK_BUTTON_HOVER, FILE_BACK_BUTTON_CLICK, 2, onButtonInJackpotClicked);
	Button leverButton = createButton(2048, 434, FILE_JACKPOT_LEVER_BUTTON, FILE_JACKPOT_LEVER_BUTTON_HOVER, FILE_JACKPOT_LEVER_BUTTON_CLICK, LEVER_INDEX, onButtonInJackpotClicked);
	Button buttons[JACKPOT_BUTTON_COUNT] = { backButton, leverButton };
	Image images[JACKPOT_IMAGE_COUNT] = {
		{ FILE_JACKPOT_BACKGROUND, 0, 0 },
		{ FILE_MONEY_BACKGROUND, 1850, 50 },
		{ backButton.normal, backButton.x, backButton.y },
		{ leverButton.normal, leverButton.x, leverButton.y }
	};
	layer.images = images;
	layer.imageCount = JACKPOT_IMAGE_COUNT;
	layer.applyToDC = applyToDcInJackpot;

	mainText = WAITING_MESSAGE;

	startButtonListener(buttons, JACKPOT_BUTTON_COUNT, &layer);
}
