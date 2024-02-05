/*
* function		: server summery
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.02.05
*
* change author	: hammlee
* change date	: 2024.02.05
* change log	: init
*/

#pragma once
#include "cpplogs/basetools/base.h"
#include "servers/serverbase.h"
#if defined(CPPLOGS_SYSTEM_WINDOWS)
#include "servers/sockettcpwinserver.h"
#else
#include "servers/sockettcplinuxserver.h"
#endif
#include "cpplogs/basetools/toolbox.h"

namespace CppLogs
{
	class NetServer
	{
	public:
		NetServer(const int& port = 9605)
		{
#if defined(CPPLOGS_SYSTEM_WINDOWS)
			_pServerBase = std::make_shared<SocketTcpWinServer>(port);
#else
			_pServerBase = std::make_shared<SocketTcpLinuxServer>(port);
#endif
		}

		~NetServer()
		{

		}

	private:
		CPPLOGS_DISABLE4251(std::shared_ptr<ServerBase> _pServerBase);
	};
}