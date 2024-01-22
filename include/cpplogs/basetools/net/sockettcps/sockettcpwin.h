/*
* function		: tcp base for windows
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

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

namespace CppLogs
{
	class SocketTcpWin : public SocketTcpBase
	{
	public:
		SocketTcpWin(const char* hostip = "127.0.0.1", const int hostport = 9605);
		~SocketTcpWin();


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