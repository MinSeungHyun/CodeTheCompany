#pragma once
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

//PlaySound 함수로 음악을 재생시켜줌
inline void playBGM(char* fileName) {
	PlaySound(fileName, NULL, SND_ASYNC | SND_LOOP);
}

//빈 음악파일을 재생시켜 원래 재생중이던 음악을 멈춤
inline void stopBGM() {
	PlaySound(SOUND_NULL, NULL, SND_ASYNC);
}

//mci를 사용하여 소리를 재생하기 위한 함수
inline void playSound(char* fileName) {
	char command[100];
	sprintf(command, "play %s", fileName);
	mciSendString(command, NULL, 0, NULL);
}

//재생중이던 소리를 멈추기 위한 함수
inline void stopSound(char* fileName) {
	char command[100];
	sprintf(command, "stop %s", fileName);
	mciSendString(command, NULL, 0, NULL);
}

#endif