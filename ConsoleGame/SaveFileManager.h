#pragma once
#include <direct.h>

#define DIR_SAVE "saves"
#define DIR_NAME "saves/name.ctc"
#define DIR_COMPANY_NAME "saves/company_name.ctc"
#define DIR_MONEY_AND_EXP "saves/money_exp.ctc"
#define DIR_BUILDING_STATE "saves/building_state.ctc"
#define DIR_MPS "saves/mps.ctc"

inline void saveName(char* lastName, char* firstName) {
	_mkdir(DIR_SAVE);

	FILE* file = fopen(DIR_NAME, "w");
	fprintf(file, "%s %s", lastName, firstName);
	fclose(file);
}

inline int loadName(char* lastName, char* firstName) {
	FILE* file = fopen(DIR_NAME, "r");
	if (file == NULL) return 0;
	fscanf(file, "%s %s", lastName, firstName);
	fclose(file);
	return 1;
}

inline void saveCompanyName(char* companyName) {
	FILE* file = fopen(DIR_COMPANY_NAME, "w");
	fprintf(file, "%s", companyName);
	fclose(file);
}

inline int loadCompanyName(char* companyName) {
	FILE* file = fopen(DIR_COMPANY_NAME, "r");
	if (file == NULL) return 0;
	fscanf(file, "%s", companyName);
	fclose(file);
	return 1;
}

inline void saveMoneyAndExp(unsigned long long money, unsigned long long exp) {
	FILE* file = fopen(DIR_MONEY_AND_EXP, "w");
	fprintf(file, "%lld %lld", money, exp);
	fclose(file);
}

inline int loadMoneyAndExp(unsigned long long* money, unsigned long long* exp) {
	FILE* file = fopen(DIR_MONEY_AND_EXP, "r");
	if (file == NULL) return 0;
	fscanf(file, "%lld %lld", money, exp);
	fclose(file);
	return 1;
}

inline void saveBuildingState(int firstOffice, int myBuilding, int casino) {
	FILE* file = fopen(DIR_BUILDING_STATE, "w");
	fprintf(file, "%d %d %d", firstOffice, myBuilding, casino);
	fclose(file);
}

inline int loadBuildingState(int* firstOffice, int* myBuilding, int* casino) {
	FILE* file = fopen(DIR_BUILDING_STATE, "r");
	if (file == NULL) return 0;
	fscanf(file, "%d %d %d", firstOffice, myBuilding, casino);
	fclose(file);
	return 1;
}

inline void saveMPS(unsigned long long mps) {
	FILE* file = fopen(DIR_MPS, "w");
	fprintf(file, "%lld", mps);
	fclose(file);
}

inline int loadMPS(unsigned long long* mps) {
	FILE* file = fopen(DIR_MPS, "r");
	if (file == NULL) return 0;
	fscanf(file, "%lld", mps);
	fclose(file);
	return 1;
}
