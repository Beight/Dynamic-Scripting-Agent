#include "Environment.h"
#include <stdlib.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define SET_DBG_FLAG _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF )
#define DUMP_LEAKS _CrtDumpMemoryLeaks()


int main(int argc, char argv[])
{
	SET_DBG_FLAG;
	Environment env = Environment();
	env.init();
	env.run();
	env.destroy();


	//system("pause");
	DUMP_LEAKS;
	return 0;
}