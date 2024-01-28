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
		CppLogsStreamClient(const std::string& hostip = "127.0.0.1", const int& hostport = 9605)
		{
			_NetClient = new SocketTcp(hostip, hostport);
			_CppLogsMessage = new CppLogsMessage();
		}
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

		Error::EnCppLogsNetError init()
		{
			Error::EnCppLogsNetError ret = Error::EnCppLogsNetError_None;
			ret = _NetClient->init();
			if (ret) {
				return ret;
			}
			ret = _NetClient->connect();
			if (ret) {
				return ret;
			}
			return ret;
		}

		Error::EnCppLogsNetError send_file_info(const std::string& filepathname)
		{
			std::string jsValue;
			_CppLogsMessage->CommandSetFileInfo(filepathname, jsValue);
			//CPPLOGS_DEBUG << jsValue;
			_NetClient->send(jsValue);
			return Error::EnCppLogsNetError_None;
		}

	private:
		SocketTcp *_NetClient;
		CppLogsMessage *_CppLogsMessage;
	};
}