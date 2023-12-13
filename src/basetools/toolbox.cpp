#include "toolbox.h"
#include <fstream>

namespace CppLogs {

	bool ToolBox::writefile(const std::string& filename, const std::string& data)
	{
		return false;
	}

	bool ToolBox::readfile(const std::string& filename, std::string& data)
	{
		return false;
	}

	bool existfile(const std::string& filename)
	{
		std::ifstream f(filename.c_str());
		return f.good();
	}
}
