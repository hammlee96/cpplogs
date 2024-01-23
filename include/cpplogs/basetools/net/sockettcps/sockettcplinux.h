/*
* function		: tcp base for linux
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.01.22
*
* change author	: hammlee
* change date	: 2024.01.22
* change log	: init
*/


#pragma once

#include "sockettcpbase.h"
#include <sys/socket.h>

namespace CppLogs
{
	class SocketTcpLinuxClient : public SocketTcpBase
	{
	public:
		SocketTcpLinuxClient(const std::string& hostip = "127.0.0.1", const int& hostport = 9605);
		~SocketTcpLinuxClient();

		Error::EnCppLogsNetError init() override
		{
			return Error::EnCppLogsNetError();
		}

		Error::EnCppLogsNetError connect() override
		{
			return Error::EnCppLogsNetError();
		}

		Error::EnCppLogsNetError disconnect() override
		{
			return Error::EnCppLogsNetError();
		}

		Error::EnCppLogsNetError send(const char* data, const size_t& size) override
		{
			return Error::EnCppLogsNetError();
		}

		Error::EnCppLogsNetError recv(char* data, size_t& size) override
		{
			return Error::EnCppLogsNetError();
		}
	};

	class SocketTcpLinuxServer : public SocketTcpBase
	{
	public:
		SocketTcpLinuxServer(const std::string& hostip = "127.0.0.1", const int& hostport = 9605);
		~SocketTcpLinuxServer();

		Error::EnCppLogsNetError init() override
		{
			return Error::EnCppLogsNetError();
		}

		Error::EnCppLogsNetError connect() override
		{
			return Error::EnCppLogsNetError();
		}

		Error::EnCppLogsNetError disconnect() override
		{
			return Error::EnCppLogsNetError();
		}

		Error::EnCppLogsNetError listen() override
		{
			return Error::EnCppLogsNetError();
		}
	};
}