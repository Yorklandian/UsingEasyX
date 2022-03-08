#include <iostream>
#include <lua.hpp>
#include "MoImage.h"
#include "MoImageRegFunc.h"

using namespace std;
static const luaL_Reg lua_reg_libs[]
{
	{"base",luaopen_base},
	{"MoImage",lua_open_image_libs},
	{NULL,NULL}
};

int main()
{
	initgraph(1280, 720, EW_SHOWCONSOLE);

	lua_State* L = luaL_newstate();
	const luaL_Reg* lua_reg = lua_reg_libs;
	//зЂВс
	for(;lua_reg->func;++lua_reg)
	{
		luaL_requiref(L, lua_reg->name, lua_reg->func, 1);
		lua_pop(L, 1);
	}

	//luaL_dofile(L, ".\\Scripts\\lua2.lua");
	luaL_openlibs(L);
	int ret=luaL_loadfile(L, ".\\Scripts\\lua2.lua");
	if(ret)
	{
		cout << "file load err" << endl;
	}
	else
	{
		cout << "file loaded" << endl;
	}
	int status=lua_pcall(L, 0, 0, 0);
	if(status!=LUA_OK)
	{
		cout << "something wrong" << endl;
		string err = lua_tostring(L, -1);
		cout << err << endl;
	}
	

	while (true)
	{
		if(_kbhit())
		{
			lua_close(L);
			closegraph();
		}
	}
	return 0;
}