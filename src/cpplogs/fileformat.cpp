#include "fileformat.h"

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
		return FileFormat::StCppLogsHeader();
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
		return Error::ErrorCode_None;
	}

	Error::EnErrorCode FileFormat::create_log_file(const StCppLogsHeader& st_CppLogsHeader)
	{
		return Error::EnErrorCode();
	}

	Error::EnErrorCode FileFormat::writefile(const std::string& key, const std::string secondKey, const std::string& data)
	{
		return Error::EnErrorCode();
	}
}