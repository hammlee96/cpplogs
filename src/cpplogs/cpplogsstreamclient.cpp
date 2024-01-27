#include "cpplogs/cpplogsstreamclient.h"

namespace CppLogs {
	CppLogsStreamClient::CppLogsStreamClient(const std::string& hostip, const int& hostport) :
		_hostip(hostip), _hostport(hostport)
	{
		_NetClient = new SocketTcp(_hostip, _hostport);
		_CppLogsMessage = new CppLogsMessage();
	}

	Error::EnCppLogsNetError CppLogsStreamClient::init()
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

	Error::EnCppLogsNetError CppLogsStreamClient::send_file_info(const std::string& filepathname)
	{
		std::string jsValue;
		_CppLogsMessage->CommandSetFileInfo(filepathname, jsValue);
		//CPPLOGS_DEBUG << jsValue;
		_NetClient->send(jsValue);
		return Error::EnCppLogsNetError_None;
	}
}