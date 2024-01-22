/*
* function		: data format
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.01.08
*
* change author	: hammlee
* change date	: 2024.01.08
* change log	: init
*/

#pragma once

#include "cpplogs/basetools/base.h"
#include "cpplogs/basetools/error.h"
#include "cpplogs/basetools/toolbox.h"
#include <iostream>

/*
<#header#>
create_time:2022-02-03 23:22:25
level:1
info:info
warn:warn
error:error
time_stamp:y
file_line:y
<#/header#>
<#info#secondkeyinfo#T2022-02-03 23:22:25#F/home/root/clim/cpplogs/test.cpp:235#>xxxxxxxxx<#/info#>
<#warn#secondkeywarn#T2022-02-03 23:22:25#F/home/root/clim/cpplogs/test.cpp:240#>xxxxxxxxx<#/error#>
<#error#secondkeyerror#T2022-02-03 23:22:25#F/home/root/clim/cpplogs/test.cpp:256#>xxxxxxxxx<#/error#>
*/

namespace CppLogs
{
	class CPPLOGS_API DataFormat
	{
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
			std::string create_time;
			std::string keyInfo;
			std::string keyWarn;
			std::string keyError;
			EnCppLogsLevel en_CppLogsLevel;
			bool		stampRecord;
		};
		struct StCppLogsItem {
			std::string key;
			std::string secondKey;
			std::string timeStamp;
			std::string data;
		};

	public:
		DataFormat() = delete;

		/*
		* @brief format header data
		* @param create_time : date of log creation
		* @return formatted data
		*/
		static std::string format_header(const DataFormat::StCppLogsHeader& st_CppLogsHeader);

		/*
		* @brief analysis header data
		* @param st_CppLogsHeader : get header info
		* @return the error code
		*/
		static Error::EnErrorCode unformat_header(const std::string& data, DataFormat::StCppLogsHeader& st_CppLogsHeader);

		/*
		* @brief format logs item
		* @param key : the key value of item type
		* @param secondKey : the key value of item type's name
		* @param data : the data of log
		* @return formatted data
		*/
		static std::string format_data(const DataFormat::EnCppLogsItemType& key, const std::string secondKey, const std::string& data, const DataFormat::StCppLogsHeader& st_CppLogsHeader);

		/*
		* @brief analysis log item data
		* @param st_CppLogsItem : get item info
		* @return error code
		*/
		static Error::EnErrorCode unformat_data(const std::string& data, std::vector<DataFormat::StCppLogsItem>& st_CppLogsItemVector, const DataFormat::StCppLogsHeader& st_CppLogsHeader);
	};
}