#include "LuaScript.h"
#include <iostream>

LuaScript::LuaScript()
{
	m_state = luaL_newstate();

	if (m_state)
	{
		luaL_openlibs(m_state);
	}


}

LuaScript::~LuaScript()
{
	if (m_state)
		lua_close(m_state);

}

void LuaScript::load(const std::string& p_scriptname)
{
	//if (m_state)
	//	lua_close(m_state);

	//m_state = luaL_newstate();
	
	if (luaL_dostring(m_state, p_scriptname.c_str()))// || lua_pcall(m_state, 0, 0, 0))
	{
		std::cout << lua_tostring(m_state, -1) << "\n";
		m_state = 0;
	}
	//if (m_state)
	//{
	//	luaL_openlibs(m_state);
	//}

}

void LuaScript::callFunction(const std::string &p_fucntionName, int p_nrArguments, int nrReturns)
{
	lua_getglobal(m_state, p_fucntionName.c_str());

	if (lua_pcall(m_state, p_nrArguments, nrReturns, 0) != 0)
		std::cout << lua_tostring(m_state, -1) << "\n";


}
void LuaScript::printError(const std::string& p_variableName, const std::string &p_reason)
{
	std::cout << "Error: can't get " << p_variableName << " " << p_reason << "\n";
}

std::vector<int> LuaScript::getIntVector(const std::string &p_vectorName)
{
	std::vector<int> v;
	lua_getglobal(m_state, p_vectorName.c_str());
	if (lua_isnil(m_state, -1))
		return std::vector<int>();

	lua_pushnil(m_state);
	while (lua_next(m_state, -2))
	{
		v.push_back(static_cast<int>(lua_tonumber(m_state, -1)));
		lua_pop(m_state, 1);
	}
	clean();
	return v;
}

void LuaScript::intVectorToLuaTable(const std::vector<int> &p_transferVector, const std::string &p_tableName)
{
	lua_createtable(m_state, p_transferVector.size(), 0);
	int newTable = lua_gettop(m_state);
	int index = 1;
	//std::vector<int>::const_iterator iter = p_transferVector.begin();


	for (unsigned int i = 0; i < p_transferVector.size(); i++)
	{
		lua_pushnumber(m_state, p_transferVector.at(i));
		lua_rawseti(m_state, newTable, index);
		index++;
	}

	//while (iter == p_transferVector.end())
	//{
	//	lua_pushnumber(m_state, (*iter));
	//	lua_rawseti(m_state, newTable, index);
	//	iter++;
	//	index++;
	//}


	lua_setglobal(m_state, p_tableName.c_str());	
}


void LuaScript::clean()
{
	int n = lua_gettop(m_state);
	lua_pop(m_state, n);
}