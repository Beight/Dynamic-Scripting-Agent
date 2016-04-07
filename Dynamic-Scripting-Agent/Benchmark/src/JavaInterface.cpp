#include "JavaInterface.h"
#include <iostream>

JavaInterface::JavaInterface() : m_javaEnv(nullptr),
								 m_javaVM(nullptr)
{

}

JavaInterface::~JavaInterface()
{
}

int JavaInterface::initJava(int p_numberOfOptions, va_list p_optionList)
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
	vmArgs.nOptions = p_numberOfOptions;

	std::vector<JavaVMOption> options(p_numberOfOptions);

	if (p_numberOfOptions > 0)
	{	
		for (int i = 0; i < p_numberOfOptions; i++)
		{
			options.at(i).optionString = va_arg(p_numberOfOptions, char*);
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

jmethodID JavaInterface::getMethodID(const jclass &p_javaClass, const char *p_methodName, const char *p_methodSignature)
{
	jmethodID jmid = m_javaEnv->GetMethodID(p_javaClass, p_methodName, p_methodSignature);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Can't find Java method id for " << p_methodName << ".\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	else
		std::cout << "Java method " << p_methodName << " found! id: " << jmid << "\n";
	
	return jmid;
}

jmethodID JavaInterface::getStaticMethodID(const jclass &p_javaClass, const char *p_methodName, const char *p_methodSignature)
{
	jmethodID jmid = m_javaEnv->GetStaticMethodID(p_javaClass, p_methodName, p_methodSignature);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Can't find Java static method id for " << p_methodName << ".\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	else
		std::cout << "Java static method " << p_methodName << " found! id: " << jmid << "\n";

	return jmid;
}

void JavaInterface::callJavaVoidMethod(const jobject &p_javaObject, const jmethodID p_methodID, ...)
{
	va_list arg;
	va_start(arg, p_methodID);
	m_javaEnv->CallVoidMethodV(p_javaObject, p_methodID, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Calling Java void method failed. Id: " << p_methodID << "\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
}

int JavaInterface::callJavaIntMethod(const jobject &p_javaObject, const jmethodID p_methodID, ...)
{
	va_list arg;
	va_start(arg, p_methodID);
	jint javaInt = m_javaEnv->CallIntMethodV(p_javaObject, p_methodID, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Calling Java int method failed. Id: " << p_methodID << "\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	return javaInt;
}


bool JavaInterface::callJavaBooleanMethod(const jobject &p_javaObject, const jmethodID p_methodID, ...)
{
	va_list arg;
	va_start(arg, p_methodID);
	jboolean javabool = m_javaEnv->CallBooleanMethodV(p_javaObject, p_methodID, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Calling Java boolean method failed. Id: " << p_methodID << "\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	return javabool;
}

jobject JavaInterface::callJavaObjectMethod(const jobject &p_javaObject, const jmethodID p_methodID, ...)
{
	va_list arg;
	va_start(arg, p_methodID);
	jobject javaObj = m_javaEnv->CallObjectMethodV(p_javaObject, p_methodID, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Calling Java object method failed. Id: " << p_methodID << "\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	return javaObj;
}

jobject JavaInterface::callJavaStaticObjectMethod(const jclass &p_javaClass, const jmethodID p_methodID, ...)
{
	va_list arg;
	va_start(arg, p_methodID);
	jobject javaObj = m_javaEnv->CallStaticObjectMethodV(p_javaClass, p_methodID, arg);
	va_end(arg);
	if (m_javaEnv->ExceptionCheck())
	{
		std::cerr << "Error: Calling Java static object method failed. Id: " << p_methodID << "\n";
		m_javaEnv->ExceptionDescribe();
		m_javaEnv->ExceptionClear();
	}
	return javaObj;
}

void JavaInterface::deleteLocalRef(jobject p_objectToDelete)
{
	m_javaEnv->DeleteLocalRef(p_objectToDelete);
}

void JavaInterface::deleteGlobalRef(jobject p_objectToDelete)
{
	m_javaEnv->DeleteGlobalRef(p_objectToDelete);
}

void JavaInterface::releaseIntArrayElem(jintArray &p_arrayToDelete, jint *p_elements, int p_mode)
{
	m_javaEnv->ReleaseIntArrayElements(p_arrayToDelete, p_elements, p_mode);
}

void JavaInterface::releaseFloatArrayElem(jfloatArray& p_arrayToDelete, jfloat *p_elements, int p_mode)
{
	m_javaEnv->ReleaseFloatArrayElements(p_arrayToDelete, p_elements, p_mode);
}

void JavaInterface::releaseBoolArrayElem(jbooleanArray &p_arrayToDelete, jboolean *p_elements, int p_mode)
{
	m_javaEnv->ReleaseBooleanArrayElements(p_arrayToDelete, p_elements, p_mode);
}

void JavaInterface::javaIntArrayToVector(jintArray &p_array, std::vector<int> &p_ret)
{
	std::unique_ptr<jint> ptr(m_javaEnv->GetIntArrayElements(p_array, 0));
	jsize size = m_javaEnv->GetArrayLength(p_array);

	for (int i = 0; i < size; i++)
		p_ret.push_back(ptr.get()[i]);

	m_javaEnv->ReleaseIntArrayElements(p_array, ptr.release(), 0);
	m_javaEnv->DeleteLocalRef(p_array);
}


void JavaInterface::javaFloatArrayToVector(jfloatArray &p_array, std::vector<float> &p_ret)
{
	std::unique_ptr<jfloat> ptr(m_javaEnv->GetFloatArrayElements(p_array, 0));
	jsize size = m_javaEnv->GetArrayLength(p_array);

	for (int i = 0; i < size; i++)
		p_ret.push_back(ptr.get()[i]);

	m_javaEnv->ReleaseFloatArrayElements(p_array, ptr.release(), 0);
	m_javaEnv->DeleteLocalRef(p_array);
}

jbooleanArray JavaInterface::IntVectorToJavaBoolArray(const std::vector<int> &p_array, const int p_aSize)
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