#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <ctype.h>
#include <libgen.h>

bool strtolower(char* dst, const char* src, size_t n)
{
	size_t size = n ? n : strlen(src);

	for(int i = (src[0] == '.' && src[1] == '/') ? 2 : 0; i < size; i++)
	{
		if( i == 0 && size == 1 )
		{
			if(src[i] == '.' || src[i] == '/')
			{
				return false;
			}
		}

		if( i == 0 && size == 2)
		{
			if(src[i] == '.' && src[i + 1] == '.')
			{
				return false;
			}
		}

		if(i < size - 1 && size == 3)
			if(src[i] == '.' && src[i + 1] == '.')
				return false;

		dst[i] = tolower(src[i]);
	}
	return true;
}

bool renameable(const char* src)
{
	int res = 0;
	int punct = 0;
	size_t size = strlen(src);

	for(int i=0; i< size; i++)
	{
		if( i == 0 && size == 1 )
		{
			if(src[i] == '.' || src[i] == '/')
			{
				return false;
			}
		}

		if(i < size - 1)
			if(src[i] == '.' && src[i+1] == '.')
				return false;
	}

	return true;
}

bool dirtolower(char* dst, const char* path)
{
	struct stat sb;
	struct dirent **namelist;

	char* cwd = getcwd(NULL,0);
	if(lstat(path, &sb) == -1)
	{
		perror("Retrieving file information using stat!");
		return false;
	}

	if(!strtolower(dst, path, strlen(path)))
	{
		perror("ERROR: strtolower(): converting path string to lower case");
		return false;
	}

	if(strcmp(dst, path) == 0 && (lstat(dst, &sb) == 0))
	{
		fprintf(stderr, "Source and destination strings are equal and already exist!\n");
		return false;
	}
	 
	if(rename(path, dst) != 0)
	{
		perror("renaming path to lower case");
		return false;
	}
	
	int n = scandir(dst, &namelist, NULL, alphasort);
	if( n == -1) {
		perror("scandir");
		return false;
	}

	chdir(dst);
	while( n-- ) {
		char * name = strdup(namelist[n]->d_name);

		if(!renameable(name))
		{
			free(name);
			free(namelist[n]);
			continue;
		}

		if(!strtolower(name, namelist[n]->d_name, strlen(namelist[n]->d_name)))
		{
			perror("strtolower");
			free(name);
			free(namelist[n]);
			free(namelist);
			chdir(cwd);
			free(cwd);
			return false;
		}
		if(namelist[n]->d_type == DT_DIR)
		{
			if(!dirtolower(name,namelist[n]->d_name))
			{
				perror("recurse directory");				
				free(name);
				free(namelist[n]);
				free(namelist);
				chdir(cwd);
				free(cwd);
				return false;
			}
		}
		else if(rename(namelist[n]->d_name, name) != 0)
		{
			perror("rename directory");
			return false;
		}
		free(name);
		free(namelist[n]);
	}
	chdir(cwd);

	free(cwd);
	free(namelist);
	return true;
}
int main(int argc, char** argv)
{
	struct stat sb;

	if(argc > 1)
	{
		char* lower = strdup(argv[1]);
		if(!dirtolower(lower,argv[1]))
		{
			fprintf(stderr,"conversion of %s -> %s not successful!\n", argv[1], lower);
			free(lower);
			exit(EXIT_FAILURE);
		}
		fprintf(stdout,"%s -> %s\n", argv[1], lower);
	}
	else
	{
		fprintf(stderr,"Usage: tolower PATH...\nConvert PATH directory name recursively to lowercase\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
