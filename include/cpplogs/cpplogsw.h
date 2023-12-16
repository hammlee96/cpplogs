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

namespace CppLogs {

	using PrivateString = struct {
		std::string data;
	};

	class CPPLOGS_API CppLogsW
	{
	public:
		CppLogsW(const std::string& filename)
		{
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
			return _fileFormat->set_log_header(st_CppLogsItem);
		}

		/*
		* @brief create log file at the under the specified path
		* @return error code
		*/
		Error::EnErrorCode create_log_file()
		{
			return _fileFormat->create_log_file();
		}

		/*
		* @brief write info data into log file
		* @param secondaryKey	: secondary key, you may use this parameter to count the number of occurrences of a single log
		* @param data			: the explain of this item 
		* @return error code
		*/
		Error::EnErrorCode information(const std::string& secondaryKey = "", const std::string& data = "")
		{
			return _fileFormat->writefile(_fileFormat->analysis_header().keyInfo, secondaryKey, data);
		}

		/*
		* @brief write info data into warn file
		* @param secondaryKey	: secondary key, you may use this parameter to count the number of occurrences of a single log
		* @param data			: the explain of this item
		* @return error code
		*/
		Error::EnErrorCode warning(const std::string& secondaryKey = "", const std::string& data = "")
		{
			return _fileFormat->writefile(_fileFormat->analysis_header().keyWarn, secondaryKey, data);
		}

		/*
		* @brief write info data into error file
		* @param secondaryKey	: secondary key, you may use this parameter to count the number of occurrences of a single log
		* @param data			: the explain of this item
		* @return error code
		*/
		Error::EnErrorCode error(const std::string& secondaryKey = "", const std::string& data = "")
		{
			return _fileFormat->writefile(_fileFormat->analysis_header().keyError, secondaryKey, data);
		}

	private:
		FileFormat *_fileFormat;
	};
}
