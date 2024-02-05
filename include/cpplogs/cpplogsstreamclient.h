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
#include "cpplogs/basetools/net/netclient.h"
#include "cpplogs/cpplogsmessage.h"

namespace CppLogs
{
	class CPPLOGS_API CppLogsStreamClient
	{
	public:
		CppLogsStreamClient(const std::string& hostip = "127.0.0.1", const int& hostport = 9605)
		{
			_NetClient = std::make_shared<NetClient>(hostip, hostport);
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
			_CppLogsMessage.get()->CommandSetFileInfo(jsValue, filepathname);
			return _NetClient.get()->send(jsValue);
		}

		Error::EnCppLogsNetError send_log_type(const DataFormat::StCppLogsHeader& st_CppLogsHeader)
		{
			std::string jsValue;
			_CppLogsMessage.get()->CommandSetLogType(jsValue, st_CppLogsHeader);
			return _NetClient.get()->send(jsValue);
		}

		Error::EnCppLogsNetError send_log_data_info(const std::string secondKey, const std::string& data)
		{
			std::string jsValue;
			_CppLogsMessage.get()->CommandSetLogData(jsValue, DataFormat::CppLogsItemType_Info, secondKey, data);
			return _NetClient.get()->send(jsValue);
		}

		Error::EnCppLogsNetError send_log_data_warn(const std::string secondKey, const std::string& data)
		{
			std::string jsValue;
			_CppLogsMessage.get()->CommandSetLogData(jsValue, DataFormat::CppLogsItemType_Warn, secondKey, data);
			return _NetClient.get()->send(jsValue);
		}

		Error::EnCppLogsNetError send_log_data_error(const std::string secondKey, const std::string& data)
		{
			std::string jsValue;
			_CppLogsMessage.get()->CommandSetLogData(jsValue, DataFormat::CppLogsItemType_Error, secondKey, data);
			return _NetClient.get()->send(jsValue);
		}

		// TODO: return error need redefine
		Error::EnCppLogsNetError send_log_file(const std::string& filename)
		{
			std::string data;
			ToolBox::readfile(filename, data);
			return _NetClient.get()->send(data);
		}

	private:
		CPPLOGS_DISABLE4251(std::shared_ptr<NetClient> _NetClient);
		CPPLOGS_DISABLE4251(std::shared_ptr<CppLogsMessage> _CppLogsMessage);
	};
}