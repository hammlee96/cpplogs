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
			_pSocketTcpBase = std::make_shared<SocketTcpWinClient>(hostip, hostport);
#else
			_pSocketTcpBase = std::make_shared<SocketTcpLinuxClient>(hostip, hostport);
#endif
		}

		~SocketTcp()
		{
		}

		Error::EnCppLogsNetError init()
		{
			return _pSocketTcpBase.get()->init();
		}

		Error::EnCppLogsNetError connect()
		{
			Error::EnCppLogsNetError ret = _pSocketTcpBase.get()->connect();
			ToolBox::msleep(100);
			return ret;
		}

		Error::EnCppLogsNetError send(const std::string& data)
		{
			return _pSocketTcpBase.get()->send(data.c_str(), data.size());;
		}

		Error::EnCppLogsNetError disconnect()
		{
			return _pSocketTcpBase.get()->disconnect();
		}

	private:
		CPPLOGS_DISABLE4251(std::shared_ptr<SocketTcpBase> _pSocketTcpBase);
	};
}