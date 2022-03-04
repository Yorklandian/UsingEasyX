#include "MoImage.h"

#include <iostream>

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
