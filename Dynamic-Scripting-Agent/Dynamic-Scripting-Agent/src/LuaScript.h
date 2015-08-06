#pragma once

#include <lua.hpp>
#include <vector>

class LuaScript
{
public:
	LuaScript();
	~LuaScript();
	void loadScript(const char *p_fileName);
	void getGlobal(const char *p_globalName);
	void callFunction(int p_nrArguments, int p_nrReturns);
	void pushNumber(double p_nr);
	void pushNil();
	void pop(int p_stackPos);
	int toNumber(int p_stackPos);
	void next(int p_stackPos);

	std::vector<int> getIntVector(const char *p_vectorName);

	void runScript();
private:
	lua_State *m_state;


};

