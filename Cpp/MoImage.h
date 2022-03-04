#pragma once
#include <graphics.h>
#include <conio.h>
#include <string>
using namespace std;
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

