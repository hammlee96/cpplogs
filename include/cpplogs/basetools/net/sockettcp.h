/*
* function		: tcp summery
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.01.22
*
* change author	: hammlee
* change date	: 2024.01.22
* change log	: init
*/

#pragma once
#include "cpplogs/basetools/base.h"
#include "sockettcps/sockettcpbase.h"
#if defined(CPPLOGS_SYSTEM_WINDOWS)
#include "sockettcps/sockettcpwin.h"
#else
#include "sockettcps/sockettcplinux.h"
#endif

namespace CppLogs
{
	class SocketTcp
	{
	public:
		SocketTcp(const char* hostip, const int hostport);
		~SocketTcp();
	};
}