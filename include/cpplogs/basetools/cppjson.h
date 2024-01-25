/*
* function		: Encapsulating cJSON functions
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.01.25
*
* change author	: hammlee
* change date	: 2024.01.25
* change log	: init
*/

#pragma once

namespace CppLogs
{
	class CppJson
	{
	public:
		CppJson();
		~CppJson();

		void Clear();

		bool Add(const std::string& key, const std::string& value);
		bool Add(const std::string& key, const int& value);
		bool Add(const std::string& key, const float& value);

	private:
		cJSON* _pmonitor;

	private:
		cJSON* _get_valid_object();
	};
}