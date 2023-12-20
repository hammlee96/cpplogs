/*
* function		: some universal features
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2023.12.16
*
* change author	: hammlee
* change date	: 2023.12.16
* change log	: init
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

namespace CppLogs {

	class ToolBox
	{
	public:
		ToolBox() = delete;
		static bool writefile(const std::string& filename, const std::string& data);
		static bool readfile(const std::string& filename, std::string& data);
		static bool existfile(const std::string& filename);
		static std::vector<std::string> regexmatch(const std::string& value, const std::string& matchstr);

		template<typename ... Args>
		static std::string format(const std::string& format, Args ... args)
		{
			auto size_buf = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
			std::unique_ptr<char[]> buf(new(std::nothrow) char[size_buf]);

			if (!buf)
				return std::string("");

			std::snprintf(buf.get(), size_buf, format.c_str(), args ...);
			return std::string(buf.get(), buf.get() + size_buf - 1);
		}
	};
}