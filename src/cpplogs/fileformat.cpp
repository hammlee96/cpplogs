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

	std::any FileFormat::analysis_header()
	{
		return std::any();
	}

	FileFormat::StCppLogsHeader FileFormat::get_header()
	{
		return _st_CppLogsIHeader;
	}

	Error::EnErrorCode FileFormat::set_log_header(const StCppLogsHeader& st_CppLogsHeader)
	{
		if (existfile()) {
			return Error::ErrorCode_LogFileExist;
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
		CPPLOGS_DEBUG << existfile();
		if (!existfile()) {
			return ToolBox::writefile(_filename + CPPLOGS_EXTNAME, format_header(create_time)) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
		}
		return Error::ErrorCode_LogFileExist;
	}

	Error::EnErrorCode FileFormat::writefile(const FileFormat::EnCppLogsItemType& key, const std::string secondKey, const std::string& data)
	{
		if (existfile()) {
			return ToolBox::writefile(_filename, format_data(key, secondKey, data)) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
		}
		return Error::ErrorCode_OpenFileFailed;
	}

	std::string FileFormat::format_header(const std::string& create_time)
	{
		return std::format("<#header#>\ncreate_time:{}\nlevel:{}\ninfo:{}\nwarn:{}\nerror:{}\ntime_stamp:{}\nfile_line:{}\n<#headerEnd#>", \
			create_time.c_str(), (int)_st_CppLogsIHeader.en_CppLogsLevel, _st_CppLogsIHeader.keyInfo.c_str(), _st_CppLogsIHeader.keyWarn.c_str(), \
			_st_CppLogsIHeader.keyError.c_str(), _st_CppLogsIHeader.stampRecord ? "y" : "n", _st_CppLogsIHeader.fileLineRecord ? "y" : "n");
	}

	FileFormat::StCppLogsHeader FileFormat::unformat_header()
	{

		return FileFormat::StCppLogsHeader();
	}

	std::string FileFormat::format_data(const FileFormat::EnCppLogsItemType& key, const std::string secondKey, const std::string& data)
	{
		return std::string();
	}

	FileFormat::StCppLogsItem FileFormat::unformat_data()
	{
		return FileFormat::StCppLogsItem();
	}
}