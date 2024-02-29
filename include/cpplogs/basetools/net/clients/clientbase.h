/*
* function		: net client base
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.01.22
*
* change author	: hammlee
* change date	: 2024.01.22
* change log	: init
*/


#pragma once
#include <iostream>
#include <string>
#include "cpplogs/basetools/error.h"

#define CPPLOGS_NET_SIZE	2048

namespace CppLogs
{
	class ClientBase
	{
	public:
		ClientBase(const std::string& hostip = "127.0.0.1", const int& hostport = 9605)
		{

		}
		virtual ~ClientBase()
		{

		}
		
		virtual CppLogs::Error::EnCppLogsNetError init() = 0;
		virtual CppLogs::Error::EnCppLogsNetError connect() = 0;
		virtual CppLogs::Error::EnCppLogsNetError disconnect() = 0;

		virtual CppLogs::Error::EnCppLogsNetError send(const char* data, const size_t& size) = 0;
		virtual CppLogs::Error::EnCppLogsNetError recv(char* data, size_t& size) = 0;

		virtual bool is_connected() const = 0;
	};
}