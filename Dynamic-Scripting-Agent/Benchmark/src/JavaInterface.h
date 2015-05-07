#pragma once

#include <jni.h>

class JavaInterface
{
public:
	JavaInterface();
	~JavaInterface();

	int initJava(int p_nOptions, ...);
	jclass createJavaClass(const char *p_javaClassName);
	jmethodID getMethodID(const jclass &p_javaClass, const char *p_mName, const char *p_mSig);
	jmethodID getStaticMethodID(const jclass &p_javaClass, const char *p_mName, const char *p_mSig);
	void callJavaVoidMethod(const jobject &p_javaObject, const jmethodID &p_methodId, ...);
	int callJavaIntMethod(const jobject &p_javaObject, const jmethodID &p_methodId, ...);
	bool callJavaBooleanMethod(const jobject &p_javaObject, const jmethodID &p_methodId, ...);
	jobject callJavaObjectMethod(const jobject &p_javaObject, const jmethodID &p_methodId, ...);
	jobject callJavaStaticObjectMethod(const jclass &p_javaClass, const jmethodID &p_methodId, ...);



	///int *javaIntArrayToCArray(jarray p_array);
	///jintArray cIntArrayToJavaIntArray(int *p_array);
	///float *javaFloatArrayToCfloatArray(jarray p_array);
	///jfloatArray cFloatArrayToJavaFloatArray(float *p_array);



	void shutdownJava();

private:
	JNIEnv_ *m_javaEnv;
	JavaVM *m_javaVM;
	

};