/*
* function		: tcp client for linux
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.01.22
*
* change author	: hammlee
* change date	: 2024.01.22
* change log	: init
*/


#pragma once

#include "clientbase.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

namespace CppLogs
{
	class SocketTcpLinuxClient : public CppLogs::ClientBase
	{
	public:
		SocketTcpLinuxClient(const std::string& hostip = "127.0.0.1", const int& hostport = 9605) : 
			_hostip(hostip), _hostport(hostport)
		{
			_socket = -1;
		}
		~SocketTcpLinuxClient()
		{

		}

		CppLogs::Error::EnCppLogsNetError init() override
		{
			return CppLogs::Error::EnCppLogsNetError_None;
		}

		CppLogs::Error::EnCppLogsNetError connect() override
		{
			if (is_connected()) {
				disconnect();
			}
			_socket = ::socket(AF_INET, SOCK_STREAM, 0);
			if (_socket == -1) {
				return CppLogs::Error::EnCppLogsNetError_InitFailed;
			}
			struct ::sockaddr_in st_sockaddr_in;
			memset(&st_sockaddr_in, 0, sizeof(st_sockaddr_in));
			st_sockaddr_in.sin_family = AF_INET;
			//st_sockaddr_in.sin_addr.s_addr = inet_addr(_hostip.c_str());
			st_sockaddr_in.sin_port = ::htons(_hostport);
			if (::inet_pton(AF_INET, _hostip.c_str(), &st_sockaddr_in.sin_addr) <= 0) {
				disconnect();
				return CppLogs::Error::EnCppLogsNetError_SetSocketFailed;
			}
			if (::connect(_socket, (struct sockaddr*)&st_sockaddr_in, sizeof(st_sockaddr_in)) == -1) {
				disconnect();
				return CppLogs::Error::EnCppLogsNetError_ConnectFailed;
			}

			return CppLogs::Error::EnCppLogsNetError_None;
		}

		CppLogs::Error::EnCppLogsNetError disconnect() override
		{
			::close(_socket);
			_socket = -1;
			return CppLogs::Error::EnCppLogsNetError_None;
		}

		CppLogs::Error::EnCppLogsNetError send(const char* data, const size_t& size) override
		{
			if (::send(_socket, data, size, 0) != size) {
				disconnect();
				return CppLogs::Error::EnCppLogsNetError_SendFailed;
			}
			return CppLogs::Error::EnCppLogsNetError_None;
		}

		CppLogs::Error::EnCppLogsNetError recv(char* data, size_t& size) override
		{
			int ret = ::recv(_socket, data, CPPLOGS_NET_SIZE, 0);
			if (ret < 0) {
				disconnect();
				return CppLogs::Error::EnCppLogsNetError_RecvFailed;
			}
			size = ret;
			return CppLogs::Error::EnCppLogsNetError_None;
		}

		bool is_connected() const override
		{
			return _socket != -1;
		}

	private:
		std::string _hostip;
		int _hostport;
		int _socket;
	};
}