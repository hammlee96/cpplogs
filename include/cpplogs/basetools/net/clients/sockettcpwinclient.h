/*
* function		: tcp client for windows
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

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace CppLogs
{
	class SocketTcpWinClient : public CppLogs::ClientBase
	{
	public:
		SocketTcpWinClient(const std::string& hostip = "127.0.0.1", const int& hostport = 9605) :
			_hostip(hostip), _hostport(hostport)
		{

		}
		~SocketTcpWinClient()
		{
			disconnect();
		}

		CppLogs::Error::EnCppLogsNetError init() override
		{
			WSADATA wsaData;
			int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (ret) {
				return CppLogs::Error::EnCppLogsNetError_InitFailed;
			}
			return CppLogs::Error::EnCppLogsNetError_None;
		}

		CppLogs::Error::EnCppLogsNetError connect() override
		{
			if (is_connected()) {
				if (disconnect()) {
					return CppLogs::Error::EnCppLogsNetError_DisconnectFailed;
				}
			}

			struct addrinfo st_addrinfo{};
			ZeroMemory(&st_addrinfo, sizeof(st_addrinfo));

			st_addrinfo.ai_family = AF_UNSPEC; // not specified ip type
			st_addrinfo.ai_socktype = SOCK_STREAM; // use tcp
			st_addrinfo.ai_flags = AI_NUMERICSERV; // port passed as numeric value
			st_addrinfo.ai_protocol = 0;

			std::string str_port = std::to_string(_hostport);
			struct addrinfo* st_addrinfo_result;
			int ret = ::getaddrinfo(_hostip.data(), str_port.data(), &st_addrinfo, &st_addrinfo_result);
			if (ret) {
				::WSAGetLastError();
				::WSACleanup();
				return CppLogs::Error::EnCppLogsNetError_GetAddrInfoFailed;
			}
			//CPPLOGS_DEBUG << st_addrinfo.ai_addr;
			for (auto ptr = st_addrinfo_result; ptr != nullptr; ptr = ptr->ai_next) {
				_socket = ::socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
				if (_socket == INVALID_SOCKET) {
					::WSAGetLastError();
					::WSACleanup();
					continue;
				}
				if (::connect(_socket, ptr->ai_addr, (int)ptr->ai_addrlen) == 0) {
					break;
				}
				else {
					::WSAGetLastError();
					disconnect();
					return CppLogs::Error::EnCppLogsNetError_ConnectFailed;
				}
			}
			::freeaddrinfo(st_addrinfo_result);
			if (_socket == INVALID_SOCKET) {
				::WSACleanup();
				return CppLogs::Error::EnCppLogsNetError_SetSocketFailed;
			}
			int enable_flag = 1;
			::setsockopt(_socket, IPPROTO_TCP, TCP_NODELAY, \
				reinterpret_cast<char*>(&enable_flag), sizeof(enable_flag));
			return CppLogs::Error::EnCppLogsNetError_None;
		}

		CppLogs::Error::EnCppLogsNetError disconnect() override
		{
			int ret = ::closesocket(_socket);
			_socket = INVALID_SOCKET;
			return CppLogs::Error::EnCppLogsNetError_None;
		}

		CppLogs::Error::EnCppLogsNetError send(const char* data, const size_t& size) override
		{
			size_t bytes_send = 0;
			while (bytes_send < size) {
				const int send_flag = 0;
				size_t ret_size = ::send(_socket, data + bytes_send, (int)(size - bytes_send), send_flag);
				if (ret_size == SOCKET_ERROR) {
					::WSAGetLastError();
					disconnect();
					return CppLogs::Error::EnCppLogsNetError_SendFailed;
				}
				if (ret_size == 0) {
					break;
				}
				bytes_send += static_cast<size_t>(ret_size);
			}
			return CppLogs::Error::EnCppLogsNetError_None;
		}

		CppLogs::Error::EnCppLogsNetError recv(char* data, size_t& size) override
		{
			const int recv_flag = 0;
			size_t ret = ::recv(_socket, data, CPPLOGS_NET_SIZE, recv_flag);
			if (ret <= 0) {
				return CppLogs::Error::EnCppLogsNetError_RecvFailed;
			}
			size = ret;
			return CppLogs::Error::EnCppLogsNetError_None;
		}

		bool is_connected() const override
		{
			return _socket != INVALID_SOCKET;
		}

	private:
		std::string _hostip;
		int _hostport;
		SOCKET _socket;
	};
}