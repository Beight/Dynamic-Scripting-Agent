#pragma once

#include <vector>
#include <string>

class Agent
{
public:
	struct Rule
	{
		std::string script;
		float weight;
		bool active;

		Rule(std::string p_script, float p_startWeight) :	script(p_script),
															weight(p_startWeight),
															active(false)
		{}							 
	};

	Agent();
	~Agent();

	void init();
	void setObservationDetails(int p_receptiveWidth, int p_receptiveHeight, int p_marioPosX, int p_marioPosY);
	void integrateObservation(const std::vector<int> &p_lvlScene, const std::vector<int> &p_enmeyScene, const std::vector<int> &p_marioState, const std::vector<float> &p_marioPos, const std::vector<float> &p_enemyPos);
	std::vector<int> getAction();
	void reset();
	//std::string getName();
	//void setName(std::string p_newName);

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
	std::vector<Rule> m_ruleBase;
	int m_ruleCount;

	bool danger();
	void updateWeights();
	void clearScript();
	void generateScript();
	bool insertInScript(std::string p_script);
};

