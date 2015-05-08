#include "Environment.h"
#include <stdlib.h>
#include <fstream>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define SET_DBG_FLAG _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF )
#define DUMP_LEAKS _CrtDumpMemoryLeaks()


int main(int argc, char argv[])
{
	SET_DBG_FLAG;

	//std::ofstream logfile("logfile.txt", std::ofstream::trunc);
	try
	{
		Environment env = Environment();
		if (env.init() < 0)
			return -1;

		env.run();
		env.destroy();
	}
	catch (std::exception& err)
	{
		//logfile << err.what();
		//logfile.close();
		return EXIT_FAILURE;
	}
	catch (...)
	{
		//logfile.close();
		return EXIT_FAILURE;
	}

	//logfile.close();


	DUMP_LEAKS;
	return EXIT_SUCCESS;
}