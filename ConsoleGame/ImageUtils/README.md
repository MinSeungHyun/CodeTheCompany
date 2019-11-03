# ImageUtils
* �̹��� ����� �����ֱ� ���� ��ƿ��Ƽ
* ���伥, �Ϸ���Ʈ ���� ���α׷��� ���̾� ������ �����ϸ� ����

## ����
1. 3���� ������ ��� �ڽ��� ������Ʈ�� �߰��Ѵ�.
2. 
	```c 
	//ImageLayerImple.h
	#define CONSOLE_WIDTH 180 //�ڽ��� �ܼ� ����� �°� �����Ѵ�
	#define CONSOLE_HEIGHT 48
	```

## ��� ����
* �̹��� ����
	```c
	#include <stdio.h>
	#include "ImageLayer.h"

	int main() {
		Sleep(500);

		ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
		imageLayer.initialize(&imageLayer); //�ʱ�ȭ

		Image images[3] = {
			{L"sample2.bmp", 0, 0}, //���ڿ� �տ�  L�� �� �ٿ���� �Ѵ�.
			{L"sample.bmp", 500, 500},
			{L"sample.bmp", 200, 200}
		};  //�迭�� ù ���Ұ� ���� �Ʒ� �׷�����.

		imageLayer.imageCount = 3; //images �迭�� ũ�⺸�� �۰ų� ���ƾ� �Ѵ�.
		imageLayer.images = images;

		imageLayer.renderAll(&imageLayer);

		getchar();
	}
	```

2. �̹��� ���� �����̱�
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
        
        //�ݺ��� �ȿ��� �̹����� ��ġ�� ������ ���� renderAll()
	    for(int i = 0; i < 1000; i += 3) {
		    imageLayer.images[0].x = i;
		    imageLayer.images[1].y = i;

		    imageLayer.renderAll(&imageLayer);
	    }

	    getchar();
    }
	```

---
������ �ְų� ���ǻ����� ���� �� issue �÷��ּ���.