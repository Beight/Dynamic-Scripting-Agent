#pragma once

#include <jni.h>
#include <memory>
#include <vector>

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
	*	@param p_numberOfOptions: Number of options that will be used when creating the JavaVM.
	*	@param p_optionList: Options that are used as options when creating the JavaVM. Ex: "Djava-class.path="
	*	@return: 0 if successful, -1 or 1 if failed.
	*/
	int initJava(int p_numberOfOptions, va_list p_optionList);

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
	*	@param p_methodName: Name of the method.
	*	@param p_methodSignature: Signature of the method. 
	*	@return: The methods ID.
	*/
	jmethodID getMethodID(const jclass &p_javaClass, const char *p_methodName, const char *p_methodSignature);

	/*
	*	Gets a method ID for a static method.
	*	If the method is not found an exception is thrown,
	*	catch it with jthrowable.
	*
	*	@param p_javaClass: Java class that the method belongs to.
	*	@param p_methodName: Name of the method.
	*	@param p_methodSignature: Signature of the method.
	*	@return: The methods ID.
	*/
	jmethodID getStaticMethodID(const jclass &p_javaClass, const char *p_methodName, const char *p_methodSignature);

	/*
	*	Calls a void method from a java object.
	*	If the call fails an exception is thrown,
	*	catch it with jthrowable
	*
	*	@param p_javaObject: The Java object the method belongs to.
	*	@param p_methodID: ID of the method to call.
	*	@param ...: Parameters to send to the Java method.
	*/
	void callJavaVoidMethod(const jobject &p_javaObject, const jmethodID p_methodID, ...);

	/*
	*	Calls a int method from a java object.
	*	If the call fails an exception is thrown,
	*	catch it with jthrowable
	*
	*	@param p_javaObject: The Java object the method belongs to.
	*	@param p_methodID: ID of the method to call.
	*	@param ...: Parameters to send to the Java method.
	*	@return: The int value that was returned from the Java method.
	*/
	int callJavaIntMethod(const jobject &p_javaObject, const jmethodID p_methodID, ...);

	/*
	*	Calls a boolean method from a java object.
	*	If the call fails an exception is thrown,
	*	catch it with jthrowable
	*
	*	@param p_javaObject: The Java object the method belongs to.
	*	@param p_methodID: ID of the method to call.
	*	@param ...: Parameters to send to the Java method.
	*	@return: The bool value that was returned from the Java method.
	*/
	bool callJavaBooleanMethod(const jobject &p_javaObject, const jmethodID p_methodID, ...);

	/*
	*	Calls a Java object method from a java object.
	*	If the call fails an exception is thrown,
	*	catch it with jthrowable
	*
	*	@param p_javaObject: The Java object the method belongs to.
	*	@param p_methodID: ID of the method to call.
	*	@param ...: Parameters to send to the Java method.
	*	@return: A pointer to the returned Java object.
	*/
	jobject callJavaObjectMethod(const jobject &p_javaObject, const jmethodID p_methodID, ...);

	/*
	*	Calls a static Java object method from a java object.
	*	If the call fails an exception is thrown,
	*	catch it with jthrowable
	*
	*	@param p_javaClass: The Java Class the method belongs to.
	*	@param p_methodID: ID of the method to call.
	*	@param ...: Parameters to send to the Java method.
	*	@return: A pointer to the returned static Java object.
	*/
	jobject callJavaStaticObjectMethod(const jclass &p_javaClass, const jmethodID p_methodID, ...);

	/*
	*	Deletes a local reference for the JavaVM,
	*	telling the JavaVM we don't need it anymore.
	*	
	*	@param p_ObjectToDelete: Java Object to delete reference to.
	*/
	void delLocalRef(jobject p_objectToDelete);

	/*
	*	Deletes a global reference for the JavaVM,
	*	telling the JavaVM we don't need it anymore.
	*
	*	@param p_ObjectToDelete: Java Object to delete reference to.
	*/
	void delGlobalRef(jobject p_objectToDelete);

	/*
	*	Releases the elements of a Java int array,
	*	telling the JavaVM we don't need them anymore.
	*	
	*	@param p_arrayToDelete: Array containing the elements to be released.
	*	@param p_elements: A pointer to the elements in the array.
	*	@param p_mode: Which mode to delete it with, 0, JNI_COMMIT or JNI_ABORT. Consult JNI documentation for explation of the three.
	*/
	void releaseIntArrayElem(jintArray &p_arrayToDelete, jint *p_elements, int p_mode);

	/*
	*	Releases the elements of a Java float array,
	*	telling the JavaVM we don't need them anymore.
	*
	*	@param p_arrayToDelete: Array containing the elements to be released.
	*	@param p_elements: A pointer to the elements in the array.
	*	@param p_mode: Which mode to delete it with, 0, JNI_COMMIT or JNI_ABORT. Consult JNI documentation for explation of the three.
	*/
	void releaseFloatArrayElem(jfloatArray &p_arrayToDelete, jfloat *p_elements, int p_mode);

	/*
	*	Releases the elements of a Java boolean array,
	*	telling the JavaVM we don't need them anymore.
	*
	*	@param p_arrayToDelete: Array containing the elements to be released.
	*	@param p_elements: A pointer to the elements in the array.
	*	@param p_mode: Which mode to delete it with, 0, JNI_COMMIT or JNI_ABORT. Consult JNI documentation for explation of the three.
	*/
	void releaseBoolArrayElem(jbooleanArray &p_arrayToDelete, jboolean *p_elements, int p_mode);

	/*
	*	Converts an Java int array into a int vector.
	*
	*	@param p_array: Array to be converted
	*	@param p_ret: vector filled with values from the java array
	*/
	void javaIntArrayToCArray(jintArray &p_array, std::vector<int> &p_ret);

	/*
	*	Converts an Java float array into a float vector.
	*
	*	@param p_array: Array to be converted
	*	@param p_ret: vector filled with values from the java array
	*/
	void javaFloatArrayToCArray(jfloatArray &p_array, std::vector<float> &p_ret);

	/*
	*	Converts an C int array into a Java boolean array.
	*
	*	@param p_array: Array to be converted
	*	@param p_aPtr: A Pointer that will point to the coverted array.
	*	@param p_aSize: Size of the array to be converted.
	*	@return: A Java boolean array.
	*/
	jbooleanArray cIntArrayToJavaBoolArray(const std::vector<int> &p_array, const int p_aSize);

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
	std::shared_ptr<JNIEnv_> m_javaEnv;
	std::shared_ptr<JavaVM> m_javaVM;
	

};