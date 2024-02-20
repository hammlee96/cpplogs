/*
* function		: tcp server for windows
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
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#pragma warning(disable:4996)

namespace CppLogs
{
	class SocketTcpWinServer : public ServerBase
	{
	public:
		SocketTcpWinServer(const int& port = 9605) :
			_port(port)
		{
			_st_CppLogsNetAddrInfo_Vector.clear();
		}
		~SocketTcpWinServer()
		{

		}

		Error::EnCppLogsNetError init()
		{
			WSADATA wsaData;
			int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (ret) {
				return Error::EnCppLogsNetError_InitFailed;
			}


			struct ::addrinfo st_addrinfo;
			struct ::addrinfo* st_addrinfo_result;

			::ZeroMemory(&st_addrinfo, sizeof(st_addrinfo));
			st_addrinfo.ai_family = AF_INET;
			st_addrinfo.ai_socktype = SOCK_STREAM;
			st_addrinfo.ai_protocol = IPPROTO_TCP;
			st_addrinfo.ai_flags = AI_PASSIVE;

			std::string str_port = std::to_string(_port);
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
		Error::EnCppLogsNetError accept()
		{
			int ret = 0;
			sockaddr_in st_client_sockaddr_in;
			int len_client_sockaddr_in = sizeof(st_client_sockaddr_in);

			SOCKET client_socket = ::accept(_listen_socket, reinterpret_cast<SOCKADDR*>(&st_client_sockaddr_in), &len_client_sockaddr_in);
			CPPLOGS_DEBUG << "client ip: " << ::inet_ntoa(st_client_sockaddr_in.sin_addr);
			//::inet_ntoa: st_client_sockaddr_in.sin_addr to char*
			//::inet_addr: char* to st_client_sockaddr_in.sin_addr
			if (client_socket == INVALID_SOCKET) {
				::closesocket(_listen_socket);
				::WSACleanup();
				return Error::EnCppLogsNetError_AcceptFailed;
			}
			_st_CppLogsNetAddrInfo_Vector.push_back({ ::inet_ntoa(st_client_sockaddr_in.sin_addr), st_client_sockaddr_in.sin_port, (unsigned int)client_socket });

			return Error::EnCppLogsNetError_None;
		}
		Error::EnCppLogsNetError \
			send(const std::string& destip, const int& destport, const char* data, const size_t& size)
		{
			return Error::EnCppLogsNetError();
		}
		Error::EnCppLogsNetError recv(char* data, int& size)
		{
			int ret = 0;
			for (auto it : _st_CppLogsNetAddrInfo_Vector) {
				::ZeroMemory(data, CPPLOGS_NET_SIZE);
				ret = ::recv(it.fd, data, CPPLOGS_NET_SIZE, 0);
				//CPPLOGS_DEBUG << "[" << it.str_ip << ":" << it.port << "]" << data;
				if (ret < 0) {
					return Error::EnCppLogsNetError_RecvFailed;
				}
				size = ret;
			}
			return Error::EnCppLogsNetError_None;
		}
		Error::EnCppLogsNetError close()
		{
			if (!_st_CppLogsNetAddrInfo_Vector.size()) {
				return Error::EnCppLogsNetError_ClientSizeNull;
			}
			int ret = 0;
			for (unsigned int i = 0; i < _st_CppLogsNetAddrInfo_Vector.size(); i++) {
				::shutdown(_st_CppLogsNetAddrInfo_Vector.at(i).fd, SD_SEND);
				::closesocket(_st_CppLogsNetAddrInfo_Vector.at(i).fd);
			}
			::WSACleanup();
			::closesocket(_listen_socket);
			_listen_socket = INVALID_SOCKET;
			_st_CppLogsNetAddrInfo_Vector.clear();
			::WSACleanup();
			return Error::EnCppLogsNetError_None;
		}

		int connect_num()
		{
			return _st_CppLogsNetAddrInfo_Vector.size();
		}
		std::vector<StCppLogsNetAddrInfo> connect_info()
		{
			return _st_CppLogsNetAddrInfo_Vector;
		}

	private:
		int _port;
		SOCKET _listen_socket;
		std::vector<StCppLogsNetAddrInfo> _st_CppLogsNetAddrInfo_Vector;
	};
}