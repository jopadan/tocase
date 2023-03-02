#pragma once
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <string>
#include <unicode/uchar.h>

namespace std
{
	enum case_mode_e
	{
		none               = UCHAR_INVALID_CODE,
		simple_lowercase   = UCHAR_SIMPLE_LOWERCASE_MAPPING,
		simple_uppercase   = UCHAR_SIMPLE_UPPERCASE_MAPPING,
		simple_titlecase   = UCHAR_SIMPLE_TITLECASE_MAPPING,
		simple_casefolding = UCHAR_SIMPLE_CASE_FOLDING, 
	};

	typedef enum case_mode_e case_mode;

	u32string tolower(const u32string& str)
	{
		u32string out;
		for(u32string::const_iterator i = str.begin(); i != str.end(); i++)
			out += u_tolower(*i);
		return out;
	}

	u32string toupper(const u32string& str)
	{
		u32string out;
		for(u32string::const_iterator i = str.begin(); i != str.end(); i++)
			out += u_toupper(*i);
		return out;
	}

	u32string totitle(const u32string& str)
	{
		u32string out;
		for(u32string::const_iterator i = str.begin(); i != str.end(); i++)
			out += u_totitle(*i);
		return out;
	}

	u32string foldcase(const u32string& str)
	{
		u32string out;
		for(u32string::const_iterator i = str.begin(); i != str.end(); i++)
			out += u_foldCase(*i, U_FOLD_CASE_DEFAULT);
		return out;
	}

	u32string tocase(const u32string& str, case_mode mode = none)
	{
		switch(mode)
		{
			case simple_lowercase:
				return tolower(str);
				break; 
			case simple_uppercase:
				return toupper(str);
				break;
			case simple_titlecase:
				return totitle(str);
				break;
			case simple_casefolding:
				return foldcase(str);
				break;
			default:
				break;
		}
		return str;
	}

	namespace filesystem
	{
		enum traverse_mode_e
		{
			none = 0,
			recursive,
		};

		typedef enum traverse_mode_e traverse_mode;

		path& tocase(path& src, case_mode mode = std::none, traverse_mode traverse = std::filesystem::none)
		{
			src = canonical(absolute(src));
			if(exists(src))
			{
				path dst = src;
				dst.replace_filename(std::tocase(src.u32string(), mode));
				rename(src, dst);
				std::cout << src << " -> " << dst << std::endl;
				src = dst;
				if(is_directory(src) && traverse == recursive)
				{
					directory_iterator dir_iter(src);
					while(dir_iter != end(dir_iter))
					{
						const directory_entry& dir_entry = *dir_iter++;
						tocase((path&)dir_entry.path(), simple_lowercase, traverse);
					}
				}

			}
			return src;
		}
	}
}
