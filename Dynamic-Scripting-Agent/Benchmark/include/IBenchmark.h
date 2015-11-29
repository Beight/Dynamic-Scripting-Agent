#pragma once
#include <vector>

class IBenchmark
{
public:
	struct Observation
	{
		std::vector<int> lvlScene;
		std::vector<int> enemyScene;
		std::vector<int> marioState;
		std::vector<float> marioPos;
		std::vector<float> enemyPos;
	};
	/*
	*	Creates the benchmark.
	*	
	*	@return: pointer to the created benchmark
	*/
	__declspec(dllexport) static IBenchmark *createBenchmark();

	/*
	*	Initializes the benchmark.
	*	
	*	@param p_numJavaOtions: Number of Java options to use when creating the JavaVM.
	*	@param ...: options for the creation of the JavaVM.
	*	@return: 0 on success, negative number on failure.
	*/
	virtual int init(int p_numJavaOptions, ...) = 0;

	/*
	*	Reset the benchmark.
	*	Use this to start a new simulation/level.
	*	
	*	@param p_options: Command line options for the benchmark, find avaiable commmands in the benchmark documentation.
	*/
	virtual void reset(const char* p_options) = 0;

	/*
	*	Checks if the level is finshied.
	*	A level counts as finished if the player reaches the goal, player dies or time runs out.
	*
	*	@returns: true if the level is finished otherwise false.
	*/
	virtual bool isLevelFinished() = 0;

	/*
	*	Updates the benchmark.
	*	Used to make the benchmark move forward with its simulation. 
	*/
	virtual void tick() = 0;

	/*
	*	Gets evaluation info based on the player performance.
	*	
	*	@return: Array with evalution info    
	*	Array[0] = Distance Passed Cells;
	*	Array[1] = Distance Passed Phys;
	*	Array[2] = Flowers Devoured;
	*	Array[3] = Kills By Fire;
	*	Array[4] = Kills By Shell;
	*	Array[5] = Kills By Stomp;
	*	Array[6] = Kills Total;
	*	Array[7] = Mario Mode;
	*	Array[8] = Mario Status;
	*	Array[9] = Mushrooms Devoured;
	*	Array[10] = Coins Gained;
	*	Array[11] = Time Left;
	*	Array[12] = Time Spent;
	*	Array[13] = Hidden Blocks Found;
	*/
	virtual void getEvaluationInfo(std::vector<int> &p_ret) = 0;

	//Don't know if i need this method in c++
	//virtual void buildpythontuple();

	/*
	*	Gets all exisitng observation data.
	*	Doesn't return the data or save it at the moment.
	*	The agent is supposed to use this data to decide what action to make.
	*	
	*	@param p_levelScene: Has to do with observation detail. Enter 1 to be safe.
	*	@param p_levelEnemies: Has to do with observation detail. Enter 0 to be safe.
	*/
	virtual Observation getEntireObservation(int p_zLevelScene, int p_zLevelEnemies) = 0;

	/*
	*	Gets details such as the agents receptivefield and poistion.
	*	
	*	@return: an array containing the details.
	*	Array[0] = Receptive field width;
	*	Array[1] = Receptive field height;
	*	Array[2] = Mario pos X.
	*	Array[3] = Mario pos Y.;
	*/
	virtual void getObservationDetails(std::vector<int> &p_ret) = 0;
	/*

	*/
	//void type is placeholder
	virtual void performAction(const std::vector<int> &p_action) = 0;
	/*

	*/
	__declspec(dllexport) static void destroyBenchmark(IBenchmark *p_benchmark);

private:
	virtual void shutdown() = 0;
	virtual void getMethodIds() = 0;

protected:
	virtual ~IBenchmark() {};

};
