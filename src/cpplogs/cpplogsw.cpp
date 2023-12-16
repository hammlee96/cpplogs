#include "cpplogsw.h"
#include "toolbox.h"

namespace CppLogs {

	//CppLogsW::~CppLogsW()
	//{
	//}

	//Error::EnErrorCode CppLogsW::set_item_type(const FileFormat::StCppLogsHeader& st_CppLogsItem)
	//{
	//	_st_CppLogsItem = st_CppLogsItem;
	//	if (!ToolBox::existfile(_filename.data)) {
	//		return Error::ErrorCode_OpenFileFailed;
	//	}
	//	FileFormat::StCppLogsHeader st_CppLogsItemCurr = _analy_item();
	//	if (!st_CppLogsItemCurr.keyError.empty()) {
	//		return Error::ErrorCode_CreateItemFailed;
	//	}
	//	if(st_CppLogsItem.keyInfo.empty() || \
	//		st_CppLogsItem.keyWarn.empty() || \
	//		st_CppLogsItem.keyInfo.empty()) {
	//		return Error::ErrorCode_CreateItemFailed;
	//	}
	//	return Error::ErrorCode_None;
	//}

	//Error::EnErrorCode CppLogsW::create_log_file()
	//{
	//	return ToolBox::writefile(_filename.data, "") ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
	//}

	//Error::EnErrorCode CppLogsW::information(const std::string& secondaryKey, const std::string& data)
	//{
	//	return ToolBox::writefile(_filename.data, _format_item(_st_CppLogsItem.keyInfo, secondaryKey, data)) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
	//}

	//Error::EnErrorCode CppLogsW::warning(const std::string& secondaryKey, const std::string& data)
	//{
	//	return ToolBox::writefile(_filename.data, _format_item(_st_CppLogsItem.keyWarn, secondaryKey, data)) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
	//}

	//Error::EnErrorCode CppLogsW::error(const std::string& secondaryKey, const std::string& data)
	//{
	//	return ToolBox::writefile(_filename.data, _format_item(_st_CppLogsItem.keyError, secondaryKey, data)) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
	//}

	//std::string CppLogsW::_format_item(const std::string& itemKey, const std::string& secondaryKey, const std::string& data)
	//{
	//	return itemKey + DEF_CPPLOGS_SPLIT + secondaryKey + DEF_CPPLOGS_SPLIT + data;
	//}

	//FileFormat::StCppLogsHeader CppLogsW::_analy_item()
	//{
	//	std::string data;
	//	if (!ToolBox::readfile(_filename.data, data)) {
	//		return { "", "", "", FileFormat::CppLogsLevel_High, true, true };
	//	}
	//	return { "", "", "", FileFormat::CppLogsLevel_High, true, true };
	//	return FileFormat::StCppLogsHeader();
	//}
}
