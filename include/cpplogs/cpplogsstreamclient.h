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
			_NetClient = std::make_shared<CppLogs::NetClient>(hostip, hostport);
			_CppLogsMessage = std::make_shared<CppLogs::CppLogsMessage>();
		}
		~CppLogsStreamClient()
		{

		}

		CppLogs::Error::EnCppLogsNetError init()
		{
			CppLogs::Error::EnCppLogsNetError ret = CppLogs::Error::EnCppLogsNetError_None;
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

		void send_file_info(const std::string& filepathname)
		{
			_filepathname = filepathname;
		}

		bool send_log_type(const CppLogs::DataFormat::StCppLogsHeader& st_CppLogsHeader = DEF_CPPLOGS_ITEMS)
		{
			if (!st_CppLogsHeader.keyInfo.empty() && \
				!st_CppLogsHeader.keyWarn.empty() && \
				!st_CppLogsHeader.keyError.empty()) {
				_st_CppLogsHeader = st_CppLogsHeader;
				return true;
			}
			return false;
		}

		CppLogs::Error::EnCppLogsNetError set_account_name(const std::string& name)
		{
			std::string jsValue;
			_CppLogsMessage.get()->CommandSetAccountName(jsValue, name);
			return _NetClient.get()->send(jsValue);
		}

		template<typename... T_InLengthData>
		CppLogs::Error::EnCppLogsNetError send_log_data_info(const std::string secondKey, const std::string& format, T_InLengthData... data)
		{
			std::string jsValue;
			_CppLogsMessage.get()->CommandSetLogData(jsValue, _filepathname, _st_CppLogsHeader, CppLogs::DataFormat::CppLogsItemType_Info, secondKey, ToolBox::format(format, data...));
			return _NetClient.get()->send(jsValue);
		}

		template<typename... T_InLengthData>
		CppLogs::Error::EnCppLogsNetError send_log_data_warn(const std::string secondKey, const std::string& format, T_InLengthData... data)
		{
			std::string jsValue;
			_CppLogsMessage.get()->CommandSetLogData(jsValue, _filepathname, _st_CppLogsHeader, CppLogs::DataFormat::CppLogsItemType_Warn, secondKey, ToolBox::format(format, data...));
			return _NetClient.get()->send(jsValue);
		}

		template<typename... T_InLengthData>
		CppLogs::Error::EnCppLogsNetError send_log_data_error(const std::string secondKey, const std::string& format, T_InLengthData... data)
		{
			std::string jsValue;
			_CppLogsMessage.get()->CommandSetLogData(jsValue, _filepathname, _st_CppLogsHeader, CppLogs::DataFormat::CppLogsItemType_Error, secondKey, ToolBox::format(format, data...));
			return _NetClient.get()->send(jsValue);
		}

		CppLogs::Error::EnCppLogsNetError send_string(const std::string& str_data)
		{
			return _NetClient.get()->send(str_data);
		}

		// TODO: return error need redefine
		CppLogs::Error::EnCppLogsNetError send_log_file(const std::string& filename)
		{
			std::string data;
			CppLogs::ToolBox::readfile(filename, data);
			return _NetClient.get()->send(data);
		}

		CppLogs::Error::EnCppLogsNetError recv(char* data, size_t& size)
		{
			return _NetClient.get()->recv(data, size);
		}

	private:
		CPPLOGS_DISABLE4251(std::shared_ptr<CppLogs::NetClient> _NetClient);
		CPPLOGS_DISABLE4251(std::shared_ptr<CppLogs::CppLogsMessage> _CppLogsMessage);
		CPPLOGS_DISABLE4251(std::string _filepathname);
		CppLogs::DataFormat::StCppLogsHeader _st_CppLogsHeader;
	};
}