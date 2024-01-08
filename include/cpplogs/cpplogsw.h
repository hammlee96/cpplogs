/*
* function		: write logs file
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

namespace CppLogs {

	class CPPLOGS_API CppLogsW : public FileFormat
	{
	public:
		CppLogsW(const std::string& filename) : FileFormat(filename)
		{}
		~CppLogsW() {}

		/*
		* @brief set keyword and timestamp
		* @param st_CppLogsItem : keyword and whether record timestamp
		* @return error code
		*/
		Error::EnErrorCode set_item_type(const DataFormat::StCppLogsHeader& st_CppLogsItem = DEF_CPPLOGS_ITEMS)
		{
			return set_log_header(st_CppLogsItem);
		}

		/*
		* @brief create log file at the under the specified path
		* @return error code
		*/
		Error::EnErrorCode create_file(const std::string& create_time)
		{
			return create_log_file(create_time);
		}

		/*
		* @brief write info data into log file
		* @param secondaryKey	: secondary key, you may use this parameter to count the number of occurrences of a single log
		* @param data			: the explain of this item 
		* @return error code
		*/
		Error::EnErrorCode information(const std::string& secondaryKey = "", const std::string& data = "")
		{
			if (get_header().en_CppLogsLevel >= DataFormat::CppLogsLevel_Middle) {
				return Error::ErrorCode_LevelNotMatch;
			}
			return writefile(DataFormat::CppLogsItemType_Info, secondaryKey, data);
		}

		/*
		* @brief write info data into warn file
		* @param secondaryKey	: secondary key, you may use this parameter to count the number of occurrences of a single log
		* @param data			: the explain of this item
		* @return error code
		*/
		Error::EnErrorCode warn(const std::string& secondaryKey = "", const std::string& data = "")
		{
			if (get_header().en_CppLogsLevel > DataFormat::CppLogsLevel_Middle) {
				return Error::ErrorCode_LevelNotMatch;
			}
			return writefile(DataFormat::CppLogsItemType_Warn, secondaryKey, data);
		}

		/*
		* @brief write info data into error file
		* @param secondaryKey	: secondary key, you may use this parameter to count the number of occurrences of a single log
		* @param data			: the explain of this item
		* @return error code
		*/
		Error::EnErrorCode error(const std::string& secondaryKey = "", const std::string& data = "")
		{
			return writefile(DataFormat::CppLogsItemType_Error, secondaryKey, data);
		}
	};
}
