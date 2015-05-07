#pragma once

#include "Agent.h"
#include "IBenchmark.h"

class Environment
{
public:
	Environment();
	~Environment();
	void init();
	void run();
	void destroy();
private:
	IBenchmark *m_benchmark;
};
