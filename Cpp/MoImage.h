#pragma once
#include <graphics.h>
#include <conio.h>
#include <string>
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
};

