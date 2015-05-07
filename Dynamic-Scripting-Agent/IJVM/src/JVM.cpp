#include "JVM.h"
#include <iostream>


IJVM *IJVM::createJVM()
{
	return new JVM();
}

JVM::JVM() : m_env(nullptr), 
			 m_JVM(nullptr), 
			 m_jclass(nullptr),
			 m_jobject(nullptr),
			 m_numberOfButtons(0),
			 m_idReset(nullptr),
			 m_idIsLevelFinished(nullptr),
			 m_idTick(nullptr),
			 m_idGetEvalutationInfo(nullptr),
			 m_idGetSerializedLevelSceneObservationZ(nullptr),
			 m_idGetSerializedEnemiesObservationZ(nullptr),
			 m_idGetObservationDetails(nullptr),
			 m_idPerformAction(nullptr),
			 m_idGetMarioPos(nullptr),
			 m_idGetEnemiesPos(nullptr),
			 m_idGetMarioState(nullptr)
{

}

JVM::~JVM()
{
}

void JVM::init()
{
	m_numberOfButtons = 6;
	if (m_env != nullptr)
	{
		std::cerr << "WARNING: Attempt to create JVM environment aborted. There already exists a JVM environment! \n";
		return;
	}	
	
	JavaVMOption *options = new JavaVMOption[2];
	options[0].optionString = "-Djava.class.path=D:\\ExamensArbete\\Mario-AI-Benchmark\\build\\classes";
	options[1].optionString = "-Djava.library.path=D:\\ExamensArbete\\Mario-AI-Benchmark\\lib";

	JavaVMInitArgs vmArgs;
	vmArgs.version = JNI_VERSION_1_8;
	vmArgs.options = options;
	vmArgs.nOptions = 2;

	jint result;
	result = JNI_CreateJavaVM(&m_JVM, (void**)&m_env, &vmArgs);

	if (result < 0)
	{
		std::cerr << "Error: Creating Java Virtual Machine failed! \n";
		delete[] options;
		return;
	}
	delete[] options;


}

void JVM::initBenchmark()
{
	m_idReset = getMethodID("reset", "(Ljava/lang/String;)V");
	m_idIsLevelFinished = getMethodID("isLevelFinished", "()Z");
	m_idTick = getMethodID("tick", "()V");
	m_idGetEvalutationInfo = getMethodID("getEvaluationInfoAsInts", "()[I");
	m_idGetSerializedLevelSceneObservationZ = getMethodID("getSerializedLevelSceneObservationZ", "(I)[I");
	m_idGetSerializedEnemiesObservationZ = getMethodID("getSerializedEnemiesObservationZ", "(I)[I");
	m_idGetObservationDetails = getMethodID("getObservationDetails", "()[I");
	m_idPerformAction = getMethodID("performAction", "([Z)V");
	m_idGetMarioPos = getMethodID("getMarioFloatPos", "()[F");
	m_idGetEnemiesPos = getMethodID("getEnemiesFloatPos", "()[F");
	m_idGetMarioState = getMethodID("getMarioState", "()[I");
}

void JVM::createMarioEnvironment(const char *p_javaClassName)
{
	m_jclass = m_env->FindClass(p_javaClassName);
	if (m_jclass == nullptr)
	{
		std::cerr << "Error: Can't find java class " << p_javaClassName << ".\n";
		javaError();
	}
	
	jmethodID jmid = m_env->GetStaticMethodID(m_jclass, "getInstance", "()Lch/idsia/benchmark/mario/environments/MarioEnvironment;");
	if (jmid == nullptr)
	{
		std::cerr << "Error: Can't find static method getInstance for " << p_javaClassName << "\n";
		javaError();
	}
	m_jobject = m_env->CallStaticObjectMethod(m_jclass, jmid);
	if (m_jobject == nullptr)
	{
		std::cerr << "Error: Can't create object from java class" << p_javaClassName << "\n";
		javaError();
	}


	initBenchmark();
}

void JVM::reset(const char *p_options)
{
	jobject options = m_env->NewStringUTF(p_options);
	m_env->CallVoidMethod(m_jobject, m_idReset, options);
	m_env->DeleteLocalRef(options);
}

bool JVM::isLevelFinished()
{
	return m_env->CallBooleanMethod(m_jobject, m_idIsLevelFinished);
}

void JVM::tick()
{
	m_env->CallVoidMethod(m_jobject, m_idTick);
}

int *JVM::getEvaluationInfo()
{
	jintArray a = (jintArray)m_env->CallObjectMethod(m_jobject, m_idGetEvalutationInfo);
	if (a == nullptr)
	{
		//std::cerr <<  "Getting the Mario's status failed! \n";
		return nullptr;
	}
	jint *pa = m_env->GetIntArrayElements(a, 0);
	jsize aLength = m_env->GetArrayLength(a);

	int *evaluation = new int[aLength];
	for (int i = 0; i < (int)aLength; i++)
		evaluation[i] = pa[i];

	
	m_env->ReleaseIntArrayElements(a, pa, 0);
	m_env->DeleteLocalRef(a);
	
	return evaluation;
}

void JVM::getEntireObservation(int p_zLevelScene, int p_zLevelEnemies)
{
	jintArray serializedLvlScene = (jintArray)m_env->CallObjectMethod(m_jobject, m_idGetSerializedLevelSceneObservationZ, p_zLevelScene);

	jintArray serializedEnemiesScene = (jintArray)m_env->CallObjectMethod(m_jobject, m_idGetSerializedEnemiesObservationZ, p_zLevelEnemies);

	jfloatArray marioPos = (jfloatArray)m_env->CallObjectMethod(m_jobject, m_idGetMarioPos, p_zLevelEnemies);

	jfloatArray enemiesPos = (jfloatArray)m_env->CallObjectMethod(m_jobject, m_idGetEnemiesPos, p_zLevelEnemies);

	jintArray marioState = (jintArray)m_env->CallObjectMethod(m_jobject, m_idGetMarioState, p_zLevelEnemies);

	//return data to environment class somwhow....
	//1. send in parameters as refernces and modify values in the method.
	//2. create a struct and return it.

	m_env->DeleteLocalRef(serializedLvlScene);
	m_env->DeleteLocalRef(serializedEnemiesScene);
	m_env->DeleteLocalRef(marioPos);
	m_env->DeleteLocalRef(enemiesPos);
	m_env->DeleteLocalRef(marioState);
}

int *JVM::getObservationDetails()
{
	jintArray obsDet = (jintArray)m_env->CallObjectMethod(m_jobject, m_idGetObservationDetails, 0);
	if (obsDet == nullptr)
		return nullptr;

	jint *pObsDet = m_env->GetIntArrayElements(obsDet, 0);
	jsize Length = m_env->GetArrayLength(obsDet);

	int *details = new int[Length];
	for (int i = 0; i < (int)Length; i++)
		details[i] = pObsDet[i];



	m_env->DeleteLocalRef(obsDet);

	return details;
}

void JVM::performAction(int *p_action)
{
	const jsize size = m_numberOfButtons;
	jbooleanArray actionArray = m_env->NewBooleanArray(size);
	jboolean *cAction = m_env->GetBooleanArrayElements(actionArray, 0);

	for (int i = 0; i < m_numberOfButtons; i++)
		cAction[i] = p_action[i];

	m_env->CallVoidMethod(m_jobject, m_idPerformAction, actionArray);

	m_env->ReleaseBooleanArrayElements(actionArray, cAction, 0);
	m_env->DeleteLocalRef(actionArray);

}

jmethodID JVM::getMethodID(const char *p_mName, const char *p_mSig)
{
	jmethodID mid = m_env->GetMethodID(m_jclass, p_mName, p_mSig);
	if (mid == nullptr)
	{
		std::cerr << "Error: Can't find java method " << p_mName << " with signature " << p_mSig << "\n";
		javaError();
	}
	else
	{
		std::cout << "Java method " << p_mName << " found! id: " << mid << "\n";
	}

	return mid;
}

void JVM::shutdown()
{
	if (m_JVM != nullptr)
	{
		m_JVM->DestroyJavaVM();
		m_JVM = nullptr;	
	}
	m_env = nullptr;
}

void IJVM::deleteJVM(IJVM *p_JVM)
{
	p_JVM->shutdown();
	delete p_JVM;
}

void JVM::javaError()
{
	std::cerr << "Java Error, shutting down JVM. \n";
	if (m_env->ExceptionOccurred())
		m_env->ExceptionDescribe();
	shutdown();
}