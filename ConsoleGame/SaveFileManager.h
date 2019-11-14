#pragma once
#include <direct.h>

#define DIR_SAVE "saves"
#define DIR_NAME "saves/name.ctc"
#define DIR_COMPANY_NAME "saves/company_name.ctc"

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