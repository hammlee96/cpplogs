/*
* function		: net server base
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.02.05
*
* change author	: hammlee
* change date	: 2024.02.05
* change log	: init
*/

#pragma once

#include <iostream>
#include <string>
#include "cpplogs/basetools/error.h"

#define CPPLOGS_NET_SIZE	512

namespace CppLogs
{
	class ServerBase
	{
	public:
		struct StCppLogsNetAddrInfo
		{
			std::string str_ip;
			unsigned short port;
			unsigned int fd;
		};

	public:
		ServerBase(const int& port = 9605)
		{

		}
		virtual ~ServerBase()
		{

		}

		virtual Error::EnCppLogsNetError init() = 0;
		virtual Error::EnCppLogsNetError accept() = 0;
		virtual Error::EnCppLogsNetError \
			send(const std::string& destip, const int& destport, const char* data, const size_t& size) = 0;
		virtual Error::EnCppLogsNetError recv(char* data, size_t& size) = 0;
		virtual Error::EnCppLogsNetError close() = 0;

		virtual int connect_num() = 0;
		virtual std::vector<StCppLogsNetAddrInfo> connect_info() = 0;
	};
}