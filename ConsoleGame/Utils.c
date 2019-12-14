#include "Defines.h"

//이미지 레이어 객체를 초기화 해주는 함수
void initLayer() {
	layer = DEFAULT_IMAGE_LAYER;
	layer.initialize(&layer);
	layer.transparentColor = RGB(0, 255, 25);
}

//imagePositionTester처럼 적절한 글씨 위치를 찾기 위해 만든 함수
void textPositionTester(int size, int weight, COLORREF textColor, int align, char* text) {
	while (1) {
		if (isMouseClicked()) {
			const COORD position = getMousePosition();
			layer.renderAll(&layer);
			printText(layer._consoleDC, position.X, position.Y, size, weight, textColor, align, text);

			gotoXY(0, 0);
			printf("%5d %5d", position.X, position.Y);
		}
	}
}

//빌딩의 이미지들을 잠금해제 상태에 맞게 만들어주는 함수
void getBuildingImages(Image* firstOffice, Image* myBuilding, Image* casino, Image* estate) {
	if (isFirstOfficeEnabled) *firstOffice = (Image){ FILE_FIRST_OFFICE, 370, 370 };
	else *firstOffice = (Image){ FILE_FIRST_OFFICE_LOCKED, 370, 370 };

	if (isMyBuildingEnabled) *myBuilding = (Image){ FILE_MY_BUILDING, 800, 400 };
	else *myBuilding = (Image){ FILE_MY_BUILDING_LOCKED, 800, 400 };

	if (isCasinoEnabled) *casino = (Image){ FILE_CASINO, 2094, 688 };
	else *casino = (Image){ FILE_CASINO_LOCKED, 2094, 688 };

	*estate = (Image){ FILE_ESTATE, 1368, 284 };
}