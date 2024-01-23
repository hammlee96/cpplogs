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
#include <iostream>
#include <string_view>
#include <string>
#include "cpplogs/basetools/error.h"

#define CPPLOGS_NET_SIZE	512

namespace CppLogs
{
	class SocketTcpBase
	{
	public:
		enum EnCppLogsSocketTcpType {
			CppLogsSocketTcpType_Client,
			CppLogsSocketTcpType_Server
		};

	public:
		SocketTcpBase(const std::string& hostip = "127.0.0.1", const int& hostport = 9605)
		{

		}
		virtual ~SocketTcpBase()
		{

		}
		
		virtual Error::EnCppLogsNetError init() = 0;
		virtual Error::EnCppLogsNetError connect()
		{
			return Error::EnCppLogsNetError_ConnectFailed;
		}

		virtual Error::EnCppLogsNetError disconnect()
		{
			return Error::EnCppLogsNetError_DisconnectFailed;
		}

		virtual Error::EnCppLogsNetError listen()
		{
			return Error::EnCppLogsNetError_CreateListenFailed;
		}

		virtual Error::EnCppLogsNetError send(const char* data, const size_t& size) = 0;
		virtual Error::EnCppLogsNetError recv(char* data, size_t& size) = 0;

		virtual bool is_connected() const = 0;
	};
}