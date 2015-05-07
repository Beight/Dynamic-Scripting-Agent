#pragma once

#include "IBenchmark.h"

class Benchmark : public IBenchmark
{
public:
	Benchmark();
	~Benchmark();

	void init() override;

	void reset(const char *p_options) override;
	bool isLevelFinished() override;
	void tick() override;
	int *getEvaluationInfo() override;
	void getEntireObservation(int p_zLevelScene, int p_zLevelEnemies) override;
	int *getObservationDetails() override;
	void performAction(int *p_action) override;


private:
	void createMarioEnvironment(const char *p_javaClassName) override;
	void shutdown() override;
};

