#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <math.h>
#include "Cpp/MoImage.h"
#include <lua.hpp>

#define PI 3.1415926535

using namespace std;

//静态的vector和id用来保存场景中的对象，id为在数组中的索引
static vector<MoImage*> ImgArray(100);
static int id = 0;


//CreateObject函数
static int CreateObjectLua(lua_State* L)
{
	//取出三个参数
	string path = lua_tostring(L, 1);
	int nx = lua_tonumber(L, 2);
	int ny = lua_tonumber(L, 3);

	//调用API加载图片
	IMAGE* img = new IMAGE;
	loadimage(img, path.c_str(), 50, 50, true);

	//设置自定义的对象的属性，并调用API设置图片
	MoImage* image = new MoImage(id,img,nx,ny);
	ImgArray[id] = image;
	id++;

	Resize(image->img, 50, 50);
	putimage(nx, ny, image->img);

	//返回值压栈
	lua_pushnumber(L, image->id);
	return 1;
}

//Move函数，默认步长5个像素
static int MoveLua(lua_State* L)
{
	int i = lua_tonumber(L, 1);
	int n = lua_tonumber(L, 2);
	MoImage* image = ImgArray[i];
	double deltaX = sin(image->rotation);
	double deltaY = cos(image->rotation);
	for(int j=0 ;j < n; j++)
	{
		image->x -= deltaX * 10 ;
		image->y -= deltaY * 10 ;
		cleardevice();
		putimage(image->x, image->y, image->img);
		Sleep(200);
	}
	
	return 0;
}

//Turn，默认的正向是Y轴负方向，旋转角度为顺时针
static int TurnLua(lua_State* L)
{
	int i = lua_tonumber(L, 1);
	float d = lua_tonumber(L, 2);

	MoImage* image = ImgArray[i];
	image->rotation -= d;

	if(image->rotation >= PI)//控制弧度在2PI之内
	{
		image->rotation -= PI;
	}
	rotateimage(image->img, image->img, -d, BLACK, false, true);
	cleardevice();
	putimage(image->x, image->y, image->img);

	return 0;
}

static int SlideToLua(lua_State* L)
{
	int i = lua_tonumber(L, 1);
	int x = lua_tonumber(L, 2);
	int y = lua_tonumber(L, 3);
	double speed = lua_tonumber(L, 4);

	MoImage* img = ImgArray[i];
	int deltaX = x - img->x;
	int deltaY = y - img->y;
	deltaX *= speed;
	deltaY *= speed;
	if(x>=img->x)
	{
		while(x > img->x)
		{
			img->x += deltaX;
			img->y += deltaY;
			cleardevice();
			putimage(img->x, img->y, img->img);
			Sleep(30);
		}
	}
	else
	{
		while (x < img->x)
		{
			img->x += deltaX;
			img->y += deltaY;
			cleardevice();
			putimage(img->x, img->y, img->img);
			Sleep(30);
		}
	}

	return 0;
}



int main()
{
	initgraph(1280, 720);
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	//lua 注册
	lua_register(L, "CreateObject", CreateObjectLua);
	lua_register(L, "Move", MoveLua);
	lua_register(L, "Turn", TurnLua);
	lua_register(L, "SlideTo", SlideToLua);
	luaL_dofile(L, ".\\Scripts\\Lua.lua");
	lua_close(L);
	while(true)
	{
		if (_kbhit())
			break;
	}
	closegraph();
	return 0;
}


