## ImageUtils
* 다운로드 주소 : http://bitly.kr/rfsK78G 
* 이미지 출력을 도와주기 위한 유틸리티
* 포토샵, 일러스트 같은 프로그램의 레이어 개념을 생각하면 편함
* Visual Studio로는 테스트 되었지만 다른 IDE는 아직 안해봤습니다.

## 사용법
1. 3개의 파일을 모두 자신의 프로젝트에 추가한다. (헤더파일, 이미지, 메인 파일이 모두 같은 폴더에 있어야 함)
2. ImageLayerImple.h를 수정한다.
	```c 
	//ImageLayerImple.h
	#define CONSOLE_WIDTH 180 //자신의 콘솔 사이즈에 맞게 설정한다.
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
			{L"sample2.bmp", 0, 0, 2}, //{이미지 이름, 시작 x좌표, 시작 y좌표, 크기 배율(쓰지 않으면 기본값인 16이 들어감)} 
			{L"sample.bmp", 500, 500}, //문자열 앞에  L을 꼭 붙여줘야 한다.
			{L"sample.bmp", 200, 200}
		}; //배열의 첫 원소가 가장 아래 그려진다.

		imageLayer.imageCount = 3; //images 배열의 크기보다 작거나 같아야 한다.
		imageLayer.images = images;

		imageLayer.renderAll(&imageLayer);

		getchar();
	}
	```

* 이미지 띄우고 움직이기
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

## 고급 사용법
1. 이미지 출력이 되지 않으면 이미지 이름 앞에 붙는  L을 지우고 해보세요.

2. 기본적으로 검정색(RGB(0, 0, 0))이 투명색으로 설정 되있는데 투명색을 수정하고 싶다면
```layer.transparentColor = RGB(0, 0, 0); //자신이 원하는 색``` 으로 설정하면 됩니다.

---
오류가 있거나 건의사항이 있을 시 issue 올려주세요.
