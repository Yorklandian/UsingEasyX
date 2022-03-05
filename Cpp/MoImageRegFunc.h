#pragma once
#include <lua.hpp>
#include "MoImage.h"

int lua_create_object(lua_State* L);

int lua_move(lua_State* L);

int lua_turn(lua_State* L);

int lua_slide_to(lua_State* L);

int lua_aoto_gc(lua_State* L);


//create 函数
static const luaL_Reg lua_reg_image_create_funcs[]
{
	{"CreateObject",lua_create_object},
	{NULL,NULL}
};

//成员函数
static const luaL_Reg lua_reg_image_member_funcs[]
{
	{"Move",lua_move},
	{"Turn",lua_turn},
	{"SlideTo",lua_slide_to},
	{"__gc",lua_aoto_gc},
	{NULL,NULL}
};

int lua_open_image_libs(lua_State* L);