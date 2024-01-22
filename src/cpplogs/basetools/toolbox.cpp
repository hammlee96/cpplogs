#include "cpplogs/basetools/toolbox.h"
#if defined(CPPLOGS_SYSTEM_WINDOWS)
#include <windows.h>
#else
#include<time.h>
#endif

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

	std::vector<std::string> ToolBox::regexmatch(const std::string& value, const std::string& matchstr)
	{
		std::regex reg(matchstr);
		std::vector<std::string> result;
		result.clear();
		std::sregex_iterator pos(value.begin(), value.end(), reg);
		std::sregex_iterator end;
		for (; pos != end; pos++) {
			result.push_back(pos->str(1));
		}
		return result;
	}

	std::map<std::string, std::string> ToolBox::regexmatchsplit(const std::string& value, const std::string& matchstr, const std::string& split_key)
	{
		std::istringstream iss(value);
		std::string line;
		std::string strsplit = ToolBox::format(R"(\s*([^\s*%s]+)%s(.+))", split_key.c_str(), split_key.c_str());
		std::regex pattern(strsplit);
		std::map<std::string, std::string> result;
		result.clear();
		while (getline(iss, line)) {
			std::smatch match;
			if (std::regex_match(line, match, pattern)) {
				if (match.size() == 3) {
					result[match.str(1)] = match.str(2);
				}
			}
			line.clear();
		}
		return result;
	}

	ToolBox::StCppLogsDateTime ToolBox::gettime()
	{
		ToolBox::StCppLogsDateTime st_CppLogsDateTime;
#if defined(CPPLOGS_SYSTEM_WINDOWS)
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		st_CppLogsDateTime.uiYear = sysTime.wYear;
		st_CppLogsDateTime.uiMonth = sysTime.wMonth;
		st_CppLogsDateTime.uiDay = sysTime.wDay;
		st_CppLogsDateTime.uiHour = sysTime.wHour;
		st_CppLogsDateTime.uiMinute = sysTime.wMinute;
		st_CppLogsDateTime.uiSecond = sysTime.wSecond;
#else
		time_t timer = time(NULL);
		struct tm* st_tm = localtime(&timer);
		st_CppLogsDateTime.uiYear = 1900 + st_tm->tm_year;
		st_CppLogsDateTime.uiMonth = st_tm->tm_mon;
		st_CppLogsDateTime.uiDay = st_tm->tm_yday;
		st_CppLogsDateTime.uiHour = st_tm->tm_hour;
		st_CppLogsDateTime.uiMinute = st_tm->tm_min;
		st_CppLogsDateTime.uiSecond = st_tm->tm_sec;
#endif
		return st_CppLogsDateTime;
	}
}
