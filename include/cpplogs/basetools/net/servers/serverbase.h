/*
* function		: net server base
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.02.05
*
* change author	: hammlee
* change date	: 2024.02.05
* change log	: init
*/

#pragma once

#include <iostream>
#include <string>
#include "cpplogs/basetools/error.h"

#define CPPLOGS_NET_SIZE	512

#define DEF_MAX_LISTEN_CNT		6000
#define DEF_MAX_CONNECT_CNT		DEF_MAX_LISTEN_CNT
#define DEF_RECV_BUF_SIZE		1024

namespace CppLogs
{
	class ServerBase
	{
	public:
		struct StCppLogsNetAddrInfo
		{
			std::string name;
			std::string addr;
			unsigned short port;
			int fd;
		};
		enum EnNetEventType
		{
			NetEventType_Conn,
			NetEventType_DisConn,
			NetEventType_Recv
		};
		struct StNetDataInfo
		{
			EnNetEventType net_event_type;
			StCppLogsNetAddrInfo st_net_addr_info;
			int ready_num;
			std::string data;
			int size;
		};

	public:
		ServerBase(const int& port = 9605)
		{

		}
		virtual ~ServerBase()
		{

		}

		virtual Error::EnCppLogsNetError init() = 0;
		virtual Error::EnCppLogsNetError accept(StNetDataInfo** st_NetDataInfo) = 0;
		virtual Error::EnCppLogsNetError \
			send(const std::string& destip, const int& destport, const char* data, const size_t& size) = 0; 
		virtual Error::EnCppLogsNetError \
			send(const std::string& name, const char* data, const size_t& size) = 0;
		virtual Error::EnCppLogsNetError\
			send(const int& client_fd, const char* data, const size_t& size) = 0;
		virtual Error::EnCppLogsNetError recv(char* data, int& size) = 0;
		virtual Error::EnCppLogsNetError close(const int client_fd) = 0;
		virtual void free_struct(StNetDataInfo* st_NetDataInfo) = 0;

		virtual bool set_name(const std::string& destip, const int& destport, const std::string& name) = 0;

		virtual int connect_num() = 0;
		virtual std::vector<StCppLogsNetAddrInfo> connect_info() = 0;
	};
}