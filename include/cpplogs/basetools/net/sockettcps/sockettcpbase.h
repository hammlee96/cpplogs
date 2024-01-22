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

namespace CppLogs
{
	class SocketTcpBase
	{
	public:
		SocketTcpBase(const char* hostip = "127.0.0.1", const int hostport = 9605);
		virtual ~SocketTcpBase()
		{

		}
		
		virtual bool init() = 0;
		virtual bool connect() = 0;
		virtual bool disconnect() = 0;
		virtual bool send(const char* data, const unsigned int size) = 0;
		virtual bool recv(char* data, unsigned int* size) = 0;
	};
}