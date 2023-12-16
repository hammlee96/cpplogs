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
#include "fileformat.h"

#define DEF_CPPLOGS_SPLIT	"#"
#define DEF_CPPLOGS_ITEMS	{ "info", "warn", "error", FileFormat::CppLogsLevel_High, true, true }

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
		CppLogsW(const std::string& filename) :
			_filename(PrivateString{ filename }) {
			_st_CppLogsItem = DEF_CPPLOGS_ITEMS;
			_fileFormat = new FileFormat(filename);
		}
		~CppLogsW() {
			delete _fileFormat;
			_fileFormat = nullptr;
		}

		/*
		* @brief set keyword and timestamp
		* @param st_CppLogsItem : keyword and whether record timestamp
		* @return error code
		*/
		Error::EnErrorCode set_item_type(const FileFormat::StCppLogsHeader& st_CppLogsItem = DEF_CPPLOGS_ITEMS)
		{
			Error::EnErrorCode ec = _fileFormat->set_log_header(st_CppLogsItem);
			if (!ec) {
				_st_CppLogsItem = st_CppLogsItem;
			}
			return ec;
		}

		/*
		* @brief create log file at the under the specified path
		* @return error code
		*/
		Error::EnErrorCode create_log_file()
		{
			return _fileFormat->create_log_file(_st_CppLogsItem);
		}

		/*
		* @brief write info data into log file
		* @param secondaryKey	: secondary key, you may use this parameter to count the number of occurrences of a single log
		* @param data			: the explain of this item 
		* @return error code
		*/
		Error::EnErrorCode information(const std::string& secondaryKey = "", const std::string& data = "")
		{
			return _fileFormat->writefile(_st_CppLogsItem.keyInfo, secondaryKey, data);
		}

		/*
		* @brief write info data into warn file
		* @param secondaryKey	: secondary key, you may use this parameter to count the number of occurrences of a single log
		* @param data			: the explain of this item
		* @return error code
		*/
		Error::EnErrorCode warning(const std::string& secondaryKey = "", const std::string& data = "")
		{
			return _fileFormat->writefile(_st_CppLogsItem.keyWarn, secondaryKey, data);
		}

		/*
		* @brief write info data into error file
		* @param secondaryKey	: secondary key, you may use this parameter to count the number of occurrences of a single log
		* @param data			: the explain of this item
		* @return error code
		*/
		Error::EnErrorCode error(const std::string& secondaryKey = "", const std::string& data = "")
		{
			return _fileFormat->writefile(_st_CppLogsItem.keyError, secondaryKey, data);
		}

	private:
		PrivateString	_filename;
		FileFormat::StCppLogsHeader	_st_CppLogsItem;
		FileFormat *_fileFormat;

	//private:
	//	std::string _format_item(const std::string& itemKey, const std::string& secondaryKey, const std::string& data);
	//	FileFormat::StCppLogsHeader _analy_item();
	};
}
