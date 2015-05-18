#include "Agent.h"

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
				 m_ruleCount(0)
{
}

Agent::~Agent()
{
}

void Agent::init()
{
	m_action = { 0, 1, 0, 0, 1, 0 };
	//lua??
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


	m_marioStatus = p_marioState.at(0);
	m_marioMode = p_marioState.at(1);
	m_isMarioOnGround = p_marioState.at(2);
	m_isMarioAbleToJump = p_marioState.at(3);
	m_isMarioAbleToShoot = p_marioState.at(4);
	m_isMarioCarrying = p_marioState.at(5);
	m_killsTotal = p_marioState.at(6);
	m_killsByFire = p_marioState.at(7);
	m_killsByStomp = p_marioState.at(8);
	m_killsByShell = p_marioState.at(9);


}

std::vector<int> Agent::getAction()
{
	m_action.at(3) = !m_isMarioOnGround || m_isMarioAbleToJump;

	return m_action;
}

bool Agent::danger()
{
	return false;
}

void Agent::updateWeights()
{}

void Agent::clearScript()
{}

void Agent::generateScript()
{
	clearScript();
	int sumWeights = 0;
	int maxt = 10;
	for (unsigned int i = 0; i < m_ruleBase.size(); i++)
		sumWeights = sumWeights + m_ruleBase.at(i).weight;

	for (int i = 0; i < m_ruleCount; i++)
	{
		int t = 0;
		bool lineadded = false;
		while (t < maxt && !lineadded)
		{
			int j = 0;
			int sum = 0;
			int selected = -1;
			int fraction = rand() % sumWeights;
			
			while (selected < 0)
			{
				sum = sum + m_ruleBase.at(j).weight;
				if (sum > fraction)
					selected = j;
				else
					j = j + 1;
			}
			lineadded = insertInScript(m_ruleBase.at(selected).script);
			t = t + 1;
		}
	}
	//Finish Script();
}


bool insertInScript(std::string p_script)
{
	return true;
}