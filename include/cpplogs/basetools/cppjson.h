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

#include <string>
struct cJSON;

namespace CppLogs
{
	static void* (*CppLogs_malloc)(size_t) = malloc;
	static void (*CppLogs_free)(void* ptr) = free;

	class CppJson
	{
	public:
		CppJson();
		~CppJson();

		void Clear();
		bool Parse(const std::string& json);
		bool ToString(std::string& jsonData);

		bool Get(const std::string& key, std::string& value);
		bool Get(const std::string& key, int& value);
		bool Get(const std::string& key, double& value);
		bool Get(const std::string& key, float& value);

		bool Add(const std::string& key, const std::string& value);
		bool Add(const std::string& key, const int& value);
		bool Add(const std::string& key, const double& value);
		bool Add(const std::string& key, const float& value);

	private:
		cJSON* _pmonitor;

	private:
		cJSON* _get_valid_object();
	};
}