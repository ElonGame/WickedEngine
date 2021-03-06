#pragma once
#include "wiLua.h"
#include "wiLuna.h"

class wiFont;

class wiFont_BindLua
{
public:
	wiFont* font;

	static const char className[];
	static Luna<wiFont_BindLua>::FunctionType methods[];
	static Luna<wiFont_BindLua>::PropertyType properties[];

	wiFont_BindLua(wiFont* font);
	wiFont_BindLua(lua_State* L);
	~wiFont_BindLua();

	int SetStyle(lua_State* L);
	int SetText(lua_State* L);
	int SetSize(lua_State* L);
	int SetPos(lua_State* L);
	int SetSpacing(lua_State* L);
	int SetAlign(lua_State* L);

	int GetText(lua_State* L);
	int GetSize(lua_State* L);
	int GetPos(lua_State* L);
	int GetSpacing(lua_State* L);
	int GetAlign(lua_State* L);

	int Destroy(lua_State* L);


	static void Bind();
};

