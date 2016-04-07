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
	m_benchmark->reset("-vis on -echo on -fps 100");
	std::vector<int> observationDetails;
	m_benchmark->getObservationDetails(observationDetails);
	m_agent.setObservationDetails(observationDetails.at(0), observationDetails.at(1), observationDetails.at(2), observationDetails.at(3));

	while (!m_benchmark->isLevelFinished())
	{
		m_benchmark->tick();
		IBenchmark::Observation observation = m_benchmark->getEntireObservation(1, 0);
		m_agent.integrateObservation(observation.levelScene, observation.enemyScene, observation.marioState, observation.marioPosition, observation.enemyPosition);
		m_benchmark->performAction(m_agent.getAction());
	}
	std::vector<int> evaluation;
	m_benchmark->getEvaluationInfo(evaluation);
}

void Environment::destroy()
{
	IBenchmark::destroyBenchmark(m_benchmark);
}