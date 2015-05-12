#include "Environment.h"


Environment::Environment() : m_benchmark(nullptr)
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

	return result;
}

void Environment::run()
{
	int action[6] = { 0, 1, 0, 1, 0, 0 };

	m_benchmark->reset("-vis off -echo on");
	int *obs = m_benchmark->getObservationDetails();
	//agent.setObservationdetails(obs[0], obs[1], obs[2], [obs3])

	while (!m_benchmark->isLevelFinished())
	{
		m_benchmark->tick();
		m_benchmark->getEntireObservation(1, 0);
		//agent.integrateobservation();
		//agent.getaction();
		m_benchmark->performAction(action);
	}
	delete[] obs;

	int *eval = m_benchmark->getEvaluationInfo();
	delete[] eval;
	
}

void Environment::destroy()
{
	IBenchmark::destroyBenchmark(m_benchmark);
}