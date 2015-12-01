#pragma once

#include "Agent.h"
#include "IBenchmark.h"

class Environment
{
public:
	/*
	* Constructor
	*/
	Environment();
	/*
	* Destructor
	*/
	~Environment();
	/*
	* Initializes the environment.
	* Creates the benchmark and the agent.
	* @return, 0 = success, < 0 = failure
	*/
	int init();
	/*
	*	The environments update function, updates the benchmark and agent.
	*	Must run contiuously for th application to wor.k
	*/
	void run();
	/*
	*	Deletes and releases all data used by the environment. 
	*/
	void destroy();
private:
	IBenchmark *m_benchmark;
	Agent m_agent;
};
