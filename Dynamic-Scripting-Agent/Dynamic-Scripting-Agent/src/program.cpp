#include "Environment.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>



#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define SET_DBG_FLAG _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF )
#define DUMP_LEAKS _CrtDumpMemoryLeaks()


int main(int argc, char argv[])
{
	SET_DBG_FLAG;
	Environment env = Environment();
	try
	{
		
		if (env.init() < 0)
		{
			env.destroy();
			return EXIT_FAILURE;
		}

		env.run();
		env.destroy();
	}
	catch (std::exception& err)
	{
		
		std::cerr << err.what() << "\n";
		env.destroy();
		return EXIT_FAILURE;
	}
	catch (...)
	{
		env.destroy();
		return EXIT_FAILURE;
	}


	DUMP_LEAKS;
	return EXIT_SUCCESS;
}