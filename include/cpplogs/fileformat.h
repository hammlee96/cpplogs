#include <iostream>
#include <fstream>
#include "error.h"

/*
<#header>
create_time:2022-02-03 23:22:25
level:1
info:info
warn:warn
error:error
time_stamp:y
file_line:y
<#headerEnd>
<#info#secondkeyinfo><#T2022-02-03 23:22:25><#F/home/root/clim/cpplogs/test.cpp:235>xxxxxxxxx<#infoEnd>
<#warn#secondkeywarn><#T2022-02-03 23:22:25><#F/home/root/clim/cpplogs/test.cpp:240>xxxxxxxxx<#errorEnd>
<#error#secondkeyerror><#T2022-02-03 23:22:25><#F/home/root/clim/cpplogs/test.cpp:256>xxxxxxxxx<#errorEnd>
*/

#define DEF_CPPLOGS_ITEMS	{ "info", "warn", "error", FileFormat::CppLogsLevel_High, true, true }

namespace CppLogs {
	class FileFormat{
	public:
		enum EnCppLogsLevel {
			CppLogsLevel_High = 1,
			CppLogsLevel_Middle,
			CppLogsLevel_Low
		};
		struct StCppLogsHeader {
			std::string keyInfo;
			std::string keyWarn;
			std::string keyError;
			EnCppLogsLevel en_CppLogsLevel;
			bool		stampRecord;
			bool		fileLineRecord;
		};
		struct StCppLogsItem {
			std::string key;
			std::string secondKey;
			std::string timeStamp;
			std::string fileLine;
			std::string data;
		};

	public:
		FileFormat(const std::string& filename) :
			_filename(filename) 
		{
			_st_CppLogsIHeader = DEF_CPPLOGS_ITEMS;
		}
		~FileFormat();

		bool existfile();
		FileFormat::StCppLogsHeader analysis_header();

		Error::EnErrorCode set_log_header(const StCppLogsHeader& st_CppLogsHeader = DEF_CPPLOGS_ITEMS);
		Error::EnErrorCode create_log_file();
		Error::EnErrorCode writefile(const std::string& key, const std::string secondKey, const std::string& data);

		std::string format_header();
		StCppLogsItem unformat_header();
		std::string format_data(const std::string& data);
		FileFormat::StCppLogsItem unformat_data(const std::string& data);

	private:
		std::string _filename;
		FileFormat::StCppLogsHeader	_st_CppLogsIHeader;
	};
}