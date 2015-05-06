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
	m_JVM->reset("-ag ch.idsia.agents.controllers.ForwardAgent -vis on");
}

void Environment::run()
{
	int m_action[6] = { 0, 1, 0, 1, 0, 0 };
	for (int i = 0; i < 100000; i++)
	{
		m_JVM->tick();
		m_JVM->performAction(m_action);
	}



	m_JVM->getEntireObservation(1,1);
	int *eval = m_JVM->getEvaluationInfo();
	int *obs = m_JVM->getObservationDetails();
	bool isfinished = m_JVM->isLevelFinished();


}

void Environment::destroy()
{
	IJVM::deleteJVM(m_JVM);
}