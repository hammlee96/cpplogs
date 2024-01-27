/*
* function		: logs data send to server
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.01.08
*
* change author	: hammlee
* change date	: 2024.01.08
* change log	: init
*/

#pragma once

#include "cpplogs/basetools/base.h"
#include "cpplogs/basetools/net/sockettcp.h"
#include "cpplogs/cpplogsmessage.h"

namespace CppLogs
{
	class CPPLOGS_API CppLogsStreamClient
	{
	public:
		CppLogsStreamClient(const std::string& hostip = "127.0.0.1", const int& hostport = 9605);
		~CppLogsStreamClient()
		{
			if (_NetClient) {
				delete _NetClient;
				_NetClient = nullptr;
			}
			if (_CppLogsMessage) {
				delete _CppLogsMessage;
				_CppLogsMessage = nullptr;
			}
		}

		Error::EnCppLogsNetError init();

		Error::EnCppLogsNetError send_file_info(const std::string& filepathname);

	private:
		const std::string& _hostip;
		const int _hostport;
		SocketTcp *_NetClient;
		CppLogsMessage *_CppLogsMessage;
	};
}