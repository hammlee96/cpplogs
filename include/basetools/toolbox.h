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

namespace CppLogs {

	class ToolBox
	{
	public:
		ToolBox() = delete;
		static bool writefile(const std::string& filename, const std::string& data);
		static bool readfile(const std::string& filename, std::string& data);
		static bool existfile(const std::string& filename);
	};
}