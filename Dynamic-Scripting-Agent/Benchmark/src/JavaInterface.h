#pragma once

#include <jni.h>

class JavaInterface
{
public:
	JavaInterface();
	~JavaInterface();

	/*
	
	*/
	int initJava(int p_nOptions, va_list p_argList);
	/*

	*/
	jclass createJavaClass(const char *p_javaClassName);
	/*

	*/
	jmethodID getMethodID(const jclass &p_javaClass, const char *p_mName, const char *p_mSig);
	/*

	*/
	jmethodID getStaticMethodID(const jclass &p_javaClass, const char *p_mName, const char *p_mSig);
	/*

	*/
	void callJavaVoidMethod(const jobject &p_javaObject, const jmethodID p_methodId, ...);
	/*

	*/
	int callJavaIntMethod(const jobject &p_javaObject, const jmethodID p_methodId, ...);
	/*

	*/
	bool callJavaBooleanMethod(const jobject &p_javaObject, const jmethodID p_methodId, ...);
	/*

	*/
	jobject callJavaObjectMethod(const jobject &p_javaObject, const jmethodID p_methodId, ...);
	/*

	*/
	jobject callJavaStaticObjectMethod(const jclass &p_javaClass, const jmethodID p_methodId, ...);
	/*

	*/
	void delLocalRef(jobject p_delObj);
	/*

	*/
	void delGlobalRef(jobject p_delObj);
	/*

	*/
	void releaseIntArrayElem(jintArray &p_delarray, jint *p_elems, int mode);
	/*

	*/
	void releaseFloatArrayElem(jfloatArray &p_delarray, jfloat *p_elems, int mode);
	/*

	*/
	void releaseBoolArrayElem(jbooleanArray &p_delarray, jboolean *p_elems, int mode);
	/*

	*/
	int *javaIntArrayToCArray(jintArray &p_array);
	/*

	*/
	float *javaFloatArrayToCArray(jfloatArray &p_array);
	/*

	*/
	jbooleanArray cIntArrayToJavaBoolArray(int *p_array, jboolean *p_aPtr ,const int p_aSize);
	/*

	*/
	jobject cStringToJavaString(const char *p_string);
	/*

	*/
	void shutdownJava();

private:
	JNIEnv_ *m_javaEnv;
	JavaVM *m_javaVM;
	

};