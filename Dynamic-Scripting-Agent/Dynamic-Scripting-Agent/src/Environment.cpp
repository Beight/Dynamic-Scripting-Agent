#include "Environment.h"


Environment::Environment() : m_benchmark(nullptr)
{
}

Environment::~Environment()
{

}
int Environment::init()
{
	int res = 0;
	m_benchmark = IBenchmark::createBenchmark();
	res = m_benchmark->init(2, "-Djava.class.path=D:\\ExamensArbete\\Mario-AI-Benchmark\\build\\classes", "-Djava.library.path=D:\\ExamensArbete\\Mario-AI-Benchmark\\lib");
	if (res < 0)
		return res;

	m_benchmark->reset("-vis on");
}

void Environment::run()
{
	m_benchmark->getEntireObservation(1, 1);
	int action[6] = { 0, 1, 0, 1, 1, 0 };
	m_benchmark->performAction(action);
	int *eval = m_benchmark->getEvaluationInfo();
	int *obs = m_benchmark->getObservationDetails();

	m_benchmark->reset("-vis on -echo on");
	obs = m_benchmark->getObservationDetails();
	//agent.setObservationdetails(obs[0], obs[1], obs[2], [obs3])


	while (!m_benchmark->isLevelFinished())
	{
		m_benchmark->tick();
		m_benchmark->getEntireObservation(1, 0);
		//agent.integrateobservation();
		//agent.getaction();
		m_benchmark->performAction(action);
	}

	//m_JVM->getEntireObservation(1,1);
	//int action[6] = { 0, 1, 0, 1, 1, 0 };
	//m_JVM->performAction(action);
	//int *eval = m_JVM->getEvaluationInfo();
	//int *obs = m_JVM->getObservationDetails();

	//int seed = 0;

	//m_JVM->reset("-ag ch.idsia.agents.controllers.ForwardJumpingAgent -echo on");
	//obs = m_JVM->getObservationDetails();
	////agent.setObservationdetails(obs[0], obs[1], obs[2], [obs3])



	//while (!m_JVM->isLevelFinished())
	//{
	//	m_JVM->tick();
	//	m_JVM->getEntireObservation(1, 0);
	//	//agent.integrateobservation();
	//	//agent.getaction();
	//	m_JVM->performAction(action);
	//}
}

void Environment::destroy()
{
	IBenchmark::destroyBenchmark(m_benchmark);
}