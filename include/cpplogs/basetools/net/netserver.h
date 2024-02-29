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
#include "servers/sockettcplinuxserver.h"
#include "cpplogs/basetools/toolbox.h"

namespace CppLogs
{
	class NetServer
	{
	public:
		NetServer(const int& port = 9605)
		{
			_pServerBase = std::make_shared<CppLogs::SocketTcpLinuxServer>(port);
		}

		~NetServer()
		{

		}

		CppLogs::Error::EnCppLogsNetError init()
		{
			return _pServerBase->init();
		}

		CppLogs::Error::EnCppLogsNetError accept(CppLogs::ServerBase::StNetDataInfo** st_NetDataInfo)
		{
			return _pServerBase->accept(st_NetDataInfo);
		}

		CppLogs::Error::EnCppLogsNetError recv(char* data, int& size)
		{
			return _pServerBase->recv(data, size);
		}

		CppLogs::Error::EnCppLogsNetError send(const std::string& destip, const int& destport, const char* data, const size_t& size)
		{
			return _pServerBase->send(destip, destport, data, size);
		}

		CppLogs::Error::EnCppLogsNetError \
			send(const std::string& name, const char* data, const size_t& size)
		{
			return _pServerBase->send(name, data, size);
		}

		CppLogs::Error::EnCppLogsNetError send(const int& client_fd, const char* data, const size_t& size)
		{
			return _pServerBase->send(client_fd, data, size);
		}

		CppLogs::Error::EnCppLogsNetError close()
		{
			return CppLogs::Error::EnCppLogsNetError_None;
		}

		void free_struct(CppLogs::ServerBase::StNetDataInfo* st_NetDataInfo)
		{
			_pServerBase->free_struct(st_NetDataInfo);
		}

		bool set_name(const std::string& destip, const int& destport, const std::string& name)
		{
			return _pServerBase->set_name(destip, destport, name);
		}

		int get_connect_num()
		{
			return _pServerBase->connect_num();
		}

		std::vector<CppLogs::ServerBase::StCppLogsNetAddrInfo> get_connect_info()
		{
			return _pServerBase->connect_info();
		}

	private:
		CPPLOGS_DISABLE4251(std::shared_ptr<CppLogs::ServerBase> _pServerBase);
	};
}