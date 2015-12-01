#pragma once

#include <lua.hpp>
#include <vector>
#include <string>

class LuaScript
{
public:
	/*
	* Constructor
	*/
	LuaScript();
	/*
	* Destructor
	*/
	~LuaScript();
	/*
	* Calls a function from a lua script.
	* @param p_functionName, name of function to be called.
	* @param p_nrArguments, The number of arguments the function takes.
	* @param p_p_nrReturns, The number of returns the called function has.
	*/
	void callFunction(const std::string& p_functionName, int p_nrArguments, int p_nrReturns);
	/*
	* Gets a table from the lua and returns it as a int vector.
	* @p_tableName, name of the tabvle in the lua script.
	* @return, an int vector containting the data of the table.
	*/
	std::vector<int> getIntVectorFromTable(const std::string& p_tableName);
	/*
	* Converts an int vector to a lua table and the data writes it to the corresponding lua table in the script.
	* @param p_transferVector, vector to transfer.
	* @param p_tableName, name of the table to transfer content to.
	*/
	void intVectorToLuaTable(const std::vector<int> &p_transferVector, const std::string &p_tableName);
	/*
	* Cleans the Lua stack
	*/
	void clean();

	/*
	* Loads a lua script into the lua state. NOTE! If a script already exits in this instance it will be replaced by the new one.
	* @param p_script, a string containing the script to be loaded.
	*/
	void load(const std::string& p_script);

	//templates
	
	/*
	* Converts an std vector to a lua table and saves it to the lua state.
	* @param p_vectorToTransfer, what vector to transfer.
	* @param p_tableName, the table to transfer the data to.
	*/
	template<typename T>
	void vectorToLuaTable(const std::vector<T> &p_vectorToTransfer, const std::string &p_tableName)
	{
		lua_createtable(m_state, p_vectorToTransfer.size(), 0);
		int newTable = lua_gettop(m_state);
		int index = 1;

		for (unsigned int i = 0; i < p_vectorToTransfer.size(); i++)
		{
			lua_pushnumber(m_state, p_vectorToTransfer.at(i));
			lua_rawseti(m_state, newTable, index);
			index++;
		}

		lua_setglobal(m_state, p_tableName.c_str());
	}



	//template<typename T>
	//T get(const std::string &p_variableName)
	//{
	//	if (!m_State)
	//	{
	//		printError(p_variableName, "Script is not Loaded");
	//		return lua_getDefault<T>();
	//	}

	//	T result;
	//	if (lua_getToStack(p_variableName)) //variable successfully on top on stack
	//		result = lua_get<T>();
	//	else
	//		result = lua_getDefault<T>();

	//	lua_pop(m_state, m_level + 1); //pop all exsiting elements from stack
	//	return result;
	//}

	//bool lua_getToStack(const std::string &p_variableName)
	//{
	//	m_level = 0;
	//	std::string var = "";
	//	for (unsigned int i = 0; i < p_variableName.size(); i++)
	//	{
	//		if (p_variableName.at(i) == '.')
	//		{
	//			if (m_level == 0)
	//				lua_getglobal(m_state, var.c_str());
	//			else
	//				lua_getfield(m_state, -1, var.c_str());


	//			if (lua_isnil(m_state, -1))
	//			{
	//				printError(p_variableName, var + " is not defined");
	//				return false;
	//			}
	//			else
	//			{
	//				var = "";
	//				m_level++;
	//			}	
	//		}
	//		else
	//			var += p_variableName.at(i);
	//	}
	//	if (m_level == 0)
	//		lua_getglobal(m_state, var.c_str());
	//	else
	//		lua_getfield(m_state, -1, var.c_str());
	//	
	//	if (lua_isnil(m_state, -1))
	//	{
	//		printError(p_variableName, var + " is not defined");
	//		return false;
	//	}

	//	return true;
	//}

	//template<typename T>
	//T lua_get(const std::string &variableName)
	//{
	//	return 0;
	//}

	//template<typename T>
	//T lua_getDefault()
	//{
	//	return 0;
	//}

private:
	lua_State *m_state;
	int m_level;
	std::string m_fileName;

	void printError(const std::string& p_variableName, const std::string& p_reason);
};

////template specializations
//template<>
//inline std::string LuaScript::lua_getDefault<std::string>()
//{
//	return "";
//}
//
//template<>
//inline bool LuaScript::lua_get(const std::string &p_variableName)
//{
//	return lua_toboolean(m_state, -1) != 0;
//}
//
//template<>
//inline float LuaScript::lua_get(const std::string &p_variableName)
//{
//	if (!lua_isnumber(m_state, -1))
//		printError(p_variableName, "Not a number");
//
//	return (float)lua_tonumber(m_state, -1);
//}
//
//template<>
//inline int LuaScript::lua_get(const std::string &p_variableName)
//{
//	if (!lua_isnumber(m_state, -1))
//		printError(p_variableName, "Not a number");
//
//	return (int)lua_tonumber(m_state, -1);
//}
//
//template<>
//inline std::string LuaScript::lua_get(const std::string &p_variableName)
//{
//	std::string s = "";
//	if (lua_isstring(m_state, -1))
//		s = std::string(lua_tostring(m_state, -1));
//	else
//		printError(p_variableName, "Not a string");
//
//	return s;
//}

