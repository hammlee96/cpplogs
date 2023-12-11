#pragma once

#include <iostream>
#include <fstream>

namespace CppLogs {

	class ToolBox
	{
	public:
		ToolBox() = delete;
		static bool writefile(const std::string& filename, const std::string& data);
		static bool readfile(const std::string& filename, std::string& data);
	};
}