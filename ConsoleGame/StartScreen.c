#include "Defines.h"

//���� ȭ�鿡 �ִ� ��ư�� Ŭ���Ǿ��� �� ȣ���
void onButtonInStartScreenClicked(Button* clickedButton) {
	playSound(SOUND_BUTTON_CLICK);
	if (clickedButton->normal == FILE_START_BUTTON) {
		layer.fadeOut(&layer, NULL);
		stopButtonListener();
	}
}

//����ȭ���� ������
void beginStartScreen() {
	playBGM(SOUND_START_BGM);
	const Button startButton = createButton(1114, 1150, FILE_START_BUTTON, FILE_START_BUTTON_HOVER, FILE_START_BUTTON_CLICK, 2, onButtonInStartScreenClicked);
	Button buttons[1] = { startButton };

	Image titleImages[3] = {
		{FILE_TITLE, 0, 0},
		{FILE_TITLE_TEXT, 638, 134},
		{startButton.normal, startButton.x, startButton.y}
	};
	layer.images = titleImages;
	layer.imageCount = 3;
	layer.renderAll(&layer);

	startButtonListener(buttons, 1, &layer);
	stopBGM();
}