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
	

	if (res < 0)
	{
		return res;
	}
	
	/*
	  Could have the argument as parameter in this method but  
	  the benchmark will awalys use the same environment in this project
	  so there's no need to let the user change it.
	*/
	m_marioEnvCl = m_jInterface.createJavaClass("ch/idsia/benchmark/mario/environments/MarioEnvironment");
	jmethodID mid = m_jInterface.getStaticMethodID(m_marioEnvCl, "getInstance", "()Lch/idsia/benchmark/mario/environments/MarioEnvironment;");
	m_marioEnvObj = m_jInterface.callJavaStaticObjectMethod(m_marioEnvCl, mid);

	getMethodIds();



	return 0;
}

void Benchmark::reset(const char *p_options)
{
	jobject options = m_jInterface.cStringToJavaString(p_options);
	m_jInterface.callJavaVoidMethod(m_marioEnvObj, m_mIdReset, options);
}

bool Benchmark::isLevelFinished()
{
	return m_jInterface.callJavaBooleanMethod(m_marioEnvObj, m_mIdIsLevelFinished);
}

void Benchmark::tick()
{
	m_jInterface.callJavaVoidMethod(m_marioEnvObj, m_mIdTick);
}

int *Benchmark::getEvaluationInfo()
{
	jintArray a = (jintArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetEvalutationInfo);

	if (a == nullptr)
		return nullptr;

	return m_jInterface.javaIntArrayToCArray(a);
}

void Benchmark::getEntireObservation(int p_zLevelScene, int p_zLevelEnemies)
{
	jintArray serializedLvlScene = (jintArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetSerializedLevelSceneObservationZ, p_zLevelScene);
	int *lvlScene = m_jInterface.javaIntArrayToCArray(serializedLvlScene);

	jintArray serializedEnemiesScene = (jintArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetSerializedEnemiesObservationZ, p_zLevelEnemies);
	int *EnScene = m_jInterface.javaIntArrayToCArray(serializedEnemiesScene);

	jfloatArray marioPos = (jfloatArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetMarioPos, p_zLevelEnemies);
	float *mPos = m_jInterface.javaFloatArrayToCArray(marioPos);

	jfloatArray enemiesPos = (jfloatArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetEnemiesPos, p_zLevelEnemies);
	float *EnPos = m_jInterface.javaFloatArrayToCArray(enemiesPos);

	jintArray marioState = (jintArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetMarioState, p_zLevelEnemies);
	int *mState = m_jInterface.javaIntArrayToCArray(marioState);



	delete[] lvlScene;
	delete[] EnScene;
	delete[] mPos;
	delete[] mState;
	delete[] EnPos;
	//m_jInterface.delLocalRef(serializedLvlScene);
	//m_jInterface.delLocalRef(serializedEnemiesScene);
	//m_jInterface.delLocalRef(marioPos);
	//m_jInterface.delLocalRef(enemiesPos);
	//m_jInterface.delLocalRef(marioState);
	//return data to environment class somwhow....
	//1. send in parameters as refernces and modify values in the method.
	//2. create a struct and return it.
}

int *Benchmark::getObservationDetails()
{
	jintArray obsDet = (jintArray)m_jInterface.callJavaObjectMethod(m_marioEnvObj, m_mIdGetObservationDetails, 0);

	int *details = m_jInterface.javaIntArrayToCArray(obsDet);

	return details;
}

void Benchmark::performAction(int *p_action)
{
	jboolean *ptr = new jboolean[m_numberOfButtons];
	jbooleanArray action = m_jInterface.cIntArrayToJavaBoolArray(p_action, ptr, m_numberOfButtons);

	m_jInterface.callJavaVoidMethod(m_marioEnvObj, m_mIdPerformAction, action);

	
	//m_jInterface.releaseBoolArrayElem(action, ptr, 0);
	m_jInterface.delLocalRef(action);
	delete ptr;
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
	m_jInterface.shutdownJava();
}

void IBenchmark::destroyBenchmark(IBenchmark *p_benchmark)
{
	p_benchmark->shutdown();
	delete p_benchmark;
}