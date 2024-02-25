/*
* function		: format network message
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.01.26
*
* change author	: hammlee
* change date	: 2024.01.26
* change log	: init
*/

#pragma once
#include <iostream>
#include "basetools/base.h"
#include "basetools/cppjson.h"
#include "cpplogs/dataformat.h"

#define CPPLOGS_JsonReturn(func) if(!func){return false;}

namespace CppLogs
{
	class CppLogsMessage : public CppJson
	{
	public:
		CppLogsMessage() : 
			_st_CppLogsHeader(DEF_CPPLOGS_ITEMS)
		{
		}
		~CppLogsMessage()
		{

		}

		bool CommandSetAccountName(std::string& json_value, const std::string& name)
		{
			Clear();
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_COMMOND, CPPLOGS_STR_SET_ACCOUNT_NAME));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_ACCOUNT_NAME, name));
			CPPLOGS_JsonReturn(GetString(json_value));
			return true;
		}

		bool CommandSetLogData(std::string& json_value, const std::string& filepathname, \
			const DataFormat::StCppLogsHeader& st_CppLogsHeader, const DataFormat::EnCppLogsItemType key, \
			const std::string secondKey, const std::string& data)
		{
			Clear();
			//CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_COMMOND, CPPLOGS_STR_SET_FILEINFO));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_FILEPATHNAME, filepathname));
			//CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_COMMOND, CPPLOGS_STR_SET_LOGTYPE));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_DEF_HEADER_CREATE_TIME, st_CppLogsHeader.create_time));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_DEF_HEADER_LEVEL, st_CppLogsHeader.en_CppLogsLevel));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_DEF_HEADER_INFO, st_CppLogsHeader.keyInfo));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_DEF_HEADER_WARN, st_CppLogsHeader.keyWarn));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_DEF_HEADER_ERROR, st_CppLogsHeader.keyError));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_DEF_HEADER_TIME_STAMP, st_CppLogsHeader.stampRecord));
			//std::string str_formatdata = DataFormat::format_data(key, secondKey, data, _st_CppLogsHeader);
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_COMMOND, CPPLOGS_STR_SET_LOGDATA));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_ENUM_KEY, key));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_SECOND_KEY, secondKey));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_DATA, data));
			CPPLOGS_JsonReturn(GetString(json_value));
			return true;
		}

	private:
		DataFormat::StCppLogsHeader _st_CppLogsHeader;

	private:
		bool ParseJson(const std::string& json)
		{
			return Parse(json);
		}

		bool GetString(std::string& value)
		{
			return ToString(value);
		}

		template<typename _ty_value>
		bool GetValue(const std::string& key, _ty_value& value)
		{
			return Get(key, value);
		}

		template<typename _ty_value>
		bool PushValue(const std::string& key, const _ty_value& value)
		{
			return Add(key, value);
		}
	};
}