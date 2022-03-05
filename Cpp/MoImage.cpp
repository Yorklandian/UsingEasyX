#include "MoImage.h"
#include <iostream>

//int MoImage::objID = 0;
//vector<MoImage*> MoImage::objArray(100);

MoImage::MoImage():img(new IMAGE),x(0),y(0)
{
	
}

MoImage::MoImage(int id, IMAGE* img, int x, int y):id(id),img(img),x(x),y(y)
{

}


MoImage::~MoImage()
{
	cout <<"Destructing MoImage"<<endl;
}

void MoImage::Move(int steps)
{
	double deltaX = sin(this->rotation);
	double deltaY = cos(this->rotation);
	for (int j = 0; j < steps; j++)
	{
		this->x -= deltaX * 10;
		this->y -= deltaY * 10;
		cleardevice();
		putimage(this->x, this->y, this->img);
		Sleep(200);
	}
}

void MoImage::Turn(float radian)
{
	this->rotation -= radian;
	if(this->rotation >= 2 * PI)
	{
		this->rotation -= 2 * PI;
	}
	rotateimage(img, img, -radian, BLACK, false, true);
	cleardevice();
	putimage(x, y, img);
}

void MoImage::SlideTo(int x, int y, double speed)
{
	int deltaX = x - this->x;
	int deltaY = y - this->y;
	deltaX *= speed;
	deltaY *= speed;
	if (x >= this->x)
	{
		while (x > this->x)
		{
			this->x += deltaX;
			this->y += deltaY;
			cleardevice();
			putimage(this->x, this->y, this->img);
			Sleep(30);
		}
	}
	else
	{
		while (x < this->x)
		{
			this->x += deltaX;
			this->y += deltaY;
			cleardevice();
			putimage(this->x, this->y, this->img);
			Sleep(30);
		}
	}
}
