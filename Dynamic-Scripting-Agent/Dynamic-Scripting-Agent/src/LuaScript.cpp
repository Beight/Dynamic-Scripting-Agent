#include "LuaScript.h"


LuaScript::LuaScript()
{
	m_state = luaL_newstate();
	luaL_openlibs(m_state);

}

LuaScript::~LuaScript()
{
	lua_close(m_state);

}

void LuaScript::loadScript(const char *p_fileName)
{
	//luaL_dofile(m_state, p_fileName);
}

void LuaScript::callFunction(int p_nrArguments, int nrReturns)
{
	if(lua_pcall(m_state, p_nrArguments, nrReturns, 0) != 0)
		return;
	//int z = 0;
	//if (lua_isnumber(m_state, -1))
	//	z = lua_tonumber(m_state, -1);

	//lua_pop(m_state, 1);
	//return z;
}

void LuaScript::getGlobal(const char *p_functionName)
{
	lua_getglobal(m_state, p_functionName);
}

void LuaScript::pushNumber(double p_nr)
{
	lua_pushnumber(m_state, p_nr);
}

void LuaScript::runScript()
{
	
}