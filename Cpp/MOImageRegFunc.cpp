#include "MoImageRegFunc.h"
using namespace std;

int lua_create_object(lua_State* L)
{
	//ȡ����������
	string path = lua_tostring(L, 1);
	int nx = lua_tonumber(L, 2);
	int ny = lua_tonumber(L, 3);

	//����API����ͼƬ
	IMAGE* img = new IMAGE;
	loadimage(img, path.c_str(), 50, 50, true);

	MoImage** m = (MoImage**)lua_newuserdata(L, sizeof(MoImage*));
	*m = new MoImage(0, img, nx, ny);
	//����
	Resize((*m)->img, 50, 50);
	putimage(nx, ny, (*m)->img);

	luaL_getmetatable(L, "MoImageClass");

	lua_setmetatable(L, -2);

	return 1;
};


//move��turn��slideTo�ǳ�Ա����
int lua_move(lua_State* L)
{

	//ȡ����Ա�����ĵ�һ�������������thisָ��
	MoImage** m = (MoImage**)luaL_checkudata(L, 1, "MoImageClass");
	luaL_argcheck(L, m != NULL, 1, "Invalid user data");

	//ȡ������Ĳ���
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


//�½�Ԫ���ģ��
int lua_open_image_libs(lua_State* L)
{
	//�½�Ԫ��
	luaL_newmetatable(L, "MoImageClass");
	//�������Ԫ������-1
	lua_pushvalue(L, -1);
	//��-1��Ԫ����Ϊ-2λ��Ԫ����ֶ�
	lua_setfield(L, -2, "__index");
	//����Ԫ���Ա����
	luaL_setfuncs(L, lua_reg_image_member_funcs, 0);

	//�½�ģ�飬������create
	luaL_newlib(L, lua_reg_image_create_funcs);
	return 1;
};
