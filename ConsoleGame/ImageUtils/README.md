# ImageUtils
* 이미지 출력을 도와주기 위한 유틸리티
* 포토샵, 일러스트 같은 프로그램의 레이어 개념을 생각하면 편함

## 사용법
1. 3개의 파일을 모두 자신의 프로젝트에 추가한다.
2. 
	```c 
	//ImageLayerImple.h
	#define CONSOLE_WIDTH 180 //자신의 콘솔 사이즈에 맞게 설정한다
	#define CONSOLE_HEIGHT 48
	```

## 사용 예시
* 이미지 띄우기
	```c
	#include <stdio.h>
	#include "ImageLayer.h"

	int main() {
		Sleep(500);

		ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
		imageLayer.initialize(&imageLayer); //초기화

		Image images[3] = {
			{L"sample2.bmp", 0, 0}, //문자열 앞에  L을 꼭 붙여줘야 한다.
			{L"sample.bmp", 500, 500},
			{L"sample.bmp", 200, 200}
		};  //배열의 첫 원소가 가장 아래 그려진다.

		imageLayer.imageCount = 3; //images 배열의 크기보다 작거나 같아야 한다.
		imageLayer.images = images;

		imageLayer.renderAll(&imageLayer);

		getchar();
	}
	```

2. 이미지 띄우고 움직이기
	```c
    #include <stdio.h>
    #include "ImageLayer.h"

    int main() {
	    Sleep(500);

	    ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	    imageLayer.initialize(&imageLayer);

	    Image images[3] = {
		    {L"sample2.bmp", 0, 0},
		    {L"sample.bmp", 500, 500},
		    {L"sample.bmp", 200, 200},
	    };

	    imageLayer.imageCount = 3;
	    imageLayer.images = images;
        
        //반복문 안에서 이미지의 위치를 조정한 다음 renderAll()
	    for(int i = 0; i < 1000; i += 3) {
		    imageLayer.images[0].x = i;
		    imageLayer.images[1].y = i;

		    imageLayer.renderAll(&imageLayer);
	    }

	    getchar();
    }
	```

---
오류가 있거나 건의사항이 있을 시 issue 올려주세요.