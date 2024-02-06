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
#include <map>
#include <sstream>
#include "cpplogs/basetools/base.h"

#if defined(CPPLOGS_SYSTEM_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <time.h>
#include <unistd.h>
#endif

namespace CppLogs {

	class CPPLOGS_API ToolBox
	{
	public:
		struct StCppLogsDateTime {
			unsigned int uiYear;
			unsigned int uiMonth;
			unsigned int uiDay;
			unsigned int uiHour;
			unsigned int uiMinute;
			unsigned int uiSecond;
		};

	public:
		ToolBox() = delete;
		static bool writefile(const std::string& filename, const std::string& data)
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

		static bool readfile(const std::string& filename, std::string& data)
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

		static bool existfile(const std::string& filename)
		{
			std::ifstream f(filename.c_str());
			return f.good();
		}

		static std::vector<std::string> regexmatch(const std::string& value, const std::string& matchstr)
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

		static std::map<std::string, std::string> regexmatchsplit(const std::string& value, const std::string& matchstr, const std::string& split_key)
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

		static ToolBox::StCppLogsDateTime gettime()
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

		static void msleep(const unsigned int& u_times)
		{
#if defined(CPPLOGS_SYSTEM_WINDOWS)
			::Sleep(u_times);
#else
			::usleep(u_times * 1000);
#endif
		}

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