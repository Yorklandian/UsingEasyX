#include "MoImageRegFunc.h"
using namespace std;

int lua_create_object(lua_State* L)
{
	//取出三个参数
	string path = lua_tostring(L, 1);
	int nx = lua_tonumber(L, 2);
	int ny = lua_tonumber(L, 3);

	//调用API加载图片
	IMAGE* img = new IMAGE;
	loadimage(img, path.c_str(), 50, 50, true);

	MoImage** m = (MoImage**)lua_newuserdata(L, sizeof(MoImage*));
	*m = new MoImage(0, img, nx, ny);
	//调整
	Resize((*m)->img, 50, 50);
	putimage(nx, ny, (*m)->img);

	luaL_getmetatable(L, "MoImageClass");

	lua_setmetatable(L, -2);

	return 1;
};


//move，turn和slideTo是成员函数
int lua_move(lua_State* L)
{

	//取出成员函数的第一个参数：对象的this指针
	MoImage** m = (MoImage**)luaL_checkudata(L, 1, "MoImageClass");
	luaL_argcheck(L, m != NULL, 1, "Invalid user data");

	//取出传入的参数
	int steps = lua_tonumber(L, 2);
	(*m)->Move(steps);
	return 0;
};

int lua_turn(lua_State* L)
{
	MoImage** m = (MoImage**)luaL_checkudata(L, 1, "MoImageClass");
	luaL_argcheck(L, m != NULL, 1, "Invalid user data");

	double radian = lua_tonumber(L, 2);
	(*m)->Turn(radian);
	return 0;
};

int lua_slide_to(lua_State* L)
{
	MoImage** m = (MoImage**)luaL_checkudata(L, 1, "MoImageClass");
	luaL_argcheck(L, m != NULL, 1, "Invalid user data");

	int x = lua_tonumber(L, 2);
	int y = lua_tonumber(L, 3);
	double speed = lua_tonumber(L, 4);

	(*m)->SlideTo(x, y, speed);
	return 0;
};

int lua_aoto_gc(lua_State* L)
{
	MoImage** m = (MoImage**)luaL_checkudata(L, 1, "MoImageClass");
	luaL_argcheck(L, m != NULL, 1, "Invalid user data");
	if(m)
	{
		delete* m;
	}
	return 0;
};


//新建元表和模块
int lua_open_image_libs(lua_State* L)
{
	//新建元表
	luaL_newmetatable(L, "MoImageClass");
	//复制这个元表并放在-1
	lua_pushvalue(L, -1);
	//将-1的元表设为-2位置元表的字段
	lua_setfield(L, -2, "__index");
	//设置元表成员函数
	luaL_setfuncs(L, lua_reg_image_member_funcs, 0);

	//新建模块，仅包含create
	luaL_newlib(L, lua_reg_image_create_funcs);
	return 1;
};
