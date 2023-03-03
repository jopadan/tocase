#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "tocase.h"

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " PATH..." << std::endl
		<< "Convert PATH names recursively to lowercase" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::filesystem::path argv_path[argc];

	for(int i=1; i < argc; i++)
	{
		argv_path[i] = argv[i];
		argv_path[i] = std::filesystem::tocase(argv_path[i], std::simple_uppercase, std::filesystem::recursive);
	}

	exit(EXIT_SUCCESS);
}
