#pragma once

#include "IBenchmark.h"
#include "JavaInterface.h"

class Benchmark : public IBenchmark
{
public:
	Benchmark();
	~Benchmark();

	int init(int p_numberOfJavaOptions, ...) override;

	void reset(const char *p_options) override;
	bool isLevelFinished() override;
	void tick() override;
	void getEvaluationInfo(std::vector<int> &p_ret) override;
	IBenchmark::Observation getEntireObservation(int p_zLevelScene, int p_zLevelEnemies) override;
	void getObservationDetails(std::vector<int> &p_ret) override;
	void performAction(const std::vector<int> &p_action) override;


private:
	JavaInterface m_javaInterface;
	jclass m_EnvironmentClass;
	jobject m_EnvironmentObject;
	int m_numberOfButtons;
	jmethodID m_methodIDReset;
	jmethodID m_methodIDIsLevelFinished;
	jmethodID m_methodIDTick;
	jmethodID m_methodIDGetEvalutationInfo;
	jmethodID m_methodIDGetSerializedLevelSceneObservationZ;
	jmethodID m_methodIDGetSerializedEnemiesObservationZ;
	jmethodID m_methodIDGetObservationDetails;
	jmethodID m_methodIDPerformAction;
	jmethodID m_methodIDGetMarioPos;
	jmethodID m_methodIDGetEnemiesPos;
	jmethodID m_methodIDGetMarioState;

	void getMethodIds() override;
	void shutdown() override;
};

