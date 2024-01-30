/*
* function		: tcp base for linux
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.01.22
*
* change author	: hammlee
* change date	: 2024.01.22
* change log	: init
*/


#pragma once

#include "sockettcpbase.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace CppLogs
{
	class SocketTcpLinuxClient : public SocketTcpBase
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

		Error::EnCppLogsNetError init() override
		{
			return Error::EnCppLogsNetError_None;
		}

		Error::EnCppLogsNetError connect() override
		{
			int _socket = ::socket(AF_INET, SOCK_STREAM, 0);
			if (_socket == -1) {
				return Error::EnCppLogsNetError_InitFailed;
			}
			struct ::sockaddr_in st_sockaddr_in;
			st_sockaddr_in.sin_family = AF_INET;
			st_sockaddr_in.sin_addr.s_addr = inet_addr(_hostip.c_str());
			st_sockaddr_in.sin_port = _hostport;
			if (::connect(_socket, (struct sockaddr*)&st_sockaddr_in, sizeof(st_sockaddr_in)) == -1) {
				return Error::EnCppLogsNetError_ConnectFailed;
			}

			return Error::EnCppLogsNetError_None;
		}

		Error::EnCppLogsNetError disconnect() override
		{
			::close(_socket);
			_socket = -1;
			return Error::EnCppLogsNetError_None;
		}

		Error::EnCppLogsNetError send(const char* data, const size_t& size) override
		{
			if (::send(_socket, data, size, 0) != size) {
				return Error::EnCppLogsNetError_SendFailed;
			}
			return Error::EnCppLogsNetError_None;
		}

		Error::EnCppLogsNetError recv(char* data, size_t& size) override
		{
			if (::recv(_socket, data, size, 0) < 0) {
				return Error::EnCppLogsNetError_RecvFailed;
			}
			return Error::EnCppLogsNetError_None;
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

	class SocketTcpLinuxServer : public SocketTcpBase
	{
	public:
		SocketTcpLinuxServer(const std::string& hostip = "127.0.0.1", const int& hostport = 9605);
		~SocketTcpLinuxServer();

		Error::EnCppLogsNetError init() override
		{
			return Error::EnCppLogsNetError();
		}

		Error::EnCppLogsNetError connect() override
		{
			return Error::EnCppLogsNetError();
		}

		Error::EnCppLogsNetError disconnect() override
		{
			return Error::EnCppLogsNetError();
		}

		Error::EnCppLogsNetError listen() override
		{
			return Error::EnCppLogsNetError();
		}
	};
}