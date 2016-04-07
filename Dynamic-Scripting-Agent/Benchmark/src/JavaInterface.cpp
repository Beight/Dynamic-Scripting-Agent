#include "JavaInterface.h"
#include <iostream>

JavaInterface::JavaInterface() : m_javaEnv(nullptr),
								 m_javaVM(nullptr)
{

}

JavaInterface::~JavaInterface()
{
}

int JavaInterface::initJava(int p_nOptions, va_list p_optionList)
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

	std::vector<JavaVMOption> options(p_nOptions);

	if (p_nOptions > 0)
	{	
		for (int i = 0; i < p_nOptions; i++)
		{
			options.at(i).optionString = va_arg(p_optionList, char*);
		}
		vmArgs.options = options.data();
	}



	jint result;
	result = JNI_CreateJavaVM((JavaVM**)&m_javaVM, (void**)&m_javaEnv, &vmArgs);

	if (result < 0)
	{
		std::cerr << "Error: Creating Java Virtual Machine failed! \n";
		options.clear();
		return result;
	}
	options.clear();

	std::cout << "Initialization of Java finished. JVM created succesfully. \n";

	return result;
}

jclass JavaInterface::createJavaClass(const char *p_javaClassName)
{
	jclass javaClass = m_javaEnv->FindClass(p_javaClassName);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Can't find Java class " << p_javaClassName << ".\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	else
		std::cout << "Java class " << p_javaClassName << " found.\n";

	return javaClass;
}

jmethodID JavaInterface::getMethodID(const jclass &p_javaClass, const char *p_mName, const char *p_mSig)
{
	jmethodID jmid = m_javaEnv->GetMethodID(p_javaClass, p_mName, p_mSig);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Can't find Java method id for " << p_mName << ".\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	else
		std::cout << "Java method " << p_mName << " found! id: " << jmid << "\n";
	
	return jmid;
}

jmethodID JavaInterface::getStaticMethodID(const jclass &p_javaClass, const char *p_mName, const char *p_mSig)
{
	jmethodID jmid = m_javaEnv->GetStaticMethodID(p_javaClass, p_mName, p_mSig);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Can't find Java static method id for " << p_mName << ".\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	else
		std::cout << "Java static method " << p_mName << " found! id: " << jmid << "\n";

	return jmid;
}

void JavaInterface::callJavaVoidMethod(const jobject &p_javaObject, const jmethodID p_methodId, ...)
{
	va_list arg;
	va_start(arg, p_methodId);
	m_javaEnv->CallVoidMethodV(p_javaObject, p_methodId, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Calling Java void method failed. Id: " << p_methodId << "\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
}

int JavaInterface::callJavaIntMethod(const jobject &p_javaObject, const jmethodID p_methodId, ...)
{
	va_list arg;
	va_start(arg, p_methodId);
	jint javaInt = m_javaEnv->CallIntMethodV(p_javaObject, p_methodId, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Calling Java int method failed. Id: " << p_methodId << "\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	return javaInt;
}


bool JavaInterface::callJavaBooleanMethod(const jobject &p_javaObject, const jmethodID p_methodId, ...)
{
	va_list arg;
	va_start(arg, p_methodId);
	jboolean javabool = m_javaEnv->CallBooleanMethodV(p_javaObject, p_methodId, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Calling Java boolean method failed. Id: " << p_methodId << "\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	return javabool;
}

jobject JavaInterface::callJavaObjectMethod(const jobject &p_javaObject, const jmethodID p_methodId, ...)
{
	va_list arg;
	va_start(arg, p_methodId);
	jobject javaObj = m_javaEnv->CallObjectMethodV(p_javaObject, p_methodId, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Calling Java object method failed. Id: " << p_methodId << "\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	return javaObj;
}

jobject JavaInterface::callJavaStaticObjectMethod(const jclass &p_javaClass, const jmethodID p_methodId, ...)
{
	va_list arg;
	va_start(arg, p_methodId);

	jobject javaObj = m_javaEnv->CallStaticObjectMethodV(p_javaClass, p_methodId, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Calling Java static object method failed. Id: " << p_methodId << "\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	return javaObj;
}

void JavaInterface::delLocalRef(jobject p_delObj)
{
	m_javaEnv->DeleteLocalRef(p_delObj);
}

void JavaInterface::delGlobalRef(jobject p_delObj)
{
	m_javaEnv->DeleteGlobalRef(p_delObj);
}

void JavaInterface::releaseIntArrayElem(jintArray &p_delarray, jint *p_elems, int p_mode)
{
	m_javaEnv->ReleaseIntArrayElements(p_delarray, p_elems, p_mode);
}

void JavaInterface::releaseFloatArrayElem(jfloatArray& p_delarray, jfloat *p_elems, int p_mode)
{
	m_javaEnv->ReleaseFloatArrayElements(p_delarray, p_elems, p_mode);
}

void JavaInterface::releaseBoolArrayElem(jbooleanArray &p_delarray, jboolean *p_elems, int p_mode)
{
	m_javaEnv->ReleaseBooleanArrayElements(p_delarray, p_elems, p_mode);
}

void JavaInterface::javaIntArrayToCArray(jintArray &p_array, std::vector<int> &p_ret)
{
	std::unique_ptr<jint> ptr(m_javaEnv->GetIntArrayElements(p_array, 0));
	jsize size = m_javaEnv->GetArrayLength(p_array);

	for (int i = 0; i < size; i++)
		p_ret.push_back(ptr.get()[i]);

	m_javaEnv->ReleaseIntArrayElements(p_array, ptr.release(), 0);
	m_javaEnv->DeleteLocalRef(p_array);
}


void JavaInterface::javaFloatArrayToCArray(jfloatArray &p_array, std::vector<float> &p_ret)
{
	std::unique_ptr<jfloat> ptr(m_javaEnv->GetFloatArrayElements(p_array, 0));
	jsize size = m_javaEnv->GetArrayLength(p_array);

	for (int i = 0; i < size; i++)
		p_ret.push_back(ptr.get()[i]);

	m_javaEnv->ReleaseFloatArrayElements(p_array, ptr.release(), 0);
	m_javaEnv->DeleteLocalRef(p_array);
}

jbooleanArray JavaInterface::cIntArrayToJavaBoolArray(const std::vector<int> &p_array, const int p_aSize)
{
	jbooleanArray ar = m_javaEnv->NewBooleanArray(p_aSize);
	std::vector<jboolean> arrayPtr(p_aSize);

	for (int i = 0; i < p_aSize; i++)
		arrayPtr.at(i) = p_array.at(i);

	m_javaEnv->SetBooleanArrayRegion(ar, 0, p_aSize, arrayPtr.data());

	return ar;
}

jobject JavaInterface::cStringToJavaString(const char *p_string)
{
	jobject str = m_javaEnv->NewStringUTF(p_string);
	return str;
}


void JavaInterface::shutdownJava()
{
	//if (m_javaVM != nullptr)
	//{
	//	m_javaVM->DestroyJavaVM();
	//}
}