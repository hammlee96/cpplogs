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
#include <fcntl.h>

namespace CppLogs
{
	class SocketTcpLinuxServer : public ServerBase
	{
	private:
		struct StEpSockFd
		{
			int sockFd;
			int epFd;
		};
		int _port;
		std::vector<StCppLogsNetAddrInfo> _st_CppLogsNetAddrInfo;
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

		Error::EnCppLogsNetError init() override
		{
			struct sockaddr_in st_sockaddr_in;
			struct epoll_event st_epoll_event;
			int nBufferSize = 2048;
			_StEpSockFd.sockFd = ::socket(AF_INET, SOCK_STREAM, 0);
			if (_StEpSockFd.sockFd < 0) {
				return Error::EnCppLogsNetError_SetSocketFailed;
			}
			int flags = ::fcntl(_StEpSockFd.sockFd, F_GETFL, 0);
			if (flags == -1) {
				perror("Failed to get file status flag");
			}

			// 设置为非阻塞模式
			if (fcntl(_StEpSockFd.sockFd, F_SETFL, flags | O_NONBLOCK) == -1) {
				perror("Failed to set non-blocking mode");
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
			_StEpSockFd.epFd = ::epoll_create(DEF_MAX_CONNECT_CNT);
			if (_StEpSockFd.epFd < 0) {
				return Error::EnCppLogsNetError_CreateEpollFailed;
			}
			st_epoll_event.events = EPOLLIN;
			st_epoll_event.data.fd = _StEpSockFd.sockFd;
			if (::epoll_ctl(_StEpSockFd.epFd, EPOLL_CTL_ADD, _StEpSockFd.sockFd, &st_epoll_event) < 0) {
				return Error::EnCppLogsNetError_CreateEpollFailed;
			}

			return Error::EnCppLogsNetError_None;
		}
		Error::EnCppLogsNetError accept(StNetDataInfo** st_NetDataInfo) override
		{
			epoll_event st_epoll_events[DEF_MAX_CONNECT_CNT];
			int ready_num = ::epoll_wait(_StEpSockFd.epFd, st_epoll_events, DEF_MAX_CONNECT_CNT, -1);
			*st_NetDataInfo = new StNetDataInfo[ready_num];
			for (int i = 0; i < ready_num; i++) {
				socklen_t size_st_sockaddr = sizeof(sockaddr);
				if (st_epoll_events[i].data.fd == _StEpSockFd.sockFd) {
					sockaddr_in st_socket_client_in;
					epoll_event st_epoll_event_add;
					int client_fd = ::accept(_StEpSockFd.sockFd, (struct sockaddr*)&st_socket_client_in, &size_st_sockaddr);
					st_epoll_event_add.events = EPOLLIN;
					st_epoll_event_add.data.fd = client_fd;
					::epoll_ctl(_StEpSockFd.epFd, EPOLL_CTL_ADD, client_fd, &st_epoll_event_add);
					(*st_NetDataInfo)[i].st_net_addr_info.fd = client_fd;
					(*st_NetDataInfo)[i].net_event_type = NetEventType_Conn;
					(*st_NetDataInfo)[i].ready_num = ready_num;
					(*st_NetDataInfo)[i].st_net_addr_info.addr = inet_ntoa(st_socket_client_in.sin_addr);
					(*st_NetDataInfo)[i].st_net_addr_info.port = st_socket_client_in.sin_port;
					(*st_NetDataInfo)[i].data = "";
					(*st_NetDataInfo)[i].size = 0;
					_st_CppLogsNetAddrInfo.push_back({"", inet_ntoa(st_socket_client_in.sin_addr), st_socket_client_in.sin_port, \
						client_fd});
				}
				else {
					char data[DEF_RECV_BUF_SIZE] = { 0 };
					::memset(data, 0, DEF_RECV_BUF_SIZE);
					int client_fd = st_epoll_events[i].data.fd;
					int size = ::recv(client_fd, data, DEF_RECV_BUF_SIZE, 0);
					sockaddr_in st_sockaddr_peer_in;
					::getpeername(client_fd, (struct sockaddr*)&st_sockaddr_peer_in, &size_st_sockaddr);
					(*st_NetDataInfo)[i].st_net_addr_info.fd = client_fd;
					(*st_NetDataInfo)[i].ready_num = ready_num;
					(*st_NetDataInfo)[i].st_net_addr_info.addr = inet_ntoa(st_sockaddr_peer_in.sin_addr);
					(*st_NetDataInfo)[i].st_net_addr_info.port = st_sockaddr_peer_in.sin_port;
					(*st_NetDataInfo)[i].data = data;
					(*st_NetDataInfo)[i].size = size;
					(*st_NetDataInfo)[i].net_event_type = NetEventType_Recv;
					if (size <= 0) {
						(*st_NetDataInfo)[i].net_event_type = NetEventType_DisConn;
						close(client_fd);
					}
				}
			}
			return Error::EnCppLogsNetError_None;
		}
		Error::EnCppLogsNetError \
			send(const std::string& destip, const int& destport, const char* data, const size_t& size) override
		{
			auto it = _st_CppLogsNetAddrInfo.begin();
			while (it != _st_CppLogsNetAddrInfo.end()) {
				if (it.base()->addr == destip && it.base()->port == destport) {
					if (::send(it.base()->fd, data, size, 0) < 0) {
						return Error::EnCppLogsNetError_SendFailed;
					}
					return Error::EnCppLogsNetError_None;
				}
				it++;
			}
			return Error::EnCppLogsNetError_SendFailed;
		}

		Error::EnCppLogsNetError \
			send(const std::string& name, const char* data, const size_t& size) override
		{
			auto it = _st_CppLogsNetAddrInfo.begin();
			while (it != _st_CppLogsNetAddrInfo.end()) {
				if (it.base()->name == name) {
					if (::send(it.base()->fd, data, size, 0) < 0) {
						return Error::EnCppLogsNetError_SendFailed;
					}
					return Error::EnCppLogsNetError_None;
				}
				it++;
			}
			return Error::EnCppLogsNetError_SendFailed;
		}

		Error::EnCppLogsNetError\
			send(const int& client_fd, const char* data, const size_t& size) override
		{
			auto it = _st_CppLogsNetAddrInfo.begin();
			while (it != _st_CppLogsNetAddrInfo.end()) {
				if (it.base()->fd == client_fd) {
					if (::send(client_fd, data, size, 0) < 0) {
						return Error::EnCppLogsNetError_SendFailed;
					}
					return Error::EnCppLogsNetError_None;
				}
				it++;
			}
			return Error::EnCppLogsNetError_SendFailed;
		}

		Error::EnCppLogsNetError recv(char* data, int& size) override
		{
			return Error::EnCppLogsNetError_None;
		}
		Error::EnCppLogsNetError close(const int client_fd) override
		{
			::epoll_ctl(_StEpSockFd.epFd, EPOLL_CTL_DEL, client_fd, NULL);
			::close(client_fd);
			auto it = _st_CppLogsNetAddrInfo.begin();
			while (it != _st_CppLogsNetAddrInfo.end()) {
				if (it.base()->fd == client_fd) {
					_st_CppLogsNetAddrInfo.erase(it);
					break;
				}
				it++;
			}
			return Error::EnCppLogsNetError_None;
		}

		void free_struct(StNetDataInfo* st_NetDataInfo) override
		{
			if (st_NetDataInfo) {
				delete [] st_NetDataInfo;
				st_NetDataInfo = nullptr;
			}
		}

		bool set_name(const std::string& destip, const int& destport, const std::string& name) override
		{
			auto it = _st_CppLogsNetAddrInfo.begin();
			while (it != _st_CppLogsNetAddrInfo.end()) {
				if (it.base()->addr == destip && it.base()->port == destport) {
					it.base()->name = name;
					return true;
				}
				it++;
			}
			return false;
		}

		int connect_num() override
		{
			return _st_CppLogsNetAddrInfo.size();
		}
		std::vector<StCppLogsNetAddrInfo> connect_info() override
		{
			return _st_CppLogsNetAddrInfo;
		}
	};
}