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