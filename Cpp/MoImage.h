#pragma once
#include <graphics.h>
#include <conio.h>
#include <string>
#ifndef PI
#define PI 3.1415926535
#endif

using namespace std;

//�Զ���Ŀ��ƶ�ͼƬ�࣬����x��y���꣬id����ת���ȵ��ֶΡ�
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

	void Move(int steps);
	void Turn(float radian);
	void SlideTo(int x, int y, double speed);

};

