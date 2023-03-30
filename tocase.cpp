#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <getopt.h>
#include <iostream>
#include <vector>
#include "tocase.h"

using namespace std;
using namespace std::filesystem;

/* initialize default options */
static case_mode mode = case_mode::simple_lowercase;
static traverse_mode traverse = traverse_mode::none;

void print_usage(const char* program_file);
void config_args(int argc, char** argv);

int main(int argc, char** argv)
{
	config_args(argc, argv);

	std::vector<path> path_arg;
	for(int i=optind; i < argc; i++)
	{		
		path_arg.push_back(argv[i]);
		path_arg[i-optind] = tocase(path_arg[i-optind], mode, traverse);
	}

	exit(EXIT_SUCCESS);
}

void print_usage(const char* program_file)
{
	std::cerr << "Usage: " << program_file << "[-r] [--case=[case]] PATH..." << std::endl
		<< "Convert PATH names [recursivly] to case" << std::endl;
}

void config_args(int argc, char** argv)
{
	if(argc < 2)
	{
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	int opt;
	int option_index;

	static struct option long_options[] = {
		{ "recursive", no_argument, 0, 'r' },
		{ "case", required_argument, 0, 'c' },
		{ "file", required_argument, 0, 0 },
		{ NULL, 0, NULL, 0 },
	};

	while((opt = getopt_long(argc, argv, "rc:", long_options, &option_index)) != -1)
	{
		switch(opt)
		{
			case 'r':
				traverse = traverse_mode::recursive;
				break;
			case 'c':
				mode = case_mode_from_str[std::string(optarg)];
				break;
			default:
				print_usage(argv[0]);
				exit(EXIT_FAILURE);
				break;
		}
	}
}
