#pragma once
#include <graphics.h>
#include <conio.h>
#include <string>
using namespace std;

//自定义的可移动图片类，包含x，y坐标，id，旋转弧度等字段。
class MoImage
{
public:
	int id;
	IMAGE* img;
	int x;
	int y;

	float rotation=0;
	MoImage();
	MoImage(int id, IMAGE* img, int x, int y);
	~MoImage();
};

