/*
* function		: tcp server for linux
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.02.05
*
* change author	: hammlee
* change date	: 2024.02.05
* change log	: init
*/

#pragma once

#include "serverbase.h"
#include <vector>

namespace CppLogs
{
	class SocketTcpLinuxServer : public ServerBase
	{
	public:
		SocketTcpLinuxServer(const int& port = 9605)
		{
			_st_CppLogsNetAddrInfo.clear();
		}
		~SocketTcpLinuxServer()
		{

		}

		Error::EnCppLogsNetError init()
		{
			return Error::EnCppLogsNetError();
		}
		Error::EnCppLogsNetError accept()
		{
			return Error::EnCppLogsNetError();
		}
		Error::EnCppLogsNetError \
			send(const std::string& destip, const int& destport, const char* data, const size_t& size)
		{
			return Error::EnCppLogsNetError();
		}
		Error::EnCppLogsNetError recv(char* data, int& size)
		{
			return Error::EnCppLogsNetError();
		}
		Error::EnCppLogsNetError close()
		{
			return Error::EnCppLogsNetError();
		}

		int connect_num()
		{
			return 0;
		}
		std::vector<StCppLogsNetAddrInfo> connect_info()
		{
			return _st_CppLogsNetAddrInfo;
		}

	private:
		std::vector<StCppLogsNetAddrInfo> _st_CppLogsNetAddrInfo;
	};
}