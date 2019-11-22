#pragma once
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

inline void playBGM(char* fileName) {
	PlaySound(fileName, NULL, SND_ASYNC | SND_LOOP);
}

inline void stopBGM() {
	PlaySound(SOUND_NULL, NULL, SND_ASYNC);
}

inline void playSound(char* fileName) {
	char command[100];
	sprintf(command, "play %s", fileName);
	mciSendString(command, NULL, 0, NULL);
}
inline void stopSound(char* fileName) {
	char command[100];
	sprintf(command, "stop %s", fileName);
	mciSendString(command, NULL, 0, NULL);
}