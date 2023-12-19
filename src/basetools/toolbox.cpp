#include "toolbox.h"

namespace CppLogs {

	bool ToolBox::writefile(const std::string& filename, const std::string& data)
	{
		std::ofstream f;
		f.open(filename, std::ios::app);
		if (!f.is_open()) {
			return false;
		}
		f << data << std::endl;
		f.close();
		return true;
	}

	bool ToolBox::readfile(const std::string& filename, std::string& data)
	{
		std::ifstream f;
		f.open(filename);
		if (!f.is_open()) {
			return false;
		}
		std::string str;
		while (getline(f, str)) {
			data.append(str + "\n");
		}
		f.close();
		return true;
	}

	bool ToolBox::existfile(const std::string& filename)
	{
		std::ifstream f(filename.c_str());
		return f.good();
	}
}
