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
#include <iostream>
#include <fstream>
#include <any>
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
		enum EnCppLogsItemType {
			CppLogsItemType_Info,
			CppLogsItemType_Warn,
			CppLogsItemType_Error
		};
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

		/*
		* @brief check if the file exists
		* @return the file status
		*/
		bool existfile();

		/*
		* @brief get current file log header define, if have no, return keyword is null, other param return default value.
		* @return current header param
		*/
		std::any analysis_header();

		/*
		* @brief get using header
		* @return current header param
		*/
		FileFormat::StCppLogsHeader get_header();

		/*
		* @brief set logs header, if not set use this function, the header value will use default param
		* @param st_CppLogsHeader : the header value you want
		* @return error code
		*/
		Error::EnErrorCode set_log_header(const StCppLogsHeader& st_CppLogsHeader = DEF_CPPLOGS_ITEMS);

		/*
		* @brief create log file, and write header
		* @param create_time : date of log creation
		* @return error code
		*/
		Error::EnErrorCode create_log_file(const std::string& create_time);

		/*
		* @brief write log data
		* @param key		: this data type
		* @param secondKey	: this data ID
		* @param data		: the data you want record
		* @return error code
		*/
		Error::EnErrorCode writefile(const FileFormat::EnCppLogsItemType& key, const std::string secondKey, const std::string& data);

		/*
		* @brief format header data
		* @param create_time : date of log creation
		* @return formatted data
		*/
		std::string format_header(const std::string& create_time);

		/*
		* @brief analysis header data
		* @return the header structure
		*/
		StCppLogsHeader unformat_header();

		std::string format_data(const FileFormat::EnCppLogsItemType& key, const std::string secondKey, const std::string& data);
		FileFormat::StCppLogsItem unformat_data();

	private:
		std::string _filename;
		FileFormat::StCppLogsHeader	_st_CppLogsIHeader;
	};
}