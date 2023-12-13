#include "cpplogs.h"
#include "toolbox.h"

namespace CppLogs {

	CppLogs::~CppLogs()
	{
	}

	Error::EnErrorCode CppLogs::set_item_type(const StCppLogsItem& st_CppLogsItem)
	{
		_st_CppLogsItem = st_CppLogsItem;
		if (!ToolBox::existfile(_filename.data)) {
			return Error::ErrorCode_OpenFileFailed;
		}
		CppLogs::StCppLogsItem st_CppLogsItemCurr = _analy_item();
		if (!st_CppLogsItemCurr.keyError.empty()) {
			return Error::ErrorCode_CreateItemFailed;
		}
		if(st_CppLogsItem.keyInfo.empty() || \
			st_CppLogsItem.keyWarn.empty() || \
			st_CppLogsItem.keyInfo.empty()) {
			return Error::ErrorCode_CreateItemFailed;
		}
		return Error::ErrorCode_None;
	}

	Error::EnErrorCode CppLogs::create_log_file()
	{
		return ToolBox::writefile(_filename.data, "") ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
	}

	Error::EnErrorCode CppLogs::information(const std::string& data)
	{
		return ToolBox::writefile(_filename.data, _format_item(_st_CppLogsItem.keyInfo, data)) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
	}

	Error::EnErrorCode CppLogs::warning(const std::string& data)
	{
		return ToolBox::writefile(_filename.data, _format_item(_st_CppLogsItem.keyWarn, data)) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
	}

	Error::EnErrorCode CppLogs::error(const std::string& data)
	{
		return ToolBox::writefile(_filename.data, _format_item(_st_CppLogsItem.keyError, data)) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
	}
	std::string CppLogs::_format_item(const std::string& itemKey, const std::string& data)
	{
		return itemKey + data;
	}

	CppLogs::StCppLogsItem CppLogs::_analy_item()
	{
		return StCppLogsItem();
	}
}
