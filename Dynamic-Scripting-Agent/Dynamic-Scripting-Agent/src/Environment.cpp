#include "Environment.h"


Environment::Environment() : m_benchmark(nullptr),
							 m_agent(Agent())
{
}

Environment::~Environment()
{

}
int Environment::init()
{
	m_benchmark = IBenchmark::createBenchmark();
	int result = m_benchmark->init(1, "-Djava.class.path=..\\..\\..\\Mario-AI-Benchmark\\dist\\Mario_AI_Benchmark.jar");
	if (result < 0)
		return result;
	m_agent.init();
	return result;
}

void Environment::run()
{
	m_benchmark->reset("-vis on -echo on");
	std::vector<int> obsDet;
	m_benchmark->getObservationDetails(obsDet);
	m_agent.setObservationDetails(obsDet.at(0), obsDet.at(1), obsDet.at(2), obsDet.at(3));

	while (!m_benchmark->isLevelFinished())
	{
		m_benchmark->tick();
		IBenchmark::Observation obs = m_benchmark->getEntireObservation(1, 0);
		m_agent.integrateObservation(obs.lvlScene, obs.enemyScene, obs.marioState, obs.marioPos, obs.enemyPos);
		m_benchmark->performAction(m_agent.getAction());
	}
	std::vector<int> eval;
	m_benchmark->getEvaluationInfo(eval);
	int j = 43;
}

void Environment::destroy()
{
	IBenchmark::destroyBenchmark(m_benchmark);
}