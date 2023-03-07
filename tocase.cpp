#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <getopt.h>
#include <iostream>
#include <vector>
#include "tocase.h"

using namespace std;
using namespace std::filesystem;

static case_mode mode = simple_lowercase;
static traverse_mode traverse = std::filesystem::none;

bool config_args(int argc, char** argv)
{
	int c;
	while(1)
	{
		int option_index;

		static struct option long_options[] = {
			{ "recursive", no_argument, 0, 'r' },
			{ "case", required_argument, 0, 'c' },
			{ "file", required_argument, 0, 0 },
			{ NULL, 0, NULL, 0 },
		};

		c = getopt_long(argc, argv, "rc:", long_options, &option_index);
		if(c == -1)
			return false;

		switch(c)
		{
			case 'r':
				traverse = std::filesystem::recursive;
				break;
			case 'c':
				mode = case_mode_from_str[std::string(optarg)];
				break;
			default:
				return false;
				break;
		}
	}
	return true;
}

int main(int argc, char** argv)
{
	if(argc < 2 || !config_args(argc, argv))
	{
		std::cerr << "Usage: " << argv[0] << "[-r] [--case=[case]] PATH..." << std::endl
			<< "Convert PATH names [recursivly] to case" << std::endl;
		exit(EXIT_FAILURE);
	}			
	std::vector<path> path_arg;
	for(int i=optind; i < argc; i++)
	{		
		path_arg.push_back(argv[i]);
		path_arg[i-optind] = tocase(path_arg[i-optind], mode, traverse);
	}

	exit(EXIT_SUCCESS);
}
