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
	std::string s;
	if (luaL_dofile(m_state, p_fileName))
		s = lua_tostring(m_state, -1);


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

void LuaScript::pushNil()
{
	lua_pushnil(m_state);
}

void LuaScript::pop(int p_stackPos)
{
	lua_pop(m_state, p_stackPos);
}

int LuaScript::toNumber(int p_stackPos)
{
	return (int)lua_tonumber(m_state, p_stackPos);
}

void LuaScript::next(int p_stackPos)
{
	lua_next(m_state, p_stackPos);
}

std::vector<int> LuaScript::getIntVector(const char *p_vectorName)
{
	std::vector<int> v;
	lua_getglobal(m_state, p_vectorName);
	if (lua_isnil(m_state, -1))
		return std::vector<int>();
	
		

	lua_pushnil(m_state);
	while (lua_next(m_state, -2))
	{
		v.push_back((int)lua_tonumber(m_state, -1));
		lua_pop(m_state, 1);
	}

	return v;
}

void LuaScript::runScript()
{
	
}