#include "Benchmark.h"


IBenchmark *IBenchmark::createBenchmark()
{
	return new Benchmark();
}


Benchmark::Benchmark() : m_javaInterface(JavaInterface()),
						 m_EnvironmentClass(nullptr),
						 m_EnvironmentObject(nullptr),
						 m_numberOfButtons(0),
						 m_methodIDReset(nullptr),
						 m_methodIDIsLevelFinished(nullptr),
						 m_methodIDTick(nullptr),
						 m_methodIDGetEvalutationInfo(nullptr),
						 m_methodIDGetSerializedLevelSceneObservationZ(nullptr),
						 m_methodIDGetSerializedEnemiesObservationZ(nullptr),
						 m_methodIDGetObservationDetails(nullptr),
						 m_methodIDPerformAction(nullptr),
						 m_methodIDGetMarioPos(nullptr),
						 m_methodIDGetEnemiesPos(nullptr),
						 m_methodIDGetMarioState(nullptr)
{
}

Benchmark::~Benchmark()
{
}


int Benchmark::init(int p_numberOfJavaOptions, ...)
{
	m_numberOfButtons = 6;

	va_list args;
	va_start(args, p_numberOfJavaOptions);
	int res = m_javaInterface.initJava(p_numberOfJavaOptions, args);
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
	m_EnvironmentClass = m_javaInterface.createJavaClass("ch/idsia/benchmark/mario/environments/MarioEnvironment");
	if (m_EnvironmentClass == nullptr)
		return -1;

	jmethodID jmid = m_javaInterface.getStaticMethodID(m_EnvironmentClass, "getInstance", "()Lch/idsia/benchmark/mario/environments/MarioEnvironment;");

	m_EnvironmentObject = m_javaInterface.callJavaStaticObjectMethod(m_EnvironmentClass, jmid);
	if (m_EnvironmentObject == nullptr)
		return -1;

	getMethodIds();

	return 0;
}

void Benchmark::reset(const char *p_options)
{
	jobject options = m_javaInterface.cStringToJavaString(p_options);
	m_javaInterface.callJavaVoidMethod(m_EnvironmentObject, m_methodIDReset, options);
	m_javaInterface.deleteLocalRef(options);
}

bool Benchmark::isLevelFinished()
{
	return m_javaInterface.callJavaBooleanMethod(m_EnvironmentObject, m_methodIDIsLevelFinished);
}

void Benchmark::tick()
{
	m_javaInterface.callJavaVoidMethod(m_EnvironmentObject, m_methodIDTick);
}

void Benchmark::getEvaluationInfo(std::vector<int> &p_ret)
{
	jintArray jArray = (jintArray)m_javaInterface.callJavaObjectMethod(m_EnvironmentObject, m_methodIDGetEvalutationInfo, 0);

	m_javaInterface.javaIntArrayToVector(jArray, p_ret);

	m_javaInterface.deleteLocalRef(jArray);
}

IBenchmark::Observation Benchmark::getEntireObservation(int p_zLevelScene, int p_zLevelEnemies)
{
	IBenchmark::Observation observation;

	jintArray serializedLvlScene = (jintArray)m_javaInterface.callJavaObjectMethod(m_EnvironmentObject, m_methodIDGetSerializedLevelSceneObservationZ, p_zLevelScene);
	
	m_javaInterface.javaIntArrayToVector(serializedLvlScene, observation.levelScene);

	jintArray serializedEnemiesScene = (jintArray)m_javaInterface.callJavaObjectMethod(m_EnvironmentObject, m_methodIDGetSerializedEnemiesObservationZ, p_zLevelEnemies);
	 m_javaInterface.javaIntArrayToVector(serializedEnemiesScene, observation.enemyScene);

	jfloatArray marioPosition = (jfloatArray)m_javaInterface.callJavaObjectMethod(m_EnvironmentObject, m_methodIDGetMarioPos, p_zLevelEnemies);
	m_javaInterface.javaFloatArrayToVector(marioPosition, observation.marioPosition);

	jfloatArray enemiesPosition = (jfloatArray)m_javaInterface.callJavaObjectMethod(m_EnvironmentObject, m_methodIDGetEnemiesPos, p_zLevelEnemies);
	m_javaInterface.javaFloatArrayToVector(enemiesPosition, observation.enemyPosition);

	jintArray marioState = (jintArray)m_javaInterface.callJavaObjectMethod(m_EnvironmentObject, m_methodIDGetMarioState, p_zLevelEnemies);
	m_javaInterface.javaIntArrayToVector(marioState, observation.marioState);

	
	return observation;
}

void Benchmark::getObservationDetails(std::vector<int> &p_ret)
{
	jintArray observationDetails = (jintArray)m_javaInterface.callJavaObjectMethod(m_EnvironmentObject, m_methodIDGetObservationDetails, 0);

	m_javaInterface.javaIntArrayToVector(observationDetails, p_ret);

	m_javaInterface.deleteLocalRef(observationDetails);
}

void Benchmark::performAction(const std::vector<int> &p_action)
{

	jbooleanArray action = m_javaInterface.intVectorToJavaBoolArray(p_action, m_numberOfButtons);

	m_javaInterface.callJavaVoidMethod(m_EnvironmentObject, m_methodIDPerformAction, action);


	m_javaInterface.deleteLocalRef(action);
}

void Benchmark::getMethodIds()
{
	m_methodIDReset									= m_javaInterface.getMethodID(m_EnvironmentClass, "reset", "(Ljava/lang/String;)V");
	m_methodIDIsLevelFinished						= m_javaInterface.getMethodID(m_EnvironmentClass, "isLevelFinished", "()Z");
	m_methodIDTick									= m_javaInterface.getMethodID(m_EnvironmentClass, "tick", "()V");
	m_methodIDGetEvalutationInfo					= m_javaInterface.getMethodID(m_EnvironmentClass, "getEvaluationInfoAsInts", "()[I");
	m_methodIDGetSerializedLevelSceneObservationZ	= m_javaInterface.getMethodID(m_EnvironmentClass, "getSerializedLevelSceneObservationZ", "(I)[I");
	m_methodIDGetSerializedEnemiesObservationZ		= m_javaInterface.getMethodID(m_EnvironmentClass, "getSerializedEnemiesObservationZ", "(I)[I");
	m_methodIDGetObservationDetails					= m_javaInterface.getMethodID(m_EnvironmentClass, "getObservationDetails", "()[I");
	m_methodIDPerformAction							= m_javaInterface.getMethodID(m_EnvironmentClass, "performAction", "([Z)V");
	m_methodIDGetMarioPos							= m_javaInterface.getMethodID(m_EnvironmentClass, "getMarioFloatPos", "()[F");
	m_methodIDGetEnemiesPos							= m_javaInterface.getMethodID(m_EnvironmentClass, "getEnemiesFloatPos", "()[F");
	m_methodIDGetMarioState							= m_javaInterface.getMethodID(m_EnvironmentClass, "getMarioState", "()[I");
}

void Benchmark::shutdown()
{
	m_javaInterface.deleteLocalRef(m_EnvironmentObject);
	m_javaInterface.deleteLocalRef(m_EnvironmentClass);
	m_javaInterface.shutdownJava();
}

void IBenchmark::destroyBenchmark(IBenchmark *p_benchmark)
{
	p_benchmark->shutdown();
	delete p_benchmark;
}