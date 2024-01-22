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
	class SocketTcpLinux : public SocketTcpBase
	{
	public:
		SocketTcpLinux(const char* hostip = "127.0.0.1", const int hostport = 9605);
		~SocketTcpLinux();

		bool init() override
		{
			return true;
		}

		bool connect() override
		{
			return true;
		}

		bool disconnect() override
		{
			return true;
		}

		bool send(const char* data, const unsigned int size) override
		{
			return true;
		}

		bool recv(char* data, unsigned int* size) override
		{
			return true;
		}
	};
}