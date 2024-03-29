#pragma once
#ifndef DEFINES_H
#define DEFINES_H

#include "ButtonUtils/Button.h"
#include "Estate.h"
#include "ImageUtils/ImageLayer.h"
#include "Initializer.h"
#include "MouseInput.h"
#include "Quest.h"
#include "resources.h"
#include "SaveFileManager.h"
#include "SoundPlayer.h"
#include "Utils.h"

#define BigInt unsigned long long
#define QUEST_TEXT_COLOR RGB(141,110,99)
#define DEFAULT_EXP 400
#define DEFAULT_MONEY 100000
#define DEFAULT_MPS 10
#define COMPANY_NAME_MAX_LENGTH 20

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;
ImageLayer layer;

char lastName[100], firstName[100], companyName[100];
BigInt money, userExp, mps;
int level;
int isFirstOfficeEnabled, isMyBuildingEnabled, isCasinoEnabled;

//GameScreens
void beginStartScreen();
void beginEnterUserNameScreen();
void beginStoryScreen();
void beginEnterCompanyNameScreen();
void beginMapScreen(int);
void beginEstateScreen();
void beginEstateBoughtScreen(int);
void beginOfficeScreen();
void beginComputerScreen();
void beginQuestScreen();
void beginQuestDetailScreen(int);
void beginQuestCompleteScreen(int);
void beginLevelUpScreen();
void beginSettingScreen();
void beginCasinoScreen();
void beginJackpotScreen();

//UserValues
BigInt getExpForLevel(int);
BigInt getTotalExpForLevel(int);
BigInt getAchievedExp();
int getProgressFromExp();
void updateUserValues();

//Others
void mainProcess();
void initLayer();
void textPositionTester(int size, int weight, COLORREF textColor, int align, char* text);
void getBuildingImages(Image* firstOffice, Image* myBuilding, Image* casino, Image* estate);

//extern variables in ButtonImple.h
int isMouseDown;
int isMouseUp;
int isListening;

//extern varialbe in Utils.h
int isSecondClockRunning;

#endif