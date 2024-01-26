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
			CPPLOGS_JsonReturn(PushValue("commond", "set_fileinfo"));
			CPPLOGS_JsonReturn(PushValue("file_path_name", filepathname));
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