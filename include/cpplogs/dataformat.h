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

#include "cpplogs/basetools/toolbox.h"
#include "cpplogs/basetools/error.h"
#include <iostream>


#define DEF_CPPLOGS_ITEMS	{"",  "info", "warn", "error", DataFormat::CppLogsLevel_High, true }

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
<#info#secondkeyinfo#T2022-02-03 23:22:25#>xxxxxxxxx<#/info#>
<#warn#secondkeywarn#T2022-02-03 23:22:25#>xxxxxxxxx<#/error#>
<#error#secondkeyerror#T2022-02-03 23:22:25#>xxxxxxxxx<#/error#>
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
		static std::string format_header(const CppLogs::DataFormat::StCppLogsHeader& st_CppLogsHeader)
		{
			return CppLogs::ToolBox::format("<#%s#>\n%s:%s\n%s:%d\n%s:%s\n%s:%s\n%s:%s\n%s:%s\n<#/%s#>", \
				CPPLOGS_DEF_HEADER, \
				CPPLOGS_DEF_HEADER_CREATE_TIME, st_CppLogsHeader.create_time.c_str(), \
				CPPLOGS_DEF_HEADER_LEVEL, (int)st_CppLogsHeader.en_CppLogsLevel, \
				CPPLOGS_DEF_HEADER_INFO, st_CppLogsHeader.keyInfo.c_str(), \
				CPPLOGS_DEF_HEADER_WARN, st_CppLogsHeader.keyWarn.c_str(), \
				CPPLOGS_DEF_HEADER_ERROR, st_CppLogsHeader.keyError.c_str(), \
				CPPLOGS_DEF_HEADER_TIME_STAMP, st_CppLogsHeader.stampRecord ? CPPLOGS_DEF_CPPLOGS_TRUE : CPPLOGS_DEF_CPPLOGS_FALSE, \
				CPPLOGS_DEF_HEADER);
		}

		/*
		* @brief analysis header data
		* @param st_CppLogsHeader : get header info
		* @return the error code
		*/
		static CppLogs::Error::EnErrorCode unformat_header(const std::string& data, CppLogs::DataFormat::StCppLogsHeader& st_CppLogsHeader)
		{
			std::string pattern = CppLogs::ToolBox::format("<#%s#>([\\s\\S]*?)<#/%s#>", CPPLOGS_DEF_HEADER, CPPLOGS_DEF_HEADER);
			std::vector<std::string> result = CppLogs::ToolBox::regexmatch(data, pattern);

			if (result.size() != 1) {
				return CppLogs::Error::ErrorCode_HeaderDamage;
			}

			std::map<std::string, std::string> mm = CppLogs::ToolBox::regexmatchsplit(result.at(0), pattern, ":");
			if (mm.size() != 6) {
				return CppLogs::Error::ErrorCode_HeaderDamage;
			}
			for (auto it : mm) {
				if (it.first == CPPLOGS_DEF_HEADER_CREATE_TIME) {
					st_CppLogsHeader.create_time = it.second;
				}
				else if (it.first == CPPLOGS_DEF_HEADER_LEVEL) {
					st_CppLogsHeader.en_CppLogsLevel = (CppLogs::DataFormat::EnCppLogsLevel)std::stoi(it.second);
				}
				else if (it.first == CPPLOGS_DEF_HEADER_INFO) {
					st_CppLogsHeader.keyInfo = it.second;
				}
				else if (it.first == CPPLOGS_DEF_HEADER_WARN) {
					st_CppLogsHeader.keyWarn = it.second;
				}
				else if (it.first == CPPLOGS_DEF_HEADER_ERROR) {
					st_CppLogsHeader.keyError = it.second;
				}
				else if (it.first == CPPLOGS_DEF_HEADER_TIME_STAMP) {
					st_CppLogsHeader.stampRecord = it.second == CPPLOGS_DEF_CPPLOGS_TRUE ? true : false;
				}
			}

			return CppLogs::Error::ErrorCode_None;
		}

		/*
		* @brief format logs item
		* @param key : the key value of item type
		* @param secondKey : the key value of item type's name
		* @param data : the data of log
		* @return formatted data
		*/
		static std::string format_data(const CppLogs::DataFormat::EnCppLogsItemType& key, const std::string secondKey, \
			const std::string& data, const CppLogs::DataFormat::StCppLogsHeader& st_CppLogsHeader)
		{
			std::string keystr = "";
			switch (key) {
			case CppLogs::DataFormat::CppLogsItemType_Info: {
				keystr = st_CppLogsHeader.keyInfo;
			}break;
			case CppLogs::DataFormat::CppLogsItemType_Warn: {
				keystr = st_CppLogsHeader.keyWarn;
			}break;
			case CppLogs::DataFormat::CppLogsItemType_Error: {
				keystr = st_CppLogsHeader.keyError;
			}break;
			}
			std::string formatdata = CppLogs::ToolBox::format("<#%s#%s", \
				keystr.c_str(), secondKey.c_str());
			if (st_CppLogsHeader.stampRecord) {
				CppLogs::ToolBox::StCppLogsDateTime st_CppLogsDateTime = CppLogs::ToolBox::gettime();
				formatdata = CppLogs::ToolBox::format("%s#T%d-%d-%d %d:%d:%d", \
					formatdata.c_str(), \
					st_CppLogsDateTime.uiYear, st_CppLogsDateTime.uiMonth, st_CppLogsDateTime.uiDay, \
					st_CppLogsDateTime.uiHour, st_CppLogsDateTime.uiMinute, st_CppLogsDateTime.uiSecond);
			}

			return CppLogs::ToolBox::format("%s#>%s<#/%s#>", \
				formatdata.c_str(), data.c_str(), keystr.c_str());
		}

		/*
		* @brief analysis log item data
		* @param st_CppLogsItem : get item info
		* @return error code
		*/
		static CppLogs::Error::EnErrorCode unformat_data(const std::string& data, std::vector<CppLogs::DataFormat::StCppLogsItem>& st_CppLogsItemVector, \
			const CppLogs::DataFormat::StCppLogsHeader& st_CppLogsHeader)
		{
			std::string pattern;
			if (st_CppLogsHeader.stampRecord) {
				pattern = "<#(.*)?#(.*)?#T(.*)?#>([\\s\\S]*?)<#/(.*)?#>";
			}
			else {
				pattern = "<#(.*)?#(.*)?#>([\\s\\S]*?)<#/(.*)?#>";
			}
			std::regex matchStr(pattern);
			std::smatch matched;
			std::istringstream iss(data);
			std::string line;
			bool isFind = false;
			while (getline(iss, line)) {
				if (std::regex_match(line, matched, matchStr)) {
					if (st_CppLogsHeader.stampRecord && matched.size() == 6) {
						st_CppLogsItemVector.push_back({ matched.str(1), matched.str(2), matched.str(3), \
							matched.str(4) });
						isFind = true;
					}
					else if (!st_CppLogsHeader.stampRecord && matched.size() == 5) {
						st_CppLogsItemVector.push_back({ matched.str(1), matched.str(2), matched.str(3), \
							matched.str(4) });
						isFind = true;
					}
				}
			}
			return (isFind ? CppLogs::Error::ErrorCode_None : CppLogs::Error::ErrorCode_FindItemFailed);
		}
	};
}