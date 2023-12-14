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
#define DEF_CPPLOGS_ITEMS	{ "[info]", "[warn]", "[error]", true }

namespace CppLogs {

	using PrivateString = struct {
		std::string data;
	};

	class CPPLOGS_API CppLogs
	{
	public:
		struct StCppLogsItem{
			std::string keyInfo;
			std::string keyWarn;
			std::string keyError;
			bool		stampRecord;
		};

	public:
		CppLogs(const std::string& filename) :
			_filename(PrivateString{ filename }) {
			_st_CppLogsItem = DEF_CPPLOGS_ITEMS;
		}
		~CppLogs();

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
