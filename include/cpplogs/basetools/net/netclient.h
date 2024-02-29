/*
* function		: client summery
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
#include "clients/clientbase.h"
#if defined(CPPLOGS_SYSTEM_WINDOWS)
#include "clients/sockettcpwinclient.h"
#else
#include "clients/sockettcplinuxclient.h"
#endif
#include "cpplogs/basetools/toolbox.h"

namespace CppLogs
{
	class NetClient
	{
	public:
		NetClient(const std::string& hostip = "127.0.0.1", const int& hostport = 9605)
		{
#if defined(CPPLOGS_SYSTEM_WINDOWS)
			_pClientBase = std::make_shared<CppLogs::SocketTcpWinClient>(hostip, hostport);
#else
			_pClientBase = std::make_shared<SocketTcpLinuxClient>(hostip, hostport);
#endif
		}

		~NetClient()
		{
		}

		CppLogs::Error::EnCppLogsNetError init()
		{
			return _pClientBase.get()->init();
		}

		CppLogs::Error::EnCppLogsNetError connect()
		{
			CppLogs::Error::EnCppLogsNetError ret = _pClientBase.get()->connect();
			CppLogs::ToolBox::msleep(100);
			return ret;
		}

		CppLogs::Error::EnCppLogsNetError send(const std::string& data)
		{
			return _pClientBase.get()->send(data.c_str(), data.size());;
		}

		CppLogs::Error::EnCppLogsNetError recv(char* data, size_t& size)
		{
			return _pClientBase.get()->recv(data, size);;
		}

		CppLogs::Error::EnCppLogsNetError disconnect()
		{
			return _pClientBase.get()->disconnect();
		}

	private:
		CPPLOGS_DISABLE4251(std::shared_ptr<CppLogs::ClientBase> _pClientBase);
	};
}