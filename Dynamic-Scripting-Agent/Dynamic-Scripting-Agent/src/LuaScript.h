#include <lua.hpp>

class LuaScript
{
public:
	LuaScript();
	~LuaScript();
	void loadScript(const char *p_fileName);
	void getGlobal(const char *p_functionName);
	void callFunction(int p_nrArguments, int p_nrReturns);
	void pushNumber(double p_nr);
	void runScript();
private:
	lua_State *m_state;


};

