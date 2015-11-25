#include "Agent.h"
#include <fstream>
//#include <iostream>
#include <sstream>

Agent::Agent() : m_name(""),
				 m_action(),
				 m_marioStatus(0),
				 m_marioMode(0),
				 m_isMarioOnGround(false),
				 m_isMarioAbleToJump(false),
				 m_isMarioAbleToShoot(false),
				 m_isMarioCarrying(false),
				 m_killsTotal(0),
				 m_killsByFire(0),
				 m_killsByStomp(0),
				 m_killsByShell(0),
				 m_receptiveFieldWidth(0),
				 m_receptiveFieldheight(0),
				 m_marioEgoRow(0),
				 m_marioEgoCol(0),
				 m_enemiesPos(),
				 m_script(LuaScript("scriptagent.lua")),
				 m_scriptRuleCount()
{
	m_ruleBase.push_back(Rule("	newAction = not isMarioOnGround or isMarioAbleToJump\n\n	if newAction == true then\n		action[4] = 1 \n	else\n		action[4] = 0\n	end\n\n", 10));
	m_ruleBase.push_back(Rule("	action[2] = 1\n	action[5] = 1\n", 10));
}

Agent::~Agent()
{
}

void Agent::init()
{
	
	generateScript();
	m_script.load("scriptagent.lua");
	//m_script.callFunction("init", 0, 0);
	m_action = m_script.getIntVector("action");
}

void Agent::setObservationDetails(int p_receptiveWidth, int p_receptiveHeight, int p_marioPosRow, int p_marioPosCol)
{
	//lua??
	m_receptiveFieldWidth = p_receptiveWidth;
	m_receptiveFieldheight = p_receptiveHeight;
	m_marioEgoRow = p_marioPosRow;
	m_marioEgoCol = p_marioPosCol;
}

void Agent::integrateObservation(const std::vector<int> &p_lvlScene, const std::vector<int> &p_enmeyScene, const std::vector<int> &p_marioState, const std::vector<float> &p_marioPos, const std::vector<float> &p_enemyPos)
{
	int row = m_receptiveFieldheight;
	int col = m_receptiveFieldWidth;

	std::vector<int> levelScene;
	std::vector<int> enemiesObservation;

	for (int i = 0; i < row; i++)
		for (int j = (i * col); j < (i * col + col); j++)
			levelScene.push_back(p_lvlScene.at(j));

	m_lvlScene = levelScene;

	for (int i = 0; i < row; i++)
		for (int j = (i * col); j < (i * col + col); j++)
			enemiesObservation.push_back(p_enmeyScene.at(j));

	m_marioPos[0] = p_marioPos.at(0);
	m_marioPos[1] = p_marioPos.at(1);
	m_enemiesPos = p_enemyPos;


	//m_marioStatus = p_marioState.at(0);
	//m_marioMode = p_marioState.at(1);
	//m_isMarioOnGround = p_marioState.at(2);
	//m_isMarioAbleToJump = p_marioState.at(3);
	//m_isMarioAbleToShoot = p_marioState.at(4);
	//m_isMarioCarrying = p_marioState.at(5);
	//m_killsTotal = p_marioState.at(6);
	//m_killsByFire = p_marioState.at(7);
	//m_killsByStomp = p_marioState.at(8);
	//m_killsByShell = p_marioState.at(9); //sent to lua


	m_script.vectorToLuaTable(p_marioPos, "marioPos");
	m_script.vectorToLuaTable(p_enemyPos, "enemyPos");
	m_script.vectorToLuaTable(p_marioState, "marioState");
	m_script.callFunction("integrateObservation", 0, 0);
}

std::vector<int> Agent::getAction()
{
	m_script.callFunction("getAction", 0, 0);
	m_action = m_script.getIntVector("action");

	///m_action.at(3) = !m_isMarioOnGround || m_isMarioAbleToJump; //moved to lua

	return m_action;
}

void Agent::updateWeights()
{
	int active = 0;
	int minWeight = 0;
	int maxWeight = 200;
	
	for (unsigned int i = 0; i < m_ruleBase.size() - 1; i++)
	{
		if (m_ruleBase.at(i).active)
		{
			active++;
		}
	}

	if (active <= 0 || active >= m_ruleBase.size())
		return;

	int nonactive = m_ruleBase.size() - active;
	int adjustment = 1;// = calculateAdjustment(fitness) Not implemented yet.
	int compensation = -active * adjustment | nonactive;
	int remains = 0;

	//Credit assignment
	for (unsigned int i = 0; i < m_ruleBase.size() - 1; i++)
	{
		if (m_ruleBase.at(i).active)
			m_ruleBase.at(i).weight += adjustment;
		else
			m_ruleBase.at(i).weight += compensation;

		if (m_ruleBase.at(i).weight < minWeight)
		{
			remains += (m_ruleBase.at(i).weight - minWeight);
			m_ruleBase.at(i).weight = minWeight;
		}
		else if (m_ruleBase.at(i).weight > maxWeight)
		{
			remains += (m_ruleBase.at(i).weight - maxWeight);
			m_ruleBase.at(i).weight = maxWeight;
		}
		//distributeRemains() not implemented yet.
	}
}

void Agent::clearScript()
{}

void Agent::generateScript()
{
	clearScript();
	int sumWeights = 0;
	int maxtries = 10;

	std::ofstream out;
	out.open("scriptagent.lua", std::ios_base::app);
	out << "\nfunction getAction()\n";
	out.close();



	for (unsigned int i = 0; i < m_ruleBase.size(); i++)
		sumWeights = sumWeights + m_ruleBase.at(i).weight;

	for (int i = 0; i < m_scriptRuleCount; i++)
	{
		int tries = 0;
		bool lineadded = false;
		while (tries < maxtries && !lineadded)
		{
			int j = 0;
			int sum = 0;
			int selected = -1;
			int fraction = rand() % sumWeights;
			
			while (selected < 0)
			{
				sum = sum + m_ruleBase.at(j).weight;
				if (sum > fraction && m_ruleBase.at(j).active == false)
					selected = j;
				else
					j = j + 1;
			}
			lineadded = insertInScript(m_ruleBase.at(selected).script);
			m_ruleBase.at(selected).active = true;
			tries = tries + 1;
		}
	}

	out.open("scriptagent.lua", std::ios_base::app);
	out << "end";
	out.close();
}


bool Agent::insertInScript(const std::string &p_script)
{
	std::ofstream file;


	file.open("scriptagent.lua", std::ios_base::app);
	file << p_script;
	file.close();

	return true;
}