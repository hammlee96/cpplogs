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
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEF_MAX_LISTEN_CNT		60000
#define DEF_MAX_CONNECT_CNT		DEF_MAX_LISTEN_CNT

namespace CppLogs
{
	class SocketTcpLinuxServer : public ServerBase
	{
	private:
		int _port;
		std::vector<StCppLogsNetAddrInfo> _st_CppLogsNetAddrInfo;
		struct StEpSockFd
		{
			int sockFd;
			int epFd;
		};
		StEpSockFd _StEpSockFd;

	public:
		SocketTcpLinuxServer(const int& port = 9605) : 
			_port(port)
		{
			_st_CppLogsNetAddrInfo.clear();
		}
		~SocketTcpLinuxServer()
		{

		}

		Error::EnCppLogsNetError init()
		{
			struct sockaddr_in st_sockaddr_in;
			struct epoll_event st_epoll_event;
			int nBufferSize = 2048;
			_StEpSockFd.sockFd = ::socket(AF_INET, SOCK_STREAM, 0);
			if (_StEpSockFd.sockFd < 0) {
				return Error::EnCppLogsNetError_SetSocketFailed;
			}
			int ret = ::setsockopt(_StEpSockFd.sockFd, SOL_SOCKET, SO_REUSEADDR, &nBufferSize, sizeof(nBufferSize));
			if (ret < 0) {
				return Error::EnCppLogsNetError_SetSocketFailed;
			}
			st_sockaddr_in.sin_family = AF_INET;
			st_sockaddr_in.sin_port = htons(_port);
			st_sockaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
			if (::bind(_StEpSockFd.sockFd, (struct sockaddr*)&st_sockaddr_in, \
				sizeof(st_sockaddr_in)) < 0) {
				return Error::EnCppLogsNetError_BindFailed;
			}
			if (::listen(_StEpSockFd.sockFd, DEF_MAX_LISTEN_CNT) < 0) {
				return Error::EnCppLogsNetError_ListenFailed;
			}
			_StEpSockFd.epFd = epoll_create(DEF_MAX_CONNECT_CNT);
			if (_StEpSockFd.epFd < 0) {
				return Error::EnCppLogsNetError_CreateEpollFailed;
			}
			st_epoll_event.events = EPOLLIN;
			st_epoll_event.data.fd = _StEpSockFd.epFd;
			if (epoll_ctl(_StEpSockFd.epFd, EPOLL_CTL_ADD, _StEpSockFd.sockFd, &st_epoll_event) < 0) {

			}

			return Error::EnCppLogsNetError_None;
		}
		Error::EnCppLogsNetError accept()
		{
			return Error::EnCppLogsNetError_None;
		}
		Error::EnCppLogsNetError \
			send(const std::string& destip, const int& destport, const char* data, const size_t& size)
		{
			return Error::EnCppLogsNetError_None;
		}
		Error::EnCppLogsNetError recv(char* data, int& size)
		{
			return Error::EnCppLogsNetError_None;
		}
		Error::EnCppLogsNetError close()
		{
			return Error::EnCppLogsNetError_None;
		}

		int connect_num()
		{
			return _st_CppLogsNetAddrInfo.size();
		}
		std::vector<StCppLogsNetAddrInfo> connect_info()
		{
			return _st_CppLogsNetAddrInfo;
		}
	};
}