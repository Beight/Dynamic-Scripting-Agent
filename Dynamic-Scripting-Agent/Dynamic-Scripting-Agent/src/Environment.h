#pragma once

#include "Agent.h"
#include "IJVM.h"

class Environment
{
public:
	Environment();
	~Environment();
	void init();
	void run();
	void destroy();
private:
	IJVM *m_JVM;
};
