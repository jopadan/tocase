#pragma once
#include <locale>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <string>

namespace std
{
	string tolower(const string& str)
	{
		std::string dst(str);
		for(string::iterator i = dst.begin(); i != dst.end(); i++)
			*i = tolower(*i);

		return dst;	
	}

	namespace filesystem
	{
		const bool recursive = true;

		path& tolower(path& src, bool recursive = false)
		{
			src = canonical(absolute(src));
			if(exists(src))
			{
				path dst = src;
				dst.replace_filename(tolower(src.native()));
				rename(src, dst);
				std::cout << src << " -> " << dst << std::endl;
				src = dst;
				if(is_directory(src) && recursive)
				{
					directory_iterator dir_iter(src);
					while(dir_iter != end(dir_iter))
					{
						const directory_entry& dir_entry = *dir_iter++;
						tolower((path&)dir_entry.path(), true);
					}
				}

			}
			return src;
		}
	}
}
