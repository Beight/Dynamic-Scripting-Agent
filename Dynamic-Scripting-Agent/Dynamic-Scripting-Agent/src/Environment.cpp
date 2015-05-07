#include "Environment.h"


Environment::Environment() : m_JVM(nullptr)
{
}

Environment::~Environment()
{

}
void Environment::init()
{
	m_JVM = IJVM::createJVM();
	m_JVM->init();
	m_JVM->createMarioEnvironment("ch/idsia/benchmark/mario/environments/MarioEnvironment");
	m_JVM->reset("-vis on");
}

void Environment::run()
{


	if (m_JVM == nullptr)
		return;
	

	m_JVM->getEntireObservation(1,1);
	int action[6] = { 0, 1, 0, 1, 1, 0 };
	m_JVM->performAction(action);
	int *eval = m_JVM->getEvaluationInfo();
	int *obs = m_JVM->getObservationDetails();

	int seed = 0;

	m_JVM->reset("-ag ch.idsia.agents.controllers.ForwardJumpingAgent -echo on");
	obs = m_JVM->getObservationDetails();
	//agent.setObservationdetails(obs[0], obs[1], obs[2], [obs3])



	while (!m_JVM->isLevelFinished())
	{
		m_JVM->tick();
		m_JVM->getEntireObservation(1, 0);
		//agent.integrateobservation();
		//agent.getaction();
		m_JVM->performAction(action);
	}




	//bool isfinished = m_JVM->isLevelFinished();
	//m_JVM->tick();
	//m_JVM->performAction(m_action);

}

void Environment::destroy()
{
	IJVM::deleteJVM(m_JVM);
}