#pragma once

#include <jni.h>

class JavaInterface
{
public:
	/*
	*	Constructor.
	*/
	JavaInterface();

	/*
	*	Destructor.
	*/
	~JavaInterface();

	/*
	*	Initializes the Java Virtual Machine.
	*	If a JavaVM already exists the method will return without 
	*   doing anything and reporting it as a success but a warning will be issued.
	*
	*	@param p_nOptions: Number of options that will be used when creating the JavaVM.
	*	@param p_optionList: Options that are used as options when creating the JavaVM. Ex: "Djava-class.path="
	*	@return: 0 if successful, -1 or 1 if failed.
	*/
	int initJava(int p_nOptions, va_list p_optionList);

	/*
	*	Creates a pointer to the specified Java class
	*	Throws an Java exception if the class can't be found,
	*	catch it with jthrowable.
	*	
	*	@param p_javaClassName: Name of the Java class to be pointed to.
	*	@return: A pointer to Java class with the name of the parameter.
	*/
	jclass createJavaClass(const char *p_javaClassName);

	/*
	*	Gets a method ID that is used to call the method.
	*	If the method is not found an exception is thrown,
	*	catch it with jthrowable.
	*
	*	@param p_javaClass: Java class that the method belongs to.
	*	@param p_mName: Name of the method.
	*	@param p_mSig: Signature of the method. 
	*	@return: The methods ID.
	*/
	jmethodID getMethodID(const jclass &p_javaClass, const char *p_mName, const char *p_mSig);

	/*
	*	Gets a method ID for a static method.
	*	If the method is not found an exception is thrown,
	*	catch it with jthrowable.
	*
	*	@param p_javaClass: Java class that the method belongs to.
	*	@param p_mName: Name of the method.
	*	@param p_mSig: Signature of the method.
	*	@return: The methods ID.
	*/
	jmethodID getStaticMethodID(const jclass &p_javaClass, const char *p_mName, const char *p_mSig);

	/*
	*	Calls a void method from a java object.
	*	If the call fails an exception is thrown,
	*	catch it with jthrowable
	*
	*	@param p_javaObject: The Java object the method belongs to.
	*	@param p_methodId: ID of the method to call.
	*	@param ...: Parameters to send to the Java method.
	*/
	void callJavaVoidMethod(const jobject &p_javaObject, const jmethodID p_methodId, ...);

	/*
	*	Calls a int method from a java object.
	*	If the call fails an exception is thrown,
	*	catch it with jthrowable
	*
	*	@param p_javaObject: The Java object the method belongs to.
	*	@param p_methodId: ID of the method to call.
	*	@param ...: Parameters to send to the Java method.
	*	@return: The int value that was returned from the Java method.
	*/
	int callJavaIntMethod(const jobject &p_javaObject, const jmethodID p_methodId, ...);

	/*
	*	Calls a boolean method from a java object.
	*	If the call fails an exception is thrown,
	*	catch it with jthrowable
	*
	*	@param p_javaObject: The Java object the method belongs to.
	*	@param p_methodId: ID of the method to call.
	*	@param ...: Parameters to send to the Java method.
	*	@return: The bool value that was returned from the Java method.
	*/
	bool callJavaBooleanMethod(const jobject &p_javaObject, const jmethodID p_methodId, ...);

	/*
	*	Calls a Java object method from a java object.
	*	If the call fails an exception is thrown,
	*	catch it with jthrowable
	*
	*	@param p_javaObject: The Java object the method belongs to.
	*	@param p_methodId: ID of the method to call.
	*	@param ...: Parameters to send to the Java method.
	*	@return: A pointer to the returned Java object.
	*/
	jobject callJavaObjectMethod(const jobject &p_javaObject, const jmethodID p_methodId, ...);

	/*
	*	Calls a static Java object method from a java object.
	*	If the call fails an exception is thrown,
	*	catch it with jthrowable
	*
	*	@param p_javaClass: The Java Class the method belongs to.
	*	@param p_methodId: ID of the method to call.
	*	@param ...: Parameters to send to the Java method.
	*	@return: A pointer to the returned static Java object.
	*/
	jobject callJavaStaticObjectMethod(const jclass &p_javaClass, const jmethodID p_methodId, ...);

	/*
	*	Deletes a local reference for the JavaVM,
	*	telling the JavaVM we don't need it anymore.
	*	
	*	@param p_delObj: Java Object to delete refernce to.
	*/
	void delLocalRef(jobject p_delObj);

	/*
	*	Deletes a global reference for the JavaVM,
	*	telling the JavaVM we don't need it anymore.
	*
	*	@param p_delObj: Java Object to delete refernce to.
	*/
	void delGlobalRef(jobject p_delObj);

	/*
	*	Releases the elements of a Java int array,
	*	telling the JavaVM we don't need them anymore.
	*	
	*	@param p_delarray: Array containing the elements to be released.
	*	@param p_elems: A pointer to the elements in the array.
	*	@param p_mode: Which mode to delete it with, 0, JNI_COMMIT or JNI_ABORT. Consult JNI documentation for explation of the three.
	*/
	void releaseIntArrayElem(jintArray &p_delarray, jint *p_elems, int p_mode);

	/*
	*	Releases the elements of a Java float array,
	*	telling the JavaVM we don't need them anymore.
	*
	*	@param p_delarray: Array containing the elements to be released.
	*	@param p_elems: A pointer to the elements in the array.
	*	@param p_mode: Which mode to delete it with, 0, JNI_COMMIT or JNI_ABORT. Consult JNI documentation for explation of the three.
	*/
	void releaseFloatArrayElem(jfloatArray &p_delarray, jfloat *p_elems, int p_mode);

	/*
	*	Releases the elements of a Java boolean array,
	*	telling the JavaVM we don't need them anymore.
	*
	*	@param p_delarray: Array containing the elements to be released.
	*	@param p_elems: A pointer to the elements in the array.
	*	@param p_mode: Which mode to delete it with, 0, JNI_COMMIT or JNI_ABORT. Consult JNI documentation for explation of the three.
	*/
	void releaseBoolArrayElem(jbooleanArray &p_delarray, jboolean *p_elems, int p_mode);

	/*
	*	Converts an Java int array into a C int array.
	*
	*	@param p_array: Array to be converted
	*	@return: Pointer to the int array containing the converted elememts
	*/
	int *javaIntArrayToCArray(jintArray &p_array);

	/*
	*	Converts an Java float array into a C float array.
	*
	*	@param p_array: Array to be converted
	*	@return: Pointer to the float array containing the converted elememts
	*/
	float *javaFloatArrayToCArray(jfloatArray &p_array);

	/*
	*	Converts an C int array into a Java boolean array.
	*
	*	@param p_array: Array to be converted
	*	@param p_aPtr: A Pointer that will point to the coverted array.
	*	@param p_aSize: Size of the array to be converted.
	*	@return: A Java boolean array.
	*/
	jbooleanArray cIntArrayToJavaBoolArray(int *p_array, jboolean *p_aPtr ,const int p_aSize);

	/*
	*	Converts a C string into a Java string which can be used as a parameter in a Java method call.
	*	
	*	@param p_string: string to be converted.
	*	@return: A jobject containing the converted string.
	*/
	jobject cStringToJavaString(const char *p_string);

	/*
	*	Destroys the JavaVM.
	*/
	void shutdownJava();

private:
	JNIEnv_ *m_javaEnv;
	JavaVM *m_javaVM;
	

};