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
#include "cpplogs/basetools/toolbox.h"

namespace CppLogs
{
	class SocketTcp
	{
	public:
		SocketTcp(const std::string& hostip = "127.0.0.1", const int& hostport = 9605)
		{
#if defined(CPPLOGS_SYSTEM_WINDOWS)
			_pSocketTcpBase = new SocketTcpWinClient(hostip, hostport);
#else
			_pSocketTcpBase = new SocketTcpLinuxClient(hostip, hostport);
#endif
		}

		~SocketTcp()
		{
			if (_pSocketTcpBase) {
				delete _pSocketTcpBase;
				_pSocketTcpBase = nullptr;
			}
		}

		Error::EnCppLogsNetError init()
		{
			return _pSocketTcpBase->init();
		}

		Error::EnCppLogsNetError connect()
		{
			Error::EnCppLogsNetError ret = _pSocketTcpBase->connect();
			ToolBox::msleep(100);
			return ret;
		}

		Error::EnCppLogsNetError send(const std::string& data)
		{
			return _pSocketTcpBase->send(data.c_str(), data.size());;
		}

	private:
		SocketTcpBase* _pSocketTcpBase;
	};
}