#pragma once
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

//PlaySound �Լ��� ������ ���������
inline void playBGM(char* fileName) {
	PlaySound(fileName, NULL, SND_ASYNC | SND_LOOP);
}

//�� ���������� ������� ���� ������̴� ������ ����
inline void stopBGM() {
	PlaySound(SOUND_NULL, NULL, SND_ASYNC);
}

//mci�� ����Ͽ� �Ҹ��� ����ϱ� ���� �Լ�
inline void playSound(char* fileName) {
	char command[100];
	sprintf(command, "play %s", fileName);
	mciSendString(command, NULL, 0, NULL);
}

//������̴� �Ҹ��� ���߱� ���� �Լ�
inline void stopSound(char* fileName) {
	char command[100];
	sprintf(command, "stop %s", fileName);
	mciSendString(command, NULL, 0, NULL);
}

#endif