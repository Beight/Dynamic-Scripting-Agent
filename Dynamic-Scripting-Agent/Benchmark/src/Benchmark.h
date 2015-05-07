#pragma once

#include "IBenchmark.h"
#include "JavaInterface.h"

class Benchmark : public IBenchmark
{
public:
	Benchmark();
	~Benchmark();

	int init(int p_numJavaOptions, ...) override;

	void reset(const char *p_options) override;
	bool isLevelFinished() override;
	void tick() override;
	int *getEvaluationInfo() override;
	void getEntireObservation(int p_zLevelScene, int p_zLevelEnemies) override;
	int *getObservationDetails() override;
	void performAction(int *p_action) override;


private:
	JavaInterface m_jInterface;
	jclass m_marioEnvCl;
	jobject m_marioEnvObj;
	int m_numberOfButtons;
	jmethodID m_mIdReset;
	jmethodID m_mIdIsLevelFinished;
	jmethodID m_mIdTick;
	jmethodID m_mIdGetEvalutationInfo;
	jmethodID m_mIdGetSerializedLevelSceneObservationZ;
	jmethodID m_mIdGetSerializedEnemiesObservationZ;
	jmethodID m_mIdGetObservationDetails;
	jmethodID m_mIdPerformAction;
	jmethodID m_mIdGetMarioPos;
	jmethodID m_mIdGetEnemiesPos;
	jmethodID m_mIdGetMarioState;

	void getMethodIds() override;
	void shutdown() override;
};

