


class IJVM
{
	__declspec(dllexport) static IJVM *createJVM();

	virtual void initJVM() = 0;

	virtual void initBenchmark() = 0;

	virtual void createMarioEnvironment(const char *p_javaClassName) = 0;

	virtual void reset(char* p_options) = 0;

	virtual bool isLevelFinished() = 0;

	virtual void tick() = 0;

	//void type is placeholder.
	virtual void getEvaluationInfo() = 0;

	//Don't know if i need this method in c++
	//virtual void buildpythontuple();

	//void type is placeholder
	virtual void getEntireObservation(int p_zLevelScene, int p_zLevelEnemies) = 0;

	//void type is placeholder
	virtual void getObservationDetails();

	//void type is placeholder
	virtual void performAction(int *p_action);

	__declspec(dllexport) void deleteJVM();
};




