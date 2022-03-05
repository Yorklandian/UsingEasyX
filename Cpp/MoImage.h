#pragma once
#include <graphics.h>
#include <conio.h>
#include <string>
#include <vector>
#ifndef PI
#define PI 3.1415926535
#endif

using namespace std;

//自定义的可移动图片类，包含x，y坐标，id，旋转弧度等字段。
class MoImage
{
public:
	int id;//采用面向对象的形式时，lua中调用API不再使用ID做参数，因此id字段暂时无用
	IMAGE* img;
	int x;
	int y;

	float rotation=0;
	MoImage();
	MoImage(int id, IMAGE* img, int x, int y);
	~MoImage();

	void Move(int steps);
	void Turn(float radian);
	void SlideTo(int x, int y, double speed);

	/*static int objID;
	static vector<MoImage*> objArray;*/
};

