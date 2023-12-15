/*
* function		: logs library entry
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2023.12.10
* 
* change author	: hammlee
* change date	: 2023.12.10
* change log	: init
*/

#pragma once

#include <iostream>
#include "base.h"
#include "error.h"

#define DEF_CPPLOGS_SPLIT	"#"
#define DEF_CPPLOGS_ITEMS	{ "info", "warn", "error", CppLogsLevel_High, true, true }

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

namespace CppLogs {

	using PrivateString = struct {
		std::string data;
	};

	class CPPLOGS_API CppLogsW
	{
	public:
		enum EnCppLogsLevel {
			CppLogsLevel_High = 1,
			CppLogsLevel_Middle,
			CppLogsLevel_Low
		};
		struct StCppLogsItem{
			std::string keyInfo;
			std::string keyWarn;
			std::string keyError;
			EnCppLogsLevel en_CppLogsLevel;
			bool		stampRecord;
			bool		fileLineRecord;
		};

	public:
		CppLogsW(const std::string& filename) :
			_filename(PrivateString{ filename }) {
			_st_CppLogsItem = DEF_CPPLOGS_ITEMS;
		}
		~CppLogsW();

		/*
		* @brief set keyword and timestamp
		* @param st_CppLogsItem : keyword and whether record timestamp
		* @return error code
		*/
		Error::EnErrorCode set_item_type(const StCppLogsItem& st_CppLogsItem = DEF_CPPLOGS_ITEMS);

		/*
		* @brief create log file at the under the specified path
		* @return error code
		*/
		Error::EnErrorCode create_log_file();
		Error::EnErrorCode information(const std::string& secondaryKey = "", const std::string& data = "");
		Error::EnErrorCode warning(const std::string& secondaryKey = "", const std::string& data = "");
		Error::EnErrorCode error(const std::string& secondaryKey = "", const std::string& data = "");

	private:
		PrivateString	_filename;
		StCppLogsItem	_st_CppLogsItem;

	private:
		std::string _format_item(const std::string& itemKey, const std::string& secondaryKey, const std::string& data);
		StCppLogsItem _analy_item();
	};
}
