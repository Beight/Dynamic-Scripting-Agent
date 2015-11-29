#pragma once

#include <vector>
#include <string>
#include "LuaScript.h"

class Agent
{
public:
	/*
	 * Represents a rule that can be inserted in a script.
	*/
	struct Rule
	{
		std::string script;
		int weight;
		bool active;

		Rule(std::string p_script, int p_startWeight) :	script(p_script),
															weight(p_startWeight),
															active(false)
		{}							 
	};

	/*
	* Constructor
	*/
	Agent();

	/*
	* Destructor
	*/
	~Agent();

	/*
	* Initializes the agent.
	* Always call once before using the agent!
	* Loads the base script from file and generates the first script 
	* which it sends to the lua class.
	*/
	void init();
	/*
	* Saves observation details aquired from the benchmark which the agent uses to influence its actions.
	* @param p_receptiveWidth, width of the grid which the agent gathers abservations data from.
	* @param p_receptiveHeigth, height of the grid which the agent gathers observations data from.
	* @param p_marioPosX, the agent's X position within the receptive grid.
	* @param p_marioPosY, the agent's Y position within the receotive grid.
	*/
	void setObservationDetails(int p_receptiveWidth, int p_receptiveHeight, int p_marioPosX, int p_marioPosY);

	/*
	* Saves observation details aquired from the benchmark which the agent uses to influence its actions.
	* @param p_lvlScene, contains information about the level around the agent.
	* @param p_enemyScene, contains information of enemies close to the agent.
	* @param p_marioState, contains informations about agents state:
	*		[0] = MarioStatus, 0 = Dead, 1 = Win, 2 = Running
	*		[1] = MarioMode, 0 = Small, 1 = Big, 2 = Fire
	*		[2] = IsMarioOnGround, true/false
	*		[3] = IsMarioAbleToJump. true/false
	*		[4] = IsMarioAbleToShoot true/false
	*		[5] = isMarioCarrying true/false
	*		[6] = TotalKills
	*		[7] = KillsByFire
	*		[8] = KillsByStomp
	*		[9] = KillsByShell
	* @param p_marioPos, the agent's Y position within the receotive grid.
	*/
	void integrateObservation(const std::vector<int> &p_lvlScene, const std::vector<int> &p_enmeyScene, const std::vector<int> &p_marioState, const std::vector<float> &p_marioPos, const std::vector<float> &p_enemyPos);
	std::vector<int> getAction();
	void reset();

private:
	std::string m_name;
	std::vector<int> m_action;
	int m_marioStatus;
	int m_marioMode;
	bool m_isMarioOnGround;
	bool m_isMarioAbleToJump;
	bool m_isMarioAbleToShoot;
	bool m_isMarioCarrying;
	int m_killsTotal;
	int m_killsByFire;
	int m_killsByStomp;
	int m_killsByShell;
	int m_receptiveFieldWidth;
	int m_receptiveFieldheight;
	int m_marioEgoRow;
	int m_marioEgoCol;
	float m_marioPos[2];
	std::vector<float> m_enemiesPos;
	std::vector<int> m_lvlScene;
	LuaScript m_script;
	std::vector<Rule> m_ruleBase;
	std::string m_baseScriptStr;
	std::string m_generatedScriptStr;

	void updateWeights();
	void clearScript();
	void generateScript();
	bool insertInScript(const std::string &p_script);
};

