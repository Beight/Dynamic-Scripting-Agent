#include "JavaInterface.h"
#include <iostream>

JavaInterface::JavaInterface() : m_javaEnv(nullptr),
								 m_javaVM(nullptr)
{

}

JavaInterface::~JavaInterface()
{
}

int JavaInterface::initJava(int p_nOptions, ...)
{
	std::cout << "Initializing Java.. \n";
	if (m_javaEnv != nullptr)
	{
		std::cerr << "WARNING: Attempt to create Java environment aborted. There already exists a Java environment! \n";
		return 0;
	}
	JavaVMInitArgs vmArgs;
	vmArgs.version = JNI_VERSION_1_8;
	vmArgs.ignoreUnrecognized = JNI_FALSE;
	vmArgs.nOptions = p_nOptions;

	JavaVMOption *options = nullptr;
	
	if (p_nOptions > 0)
	{
		options = new JavaVMOption[p_nOptions];
		va_list vl;
		va_start(vl, p_nOptions);
		for (int i = 0; i < p_nOptions; i++)
			options[i].optionString = va_arg(vl, char*);

		va_end(vl);

		vmArgs.options = options;
	}
	

	//options[0].optionString = "-Djava.class.path=D:\\ExamensArbete\\Mario-AI-Benchmark\\build\\classes";
	//options[1].optionString = "-Djava.library.path=D:\\ExamensArbete\\Mario-AI-Benchmark\\lib";
	


	jint result;
	result = JNI_CreateJavaVM(&m_javaVM, (void**)&m_javaEnv, &vmArgs);

	if (result < 0)
	{
		std::cerr << "Error: Creating Java Virtual Machine failed! \n";
		if (options != nullptr)
			delete[] options;
		return -1;
	}
	if (options != nullptr);
		delete[] options;

	std::cout << "Initialization of Java finished. JVM created succesfully \n";

	return 0;
}

jclass JavaInterface::createJavaClass(const char *p_javaClassName)
{
	jclass javaClass = m_javaEnv->FindClass(p_javaClassName);
	if (m_javaEnv->ExceptionOccurred())
	{
		std::cerr << "Error: Can't find Java class " << p_javaClassName << ".\n";
		m_javaEnv->ExceptionDescribe();
	}
	
}

jmethodID JavaInterface::getMethodID(const jclass &p_javaClass, const char *p_mName, const char *p_mSig)
{
	jmethodID jmid = m_javaEnv->GetMethodID(p_javaClass, p_mName, p_mSig);
	if (m_javaEnv->ExceptionOccurred())
	{
		std::cerr << "Error: Can't find Java method id for " << p_mName << ".\n";
		m_javaEnv->ExceptionDescribe();
	}
	return jmid;
}

jmethodID JavaInterface::getStaticMethodID(const jclass &p_javaClass, const char *p_mName, const char *p_mSig)
{
	jmethodID jmid = m_javaEnv->GetStaticMethodID(p_javaClass, p_mName, p_mSig);
	if (m_javaEnv->ExceptionOccurred())
	{
		std::cerr << "Error: Can't find Java static method id for " << p_mName << ".\n";
		m_javaEnv->ExceptionDescribe();
	}
	return jmid;
}

void JavaInterface::callJavaVoidMethod(const jobject &p_javaObject, const jmethodID &p_methodId, ...)
{
	va_list arg;
	va_start(arg, p_methodId);
	m_javaEnv->CallVoidMethod(p_javaObject, p_methodId, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionOccurred())
	{
		std::cerr << "Error: Calling Java void method failed. Id: " << p_methodId << "\n";
		m_javaEnv->ExceptionDescribe();
	}
}

int JavaInterface::callJavaIntMethod(const jobject &p_javaObject, const jmethodID &p_methodId, ...)
{
	va_list arg;
	va_start(arg, p_methodId);
	jint javaInt = m_javaEnv->CallIntMethodV(p_javaObject, p_methodId, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionOccurred())
	{
		std::cerr << "Error: Calling Java int method failed. Id: " << p_methodId << "\n";
		m_javaEnv->ExceptionDescribe();
	}
	return javaInt;
}


bool JavaInterface::callJavaBooleanMethod(const jobject &p_javaObject, const jmethodID &p_methodId, ...)
{
	va_list arg;
	va_start(arg, p_methodId);
	jboolean javabool = m_javaEnv->CallBooleanMethodV(p_javaObject, p_methodId, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionOccurred())
	{
		std::cerr << "Error: Calling Java boolean method failed. Id: " << p_methodId << "\n";
		m_javaEnv->ExceptionDescribe();
	}
	return javabool;
}

jobject JavaInterface::callJavaObjectMethod(const jobject &p_javaObject, const jmethodID &p_methodId, ...)
{
	va_list arg;
	va_start(arg, p_methodId);
	jobject javabool = m_javaEnv->CallObjectMethod(p_javaObject, p_methodId, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionOccurred())
	{
		std::cerr << "Error: Calling Java object method failed. Id: " << p_methodId << "\n";
		m_javaEnv->ExceptionDescribe();
	}
	return javabool;
}

jobject JavaInterface::callJavaStaticObjectMethod(const jclass &p_javaClass, const jmethodID &p_methodId, ...)
{
	va_list arg;
	va_start(arg, p_methodId);
	jobject object = nullptr;
	object = m_javaEnv->CallStaticObjectMethodV(p_javaClass, p_methodId, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionOccurred())
	{
		std::cerr << "Error: Calling Java static object method failed. Id: " << p_methodId << "\n";
		m_javaEnv->ExceptionDescribe();
	}
	return object;
}

void JavaInterface::shutdownJava()
{
	if (m_javaVM != nullptr)
	{
		m_javaVM->DestroyJavaVM();
		m_javaVM = nullptr;
	}
	m_javaVM = nullptr;
}