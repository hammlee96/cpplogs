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
		CppLogsMessage()
		{
		}
		~CppLogsMessage()
		{

		}

		bool CommandSetFileInfo(const std::string& filepathname, std::string& json_value)
		{
			Clear();
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_COMMOND, CPPLOGS_STR_SET_FILEINFO));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_FILEPATHNAME, filepathname));
			CPPLOGS_JsonReturn(GetString(json_value));
			return true;
		}

		bool CommandSetLogType(const DataFormat::StCppLogsHeader& st_CppLogsHeader, std::string& json_value)
		{
			Clear();
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_COMMOND, CPPLOGS_STR_SET_LOGTYPE));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_DEF_HEADER_CREATE_TIME, st_CppLogsHeader.create_time));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_DEF_HEADER_LEVEL, st_CppLogsHeader.en_CppLogsLevel));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_DEF_HEADER_INFO, st_CppLogsHeader.keyInfo));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_DEF_HEADER_WARN, st_CppLogsHeader.keyWarn));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_DEF_HEADER_ERROR, st_CppLogsHeader.keyError));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_DEF_HEADER_TIME_STAMP, st_CppLogsHeader.stampRecord));
			CPPLOGS_JsonReturn(GetString(json_value));
			return true;
		}

		bool CommandSetLogData(const DataFormat::StCppLogsItem& st_CppLogsItem, std::string& json_value)
		{
			Clear();
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_COMMOND, CPPLOGS_STR_SET_LOGDATA));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_KEY, st_CppLogsItem.key));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_SECOND_KEY, st_CppLogsItem.secondKey));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_TIME_STAMP, st_CppLogsItem.timeStamp));
			CPPLOGS_JsonReturn(PushValue(CPPLOGS_STR_DATA, st_CppLogsItem.data));
			CPPLOGS_JsonReturn(GetString(json_value));
			return true;
		}

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