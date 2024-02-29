/*
* function		: file and data format
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2023.12.16
*
* change author	: hammlee
* change date	: 2023.12.16
* change log	: init
*/

#pragma once
#include "cpplogs/basetools/toolbox.h"
#include "cpplogs/basetools/error.h"
#include "cpplogs/dataformat.h"

namespace CppLogs {
	class CPPLOGS_API FileFormat
	{
	public:
		FileFormat(const std::string& filename) :
			_filename(filename + CPPLOGS_EXTNAME)
		{
			_st_CppLogsIHeader = DEF_CPPLOGS_ITEMS;
			if (existfile()) {
				unformat_file_header(_st_CppLogsIHeader);
			}
		}
		~FileFormat()
		{

		}

		/*
		* @brief check if the file exists
		* @return the file status
		*/
		bool existfile()
		{
			return CppLogs::ToolBox::existfile(_filename);
		}

		/*
		* @brief get using header
		* @return current header param
		*/
		CppLogs::DataFormat::StCppLogsHeader get_header()
		{
			return _st_CppLogsIHeader;
		}

		/*
		* @brief set logs header, if not set use this function, the header value will use default param
		* @param st_CppLogsHeader : the header value you want
		* @return error code
		*/
		CppLogs::Error::EnErrorCode set_log_header(const CppLogs::DataFormat::StCppLogsHeader& st_CppLogsHeader = DEF_CPPLOGS_ITEMS)
		{
			if (existfile()) {
				CppLogs::Error::EnErrorCode ec = unformat_file_header(_st_CppLogsIHeader);
				if (!ec) {
					return CppLogs::Error::ErrorCode_LogFileExist;
				}
				return ec;
			}
			if (st_CppLogsHeader.keyInfo.empty() || \
				st_CppLogsHeader.keyWarn.empty() || \
				st_CppLogsHeader.keyError.empty()) {
				return CppLogs::Error::ErrorCode_CreateItemFailed;
			}
			_st_CppLogsIHeader = st_CppLogsHeader;
			return CppLogs::Error::ErrorCode_None;
		}

		/*
		* @brief create log file, and write header
		* @param create_time : date of log creation
		* @return error code
		*/
		CppLogs::Error::EnErrorCode create_log_file(const std::string& create_time)
		{
			if (!existfile()) {
				return CppLogs::ToolBox::writefile(_filename, format_file_header(create_time)) ? CppLogs::Error::ErrorCode_None : CppLogs::Error::ErrorCode_OpenFileFailed;
			}
			return CppLogs::Error::ErrorCode_LogFileExist;
		}

		/*
		* @brief write log data
		* @param key		: this data type
		* @param secondKey	: this data ID
		* @param data		: the data you want record
		* @return error code
		*/
		CppLogs::Error::EnErrorCode writefile(const CppLogs::DataFormat::EnCppLogsItemType& key, const std::string secondKey, const std::string& data)
		{
			if (existfile()) {
				return CppLogs::ToolBox::writefile(_filename, format_file_data(key, secondKey, data)) ? CppLogs::Error::ErrorCode_None : CppLogs::Error::ErrorCode_OpenFileFailed;
			}
			return CppLogs::Error::ErrorCode_OpenFileFailed;
		}

		/*
		* @brief format header data
		* @param create_time : date of log creation
		* @return formatted data
		*/
		std::string format_file_header(const std::string& create_time)
		{
			_st_CppLogsIHeader.create_time = create_time;
			return CppLogs::DataFormat::format_header(_st_CppLogsIHeader);
		}

		/*
		* @brief analysis header data
		* @param st_CppLogsHeader : get header info
		* @return the error code
		*/
		CppLogs::Error::EnErrorCode unformat_file_header(CppLogs::DataFormat::StCppLogsHeader& st_CppLogsHeader)
		{
			std::string data;
			CppLogs::ToolBox::readfile(_filename, data);
			return CppLogs::DataFormat::unformat_header(data, st_CppLogsHeader);
		}

		/*
		* @brief format logs item
		* @param key : the key value of item type
		* @param secondKey : the key value of item type's name
		* @param data : the data of log
		* @return formatted data
		*/
		std::string format_file_data(const CppLogs::DataFormat::EnCppLogsItemType& key, const std::string secondKey, const std::string& data)
		{
			return CppLogs::DataFormat::format_data(key, secondKey, data, _st_CppLogsIHeader);
		}
		
		/*
		* @brief analysis log item data
		* @param st_CppLogsItem : get item info
		* @return error code
		*/
		CppLogs::Error::EnErrorCode unformat_file_data(std::vector<CppLogs::DataFormat::StCppLogsItem>& st_CppLogsItemVector)
		{
			std::string data;
			CppLogs::ToolBox::readfile(_filename, data);
			return CppLogs::DataFormat::unformat_data(data, st_CppLogsItemVector, _st_CppLogsIHeader);
		}

	private:
		CPPLOGS_DISABLE4251(std::string _filename);
		CppLogs::DataFormat::StCppLogsHeader	_st_CppLogsIHeader;
	};
}