/*
* function		: tcp base for windows
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

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#pragma warning(disable:4996)

namespace CppLogs
{
	class SocketTcpWinClient : public SocketTcpBase
	{
	public:
		SocketTcpWinClient(const std::string& hostip = "127.0.0.1", const int& hostport = 9605) :
			_hostip(hostip), _hostport(hostport)
		{

		}
		~SocketTcpWinClient()
		{

		}

		Error::EnCppLogsNetError init() override
		{
			WSADATA wsaData;
			int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (ret) {
				return Error::EnCppLogsNetError_InitFailed;
			}
			return Error::EnCppLogsNetError_None;
		}

		Error::EnCppLogsNetError connect() override
		{
			if (is_connected()) {
				if (disconnect()) {
					return Error::EnCppLogsNetError_DisconnectFailed;
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
				WSACleanup();
				return Error::EnCppLogsNetError_GetAddrInfoFailed;
			}
			//CPPLOGS_DEBUG << st_addrinfo.ai_addr;
			for (auto ptr = st_addrinfo_result; ptr != nullptr; ptr = ptr->ai_next) {
				_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
				if (_socket == INVALID_SOCKET) {
					::WSAGetLastError();
					WSACleanup();
					continue;
				}
				if (::connect(_socket, ptr->ai_addr, (int)ptr->ai_addrlen) == 0) {
					break;
				}
				else {
					::WSAGetLastError();
					disconnect();
					return Error::EnCppLogsNetError_ConnectFailed;
				}
			}
			::freeaddrinfo(st_addrinfo_result);
			if (_socket == INVALID_SOCKET) {
				WSACleanup();
				return Error::EnCppLogsNetError_SetSocketFailed;
			}
			int enable_flag = 1;
			::setsockopt(_socket, IPPROTO_TCP, TCP_NODELAY, \
				reinterpret_cast<char*>(&enable_flag), sizeof(enable_flag));
			return Error::EnCppLogsNetError_None;
		}

		Error::EnCppLogsNetError disconnect() override
		{
			int ret = ::closesocket(_socket);
			_socket = INVALID_SOCKET;
			return Error::EnCppLogsNetError_None;
		}

		Error::EnCppLogsNetError send(const char* data, const size_t& size) override
		{
			size_t bytes_send = 0;
			while (bytes_send < size) {
				const int send_flag = 0;
				size_t ret_size = ::send(_socket, data + bytes_send, (int)(size - bytes_send), send_flag);
				if (ret_size == SOCKET_ERROR) {
					::WSAGetLastError();
					disconnect();
					return Error::EnCppLogsNetError_SendFailed;
				}
				if (ret_size == 0) {
					break;
				}
				bytes_send += static_cast<size_t>(ret_size);
			}
			return Error::EnCppLogsNetError_None;
		}

		Error::EnCppLogsNetError recv(char* data, size_t& size) override
		{
			const int recv_flag = 0;
			size_t ret = ::recv(_socket, data, CPPLOGS_NET_SIZE, recv_flag);
			if (ret <= 0) {
				return Error::EnCppLogsNetError_RecvFailed;
			}
			size = ret;
			return Error::EnCppLogsNetError_None;
		}

		bool is_connected() const override
		{
			return _socket != INVALID_SOCKET;
		}

	private:
		std::string_view _hostip;
		int _hostport;
		SOCKET _socket;
	};

	class SocketTcpWinServer : public SocketTcpBase
	{
	public:
		SocketTcpWinServer(const std::string_view& hostip = "127.0.0.1", const int& hostport = 9605) :
			_hostip(hostip), _hostport(hostport)
		{

		}
		~SocketTcpWinServer()
		{

		}

		Error::EnCppLogsNetError init() override
		{
			WSADATA wsaData;
			int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (ret) {
				return Error::EnCppLogsNetError();
			}


			struct ::addrinfo st_addrinfo;
			struct ::addrinfo* st_addrinfo_result;

			::ZeroMemory(&st_addrinfo, sizeof(st_addrinfo));
			st_addrinfo.ai_family = AF_INET;
			st_addrinfo.ai_socktype = SOCK_STREAM;
			st_addrinfo.ai_protocol = IPPROTO_TCP;
			st_addrinfo.ai_flags = AI_PASSIVE;

			std::string str_port = std::to_string(_hostport);
			ret = ::getaddrinfo(NULL, str_port.data(), &st_addrinfo, &st_addrinfo_result);
			if (ret) {
				::WSAGetLastError();
				::WSACleanup();
				return Error::EnCppLogsNetError_GetAddrInfoFailed;
			}

			_listen_socket = ::socket(st_addrinfo_result->ai_family, st_addrinfo_result->ai_socktype, st_addrinfo_result->ai_protocol);
			if (_listen_socket == INVALID_SOCKET) {
				::WSAGetLastError();
				::freeaddrinfo(st_addrinfo_result);
				::WSACleanup();
				return Error::EnCppLogsNetError_SetSocketFailed;
			}

			ret = ::bind(_listen_socket, st_addrinfo_result->ai_addr, (int)st_addrinfo_result->ai_addrlen);
			if (ret == SOCKET_ERROR) {
				::WSAGetLastError();
				::freeaddrinfo(st_addrinfo_result);
				::closesocket(_listen_socket);
				::WSACleanup();
				return Error::EnCppLogsNetError_BindFailed;
			}

			::freeaddrinfo(st_addrinfo_result);

			ret = ::listen(_listen_socket, SOMAXCONN);
			if (ret == SOCKET_ERROR) {
				::closesocket(_listen_socket);
				return Error::EnCppLogsNetError_ListenFailed;
			}

			return Error::EnCppLogsNetError_None;
		}

		Error::EnCppLogsNetError listen() override
		{
			int ret = 0;
			sockaddr_in st_client_sockaddr_in;
			int len_client_sockaddr_in = sizeof(st_client_sockaddr_in);

			SOCKET client_socket = ::accept(_listen_socket, reinterpret_cast<SOCKADDR*>(&st_client_sockaddr_in), &len_client_sockaddr_in);
			//CPPLOGS_DEBUG << "client ip: " << ::inet_ntoa(st_client_sockaddr_in.sin_addr);
			//::inet_ntoa: st_client_sockaddr_in.sin_addr to char*
			//::inet_addr: char* to st_client_sockaddr_in.sin_addr
			if (client_socket == INVALID_SOCKET) {
				::closesocket(_listen_socket);
				::WSACleanup();
				return Error::EnCppLogsNetError_AcceptFailed;
			}
			st_CppLogsNetAddrInfo_Vector.push_back({::inet_ntoa(st_client_sockaddr_in.sin_addr), st_client_sockaddr_in.sin_port, (unsigned int)client_socket });

			return Error::EnCppLogsNetError_None;
		}

		// disconnect all
		Error::EnCppLogsNetError disconnect() override
		{
			if (!st_CppLogsNetAddrInfo_Vector.size()) {
				return Error::EnCppLogsNetError_ClientSizeNull;
			}
			int ret = 0;
			for (unsigned int i = 0; i < st_CppLogsNetAddrInfo_Vector.size(); i++) {
				::shutdown(st_CppLogsNetAddrInfo_Vector.at(i).fd, SD_SEND);
				::closesocket(st_CppLogsNetAddrInfo_Vector.at(i).fd);
			}
			::WSACleanup();
			::closesocket(_listen_socket);
			_listen_socket = INVALID_SOCKET;
			st_CppLogsNetAddrInfo_Vector.clear();
			::WSACleanup();
			return Error::EnCppLogsNetError_None;
		}

		// disconnect designated IP
		Error::EnCppLogsNetError disconnect(const StCppLogsNetAddrInfo& st_CppLogsNetAddrInfo) override
		{
			::shutdown(st_CppLogsNetAddrInfo.fd, SD_SEND);
			::closesocket(st_CppLogsNetAddrInfo.fd);
			::WSACleanup();
			return Error::EnCppLogsNetError_None;
		}

		Error::EnCppLogsNetError send(const char* data, const size_t& size) override
		{
			return Error::EnCppLogsNetError();
		}

		Error::EnCppLogsNetError recv(char* data, size_t& size) override
		{
			int ret = 0;
			for (auto it : st_CppLogsNetAddrInfo_Vector) {
				::ZeroMemory(data, size);
				ret = ::recv(it.fd, data, size, 0);
				CPPLOGS_DEBUG << "[" << it.str_ip<<":"<<it.port<<"]" << data;
			}
			return Error::EnCppLogsNetError_None;
		}

	private:
		std::string_view _hostip;
		int _hostport;
		SOCKET _listen_socket;
		std::vector<StCppLogsNetAddrInfo> st_CppLogsNetAddrInfo_Vector;
	};
}