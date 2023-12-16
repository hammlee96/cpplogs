#include "fileformat.h"
#include "toolbox.h"
#include <format>

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
		return {"", "", "", (FileFormat::EnCppLogsLevel)1, true, true};
	}

	FileFormat::StCppLogsHeader FileFormat::get_header()
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

	Error::EnErrorCode FileFormat::create_log_file(const std::string& create_time)
	{
		if (!existfile()) {
			return ToolBox::writefile(_filename, format_header(create_time)) ? Error::ErrorCode_OpenFileFailed : Error::ErrorCode_None;
		}
		return Error::ErrorCode_LogFileExist;
	}

	Error::EnErrorCode FileFormat::writefile(const std::string& key, const std::string secondKey, const std::string& data)
	{
		return Error::EnErrorCode();
	}

	std::string FileFormat::format_header(const std::string& create_time)
	{
		return std::format("<#header>\ncreate_time:{}\nlevel:{}\ninfo:{}\nwarn:{}\nerror:{}\ntime_stamp:{}\nfile_line:{}\n<#headerEnd>", \
			create_time.c_str(), (int)_st_CppLogsIHeader.en_CppLogsLevel, _st_CppLogsIHeader.keyInfo.c_str(), _st_CppLogsIHeader.keyWarn.c_str(), \
			_st_CppLogsIHeader.keyError.c_str(), _st_CppLogsIHeader.stampRecord ? "y" : "n", _st_CppLogsIHeader.fileLineRecord ? "y" : "n");
	}

	FileFormat::StCppLogsHeader FileFormat::unformat_header()
	{
		return FileFormat::StCppLogsHeader();
	}

	std::string FileFormat::format_data(const std::string& data)
	{
		return std::string();
	}

	FileFormat::StCppLogsItem FileFormat::unformat_data()
	{
		return FileFormat::StCppLogsItem();
	}
}