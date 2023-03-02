#pragma once
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <string>
#include <unicode/uchar.h>

namespace std
{
	u32string tolower(const u32string& str)
	{
		u32string out;
		for(u32string::const_iterator i = str.begin(); i != str.end(); i++)
			out += u_tolower(*i);
		return out;
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
				dst.replace_filename(std::tolower(src.u32string()));
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
