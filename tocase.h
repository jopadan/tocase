#pragma once
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
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
	std::map<std::string, case_mode> case_mode_from_str =
	{
		{ "none"    ,  none },
		{ "lower"   , simple_lowercase },
		{ "upper"   , simple_uppercase },
		{ "title"   , simple_titlecase },
		{ "fold"    , simple_casefolding },
	};

	u32string tocase(const u32string& str, case_mode mode = none)
	{
		u32string out;
		for(u32string::const_iterator i = str.begin(); i != str.end(); i++)
		{
			switch(mode)
			{
				case simple_lowercase:
					out += u_tolower(*i);
					break; 
				case simple_uppercase:
					out += u_toupper(*i);
					break;
				case simple_titlecase:
					out += u_totitle(*i);
					break;
				case simple_casefolding:
					out += u_foldCase(*i, U_FOLD_CASE_DEFAULT);
					break;
				default:
					out += *i;
					break;
			}
		}
		return out;
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
				dst.replace_filename(std::tocase(src.filename().u32string(), mode));
				rename(src, dst);
				std::cout << src << " -> " << dst << std::endl;
				src = dst;
				if(is_directory(src) && traverse == recursive)
				{
					directory_iterator dir_iter(src);
					while(dir_iter != end(dir_iter))
					{
						const directory_entry& dir_entry = *dir_iter++;
						tocase((path&)dir_entry.path(), mode, traverse);
					}
				}

			}
			return src;
		}
	}
}
