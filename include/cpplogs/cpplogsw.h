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
#include "cpplogs/basetools/base.h"
#include "cpplogs/basetools/error.h"
#include "cpplogs/fileformat.h"

namespace CppLogs {

	class CPPLOGS_API CppLogsW : public CppLogs::FileFormat
	{
	public:
		CppLogsW(const std::string& filename) : CppLogs::FileFormat(filename)
		{}
		~CppLogsW() {}

		/*
		* @brief set keyword and timestamp
		* @param st_CppLogsItem : keyword and whether record timestamp
		* @return error code
		*/
		CppLogs::Error::EnErrorCode set_item_type(const CppLogs::DataFormat::StCppLogsHeader& st_CppLogsItem = DEF_CPPLOGS_ITEMS)
		{
			return set_log_header(st_CppLogsItem);
		}

		/*
		* @brief create log file at the under the specified path
		* @return error code
		*/
		CppLogs::Error::EnErrorCode create_file(const std::string& create_time)
		{
			return create_log_file(create_time);
		}

		/*
		* @brief write info data into log file
		* @param secondaryKey	: secondary key, you may use this parameter to count the number of occurrences of a single log
		* @param data			: the explain of this item 
		* @return error code
		*/
		template<typename... T_InLengthData>
		CppLogs::Error::EnErrorCode information(const std::string& secondaryKey, const std::string& format, T_InLengthData... data)
		{
			if (get_header().en_CppLogsLevel >= CppLogs::DataFormat::CppLogsLevel_Middle) {
				return CppLogs::Error::ErrorCode_LevelNotMatch;
			}
			return writefile(CppLogs::DataFormat::CppLogsItemType_Info, secondaryKey, ToolBox::format(format, data...));
		}

		/*
		* @brief write info data into warn file
		* @param secondaryKey	: secondary key, you may use this parameter to count the number of occurrences of a single log
		* @param data			: the explain of this item
		* @return error code
		*/
		template<typename... T_InLengthData>
		CppLogs::Error::EnErrorCode warn(const std::string& secondaryKey, const std::string& format, T_InLengthData... data)
		{
			if (get_header().en_CppLogsLevel > CppLogs::DataFormat::CppLogsLevel_Middle) {
				return CppLogs::Error::ErrorCode_LevelNotMatch;
			}
			return writefile(CppLogs::DataFormat::CppLogsItemType_Warn, secondaryKey, ToolBox::format(format, data...));
		}

		/*
		* @brief write info data into error file
		* @param secondaryKey	: secondary key, you may use this parameter to count the number of occurrences of a single log
		* @param data			: the explain of this item
		* @return error code
		*/
		template<typename... T_InLengthData>
		CppLogs::Error::EnErrorCode error(const std::string& secondaryKey, const std::string& format, T_InLengthData... data)
		{
			return writefile(CppLogs::DataFormat::CppLogsItemType_Error, secondaryKey, ToolBox::format(format, data...));
		}
	};
}
