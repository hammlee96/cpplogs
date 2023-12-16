#include "fileformat.h"
#include "toolbox.h"

namespace CppLogs {
	FileFormat::~FileFormat()
	{
	}

	bool FileFormat::existfile()
	{
		std::ifstream f(_filename.c_str());
		return f.good();
	}

	FileFormat::StCppLogsHeader FileFormat::analysis_header()
	{
		return _st_CppLogsIHeader;
	}

	Error::EnErrorCode FileFormat::set_log_header(const StCppLogsHeader& st_CppLogsHeader)
	{
		if (!existfile()) {
			return Error::ErrorCode_OpenFileFailed;
		}
		FileFormat::StCppLogsHeader st_CppLogsItemCurr = analysis_header();
		if (!st_CppLogsItemCurr.keyError.empty()) {
			return Error::ErrorCode_CreateItemFailed;
		}
		if (st_CppLogsHeader.keyInfo.empty() || \
			st_CppLogsHeader.keyWarn.empty() || \
			st_CppLogsHeader.keyInfo.empty()) {
			return Error::ErrorCode_CreateItemFailed;
		}
		_st_CppLogsIHeader = st_CppLogsHeader;
		return Error::ErrorCode_None;
	}

	Error::EnErrorCode FileFormat::create_log_file()
	{
		if (!existfile()) {
			return ToolBox::writefile(_filename, format_header()) ? Error::ErrorCode_OpenFileFailed : Error::ErrorCode_None;
		}
		return Error::ErrorCode_None;
	}

	Error::EnErrorCode FileFormat::writefile(const std::string& key, const std::string secondKey, const std::string& data)
	{
		return Error::EnErrorCode();
	}

	std::string FileFormat::format_header()
	{
		return std::string();
	}

	FileFormat::StCppLogsItem FileFormat::unformat_header()
	{
		return FileFormat::StCppLogsItem();
	}

	std::string FileFormat::format_data(const std::string& data)
	{
		return std::string();
	}

	FileFormat::StCppLogsItem FileFormat::unformat_data(const std::string& data)
	{
		return FileFormat::StCppLogsItem();
	}
}