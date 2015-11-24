#include "Benchmark.h"


IBenchmark *IBenchmark::createBenchmark()
{
	return new Benchmark();
}


Benchmark::Benchmark() : m_jInterface(JavaInterface()),
						 m_marioEnvCl(nullptr),
						 m_marioEnvObj(nullptr),
						 m_numberOfButtons(0),
						 m_mIdReset(nullptr),
						 m_mIdIsLevelFinished(nullptr),
						 m_mIdTick(nullptr),
						 m_mIdGetEvalutationInfo(nullptr),
						 m_mIdGetSerializedLevelSceneObservationZ(nullptr),
						 m_mIdGetSerializedEnemiesObservationZ(nullptr),
						 m_mIdGetObservationDetails(nullptr),
						 m_mIdPerformAction(nullptr),
						 m_mIdGetMarioPos(nullptr),
						 m_mIdGetEnemiesPos(nullptr),
						 m_mIdGetMarioState(nullptr)
{
}

Benchmark::~Benchmark()
{
}


int Benchmark::init(int p_numJavaOptions, ...)
{
	m_numberOfButtons = 6;

	va_list args;
	va_start(args, p_numJavaOptions);
	int res = m_jInterface.initJava(p_numJavaOptions, args);
	va_end(args);
	
	if (res != 0)
	{
		return res;
	}
	
	/*
	  Could have the argument as parameter in this method but  
	  the benchmark will awalys use the same environment in this project
	  so there's no need to let the user change it.
	*/
	m_marioEnvCl = m_jInterface.createJavaClass("ch/idsia/benchmark/mario/environments/MarioEnvironment");
	if (m_marioEnvCl == nullptr)
		return -1;

	jmethodID mid = m_jInterface.getStaticMethodID(m_marioEnvCl, "getInstance", "()Lch/idsia/benchmark/mario/environments/MarioEnvironment;");

	m_marioEnvObj = m_jInterface.callJavaStaticObjectMethod(m_marioEnvCl, mid);
	if (m_marioEnvObj == nullptr)
		return -1;

	getMethodIds();

	return 0;
}

void Benchmark::reset(const char *p_options)
{
	jobject options = m_jInterface.cStringToJavaString(p_options);
	m_jInterface.callJavaVoidMethod(m_marioEnvObj, m_mIdReset, options);
	m_jInterface.delLocalRef(options);
}

bool Benchmark::isLevelFinished()
{
	return m_jInterface.callJavaBooleanMethod(m_marioEnvObj, m_mIdIsLevelFinished);
}

void Benchmark::tick()
{
	m_jInterface.callJavaVoidMethod(m_marioEnvObj, m_mIdTick);
}

void Benchmark::getEvaluationInfo(std::vector<int> &p_ret)
{
	jintArray a = (jintArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetEvalutationInfo, 0);

	m_jInterface.javaIntArrayToCArray(a, p_ret);

	m_jInterface.delLocalRef(a);
}

IBenchmark::Observation Benchmark::getEntireObservation(int p_zLevelScene, int p_zLevelEnemies)
{
	std::vector<int> lvlScene;
	std::vector<int> EnemiesScene;
	std::vector<float> mPos;
	std::vector<float> ePos;
	std::vector<int> mState;
	IBenchmark::Observation obs;


	jintArray serializedLvlScene = (jintArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetSerializedLevelSceneObservationZ, p_zLevelScene);
	
	m_jInterface.javaIntArrayToCArray(serializedLvlScene, obs.lvlScene);

	jintArray serializedEnemiesScene = (jintArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetSerializedEnemiesObservationZ, p_zLevelEnemies);
	 m_jInterface.javaIntArrayToCArray(serializedEnemiesScene, obs.enemyScene);

	jfloatArray marioPos = (jfloatArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetMarioPos, p_zLevelEnemies);
	m_jInterface.javaFloatArrayToCArray(marioPos, obs.marioPos);	

	jfloatArray enemiesPos = (jfloatArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetEnemiesPos, p_zLevelEnemies);
	m_jInterface.javaFloatArrayToCArray(enemiesPos, obs.enemyPos);

	jintArray marioState = (jintArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetMarioState, p_zLevelEnemies);
	m_jInterface.javaIntArrayToCArray(marioState, obs.marioState);

	
	return obs;


}

void Benchmark::getObservationDetails(std::vector<int> &p_ret)
{
	jintArray obsDet = (jintArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetObservationDetails, 0);

	m_jInterface.javaIntArrayToCArray(obsDet, p_ret);

	m_jInterface.delLocalRef(obsDet);
}

void Benchmark::performAction(const std::vector<int> &p_action)
{

	jbooleanArray action = m_jInterface.cIntArrayToJavaBoolArray(p_action, m_numberOfButtons);

	m_jInterface.callJavaVoidMethod(m_marioEnvObj, m_mIdPerformAction, action);


	m_jInterface.delLocalRef(action);
}

void Benchmark::getMethodIds()
{
	m_mIdReset = m_jInterface.getMethodID(m_marioEnvCl, "reset", "(Ljava/lang/String;)V");
	m_mIdIsLevelFinished = m_jInterface.getMethodID(m_marioEnvCl, "isLevelFinished", "()Z");
	m_mIdTick = m_jInterface.getMethodID(m_marioEnvCl, "tick", "()V");
	m_mIdGetEvalutationInfo = m_jInterface.getMethodID(m_marioEnvCl, "getEvaluationInfoAsInts", "()[I");
	m_mIdGetSerializedLevelSceneObservationZ = m_jInterface.getMethodID(m_marioEnvCl, "getSerializedLevelSceneObservationZ", "(I)[I");
	m_mIdGetSerializedEnemiesObservationZ = m_jInterface.getMethodID(m_marioEnvCl, "getSerializedEnemiesObservationZ", "(I)[I");
	m_mIdGetObservationDetails = m_jInterface.getMethodID(m_marioEnvCl, "getObservationDetails", "()[I");
	m_mIdPerformAction = m_jInterface.getMethodID(m_marioEnvCl, "performAction", "([Z)V");
	m_mIdGetMarioPos = m_jInterface.getMethodID(m_marioEnvCl, "getMarioFloatPos", "()[F");
	m_mIdGetEnemiesPos = m_jInterface.getMethodID(m_marioEnvCl, "getEnemiesFloatPos", "()[F");
	m_mIdGetMarioState = m_jInterface.getMethodID(m_marioEnvCl, "getMarioState", "()[I");
}

void Benchmark::shutdown()
{
	m_jInterface.delLocalRef(m_marioEnvObj);
	m_jInterface.delLocalRef(m_marioEnvCl);
	m_jInterface.shutdownJava();
}

void IBenchmark::destroyBenchmark(IBenchmark *p_benchmark)
{
	p_benchmark->shutdown();
	delete p_benchmark;
}