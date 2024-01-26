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

namespace CppLogs
{
	class CppLogsMessage
	{
	public:
		CppLogsMessage()
		{
			CppJson json;
			std::string jsonData;
			CPPLOGS_DEBUG << json.Add("name", "hammlee");
			CPPLOGS_DEBUG << json.Add("age", 27);
			CPPLOGS_DEBUG << json.Add("height", 170.2);
			CPPLOGS_DEBUG << json.ToString(jsonData);
			CPPLOGS_DEBUG << jsonData;

			std::string value;
			int n_value = 0;
			float d_value = 0.0f;
			CPPLOGS_DEBUG << json.Parse(jsonData);
			CPPLOGS_DEBUG << json.Get("name", value);
			CPPLOGS_DEBUG << value;
			CPPLOGS_DEBUG << json.Get("age", n_value);
			CPPLOGS_DEBUG << n_value;
			CPPLOGS_DEBUG << json.Get("height", d_value);
			CPPLOGS_DEBUG << d_value;
		}
		~CppLogsMessage()
		{

		}
	};
}