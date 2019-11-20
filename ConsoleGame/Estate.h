#pragma once
#define BigInt unsigned long long

typedef struct {
	char* itemName;
	BigInt price;
	int unlockLevel;
}EstateItem;

#define ESTATE_ITEM_COUNT 6
EstateItem estateItems[ESTATE_ITEM_COUNT];

#define ESTATE_ITEM_FIRST_OFFICE "첫 사무실"
#define ESTATE_ITEM_EXTEND_OFFICE "사무실 확장"
#define ESTATE_ITEM_UPGRADE_COMPUTER "사무실 컴퓨터 업그레이드"
#define ESTATE_ITEM_CASINO "도박장 입장권"
#define ESTATE_ITEM_MY_BUILDING "내 빌딩"

inline void initEstateItems() {
	estateItems[0] = (EstateItem){ ESTATE_ITEM_FIRST_OFFICE, 100000, 0 };
	estateItems[1] = (EstateItem){ ESTATE_ITEM_EXTEND_OFFICE, 150000, 5 };
	estateItems[3] = (EstateItem){ ESTATE_ITEM_UPGRADE_COMPUTER, 3000000, 10 };
	estateItems[4] = (EstateItem){ ESTATE_ITEM_CASINO, 7777777, 20 };
	estateItems[5] = (EstateItem){ ESTATE_ITEM_MY_BUILDING, 100000000000, 50 };
}