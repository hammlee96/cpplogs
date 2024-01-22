/*
* function		: tcp base
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.01.22
*
* change author	: hammlee
* change date	: 2024.01.22
* change log	: init
*/

#pragma once

#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

namespace CppLogs
{
	class SocketTcp
	{
	public:
		SocketTcp(const char* hostip, const int hostport);
		~SocketTcp();
	};
}