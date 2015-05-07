#pragma once

#include "IJVM.h"
#include "jni.h"



class JVM : public IJVM
{
public:
	JVM();
	~JVM();

	void init() override;
	void initBenchmark() override;
	void createMarioEnvironment(const char *p_javaClassName) override;
	void reset(const char *p_options) override;
	bool isLevelFinished() override;
	void tick() override;
	int *getEvaluationInfo() override;
	void getEntireObservation(int p_zLevelScene, int p_zLevelEnemies) override;
	int *getObservationDetails() override;
	void performAction(int *p_action) override;

	

private:
	JNIEnv_ *m_env;
	JavaVM *m_JVM;
	jclass m_jclass;
	jobject m_jobject;

	int m_numberOfButtons;
	jmethodID m_idReset;
	jmethodID m_idIsLevelFinished;
	jmethodID m_idTick;
	jmethodID m_idGetEvalutationInfo;
	jmethodID m_idGetSerializedLevelSceneObservationZ;
	jmethodID m_idGetSerializedEnemiesObservationZ;
	jmethodID m_idGetObservationDetails;
	jmethodID m_idPerformAction;
	jmethodID m_idGetMarioPos;
	jmethodID m_idGetEnemiesPos;
	jmethodID m_idGetMarioState;
	

	void shutdown() override;
	jmethodID getMethodID(const char* p_mName, const char *p_mSig);
	void javaError();
};