#include "cpplogs.h"
#include "toolbox.h"

namespace CppLogs {

	CppLogs::~CppLogs()
	{
	}

	Error::EnErrorCode CppLogs::create_log_file()
	{
		return ToolBox::writefile(_filename.data, "") ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
	}

	Error::EnErrorCode CppLogs::information(const std::string& data)
	{
		std::string datafmt = "[info] - " + data;
		return ToolBox::writefile(_filename.data, datafmt) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
	}

	Error::EnErrorCode CppLogs::warning(const std::string& data)
	{
		std::string datafmt = "[warn] - " + data;
		return ToolBox::writefile(_filename.data, datafmt) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
	}

	Error::EnErrorCode CppLogs::error(const std::string& data)
	{
		std::string datafmt = "[error] - " + data;
		return ToolBox::writefile(_filename.data, datafmt) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
	}
}
