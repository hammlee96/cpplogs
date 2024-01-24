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
#include "cpplogs/basetools/toolbox.h"
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
		enum EnCppLogsSocketType
		{
			CppLogsSocketType_Client,
			CppLogsSocketType_Server
		};

	public:
		SocketTcp(const EnCppLogsSocketType type, const std::string& hostip = "127.0.0.1", const int& hostport = 9605)
		{
			if(type == CppLogsSocketType_Client){
#if defined(CPPLOGS_SYSTEM_WINDOWS)
				_pSocketTcpBase = new SocketTcpWinClient(hostip, hostport);
#else
				_pSocketTcpBase = new SocketTcpLinuxClient(hostip, hostport);
#endif
				Error::EnCppLogsNetError ret = _pSocketTcpBase->init();
				if (ret) {
					CPPLOGS_ERROR << ret;
				}
				ret = _pSocketTcpBase->connect();
				if (ret) {
					CPPLOGS_ERROR << ret;
				}
				ToolBox::msleep(100);
				ret = _pSocketTcpBase->send("aaa", 3);
				if (ret) {
					CPPLOGS_ERROR << ret;
				}
			}
			else {
				_pSocketTcpBase = new SocketTcpWinServer(hostip, hostport);

				Error::EnCppLogsNetError ret = _pSocketTcpBase->init();
				if (ret) {
					CPPLOGS_ERROR << ret;
				}

				ret = _pSocketTcpBase->listen();
				if (ret) {
					CPPLOGS_ERROR << ret;
				}

				char data[512] = { 0 };
				size_t data_len = 512;
				ret = _pSocketTcpBase->recv(data, data_len);
				if (ret) {
					CPPLOGS_ERROR << ret;
				}
			}
		}

		~SocketTcp()
		{

		}

	private:
		SocketTcpBase* _pSocketTcpBase;
	};
}