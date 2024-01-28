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
			_NetClient = std::make_shared<SocketTcp>(hostip, hostport);
			_CppLogsMessage = std::make_shared<CppLogsMessage>();
		}
		~CppLogsStreamClient()
		{

		}

		Error::EnCppLogsNetError init()
		{
			Error::EnCppLogsNetError ret = Error::EnCppLogsNetError_None;
			ret = _NetClient.get()->init();
			if (ret) {
				return ret;
			}
			ret = _NetClient.get()->connect();
			if (ret) {
				return ret;
			}
			return ret;
		}

		Error::EnCppLogsNetError send_file_info(const std::string& filepathname)
		{
			std::string jsValue;
			_CppLogsMessage.get()->CommandSetFileInfo(filepathname, jsValue);
			return _NetClient.get()->send(jsValue);
		}

		Error::EnCppLogsNetError send_log_type(const DataFormat::StCppLogsHeader& st_CppLogsHeader)
		{
			std::string jsValue;
			_CppLogsMessage.get()->CommandSetLogType(st_CppLogsHeader, jsValue);
			return _NetClient.get()->send(jsValue);
		}

		Error::EnCppLogsNetError send_log_data(const DataFormat::StCppLogsItem& st_CppLogsItem)
		{
			std::string jsValue;
			_CppLogsMessage.get()->CommandSetLogData(st_CppLogsItem, jsValue);
			return _NetClient.get()->send(jsValue);
		}

	private:
		CPPLOGS_DISABLE4251(std::shared_ptr<SocketTcp> _NetClient);
		CPPLOGS_DISABLE4251(std::shared_ptr<CppLogsMessage> _CppLogsMessage);
	};
}