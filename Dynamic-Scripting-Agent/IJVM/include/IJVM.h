#pragma once


class IJVM
{
public:
	__declspec(dllexport) static IJVM *createJVM();

	virtual void init() = 0;

	virtual void initBenchmark() = 0;

	virtual void createMarioEnvironment(const char *p_javaClassName) = 0;

	virtual void reset(const char* p_options) = 0;

	virtual bool isLevelFinished() = 0;

	virtual void tick() = 0;

	virtual int *getEvaluationInfo() = 0;

	//Don't know if i need this method in c++
	//virtual void buildpythontuple();

	//void type is placeholder
	virtual void getEntireObservation(int p_zLevelScene, int p_zLevelEnemies) = 0;

	virtual int *getObservationDetails() = 0;

	//void type is placeholder
	virtual void performAction(int *p_action) = 0;

	__declspec(dllexport) static void deleteJVM(IJVM *p_JVM);
private:
	virtual void shutdown() = 0;
protected:
	virtual ~IJVM() {};

};




