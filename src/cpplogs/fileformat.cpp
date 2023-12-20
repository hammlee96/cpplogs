#include "fileformat.h"

namespace CppLogs {
	FileFormat::~FileFormat()
	{
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
		if (!existfile()) {
			return ToolBox::writefile(_filename, format_header(create_time)) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
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
		return ToolBox::format("<#%s#>\ncreate_time:%s\nlevel:%d\ninfo:%s\nwarn:%s\nerror:%s\ntime_stamp:%s\nfile_line:%s\n<#/%s#>", \
			DEF_HEADER, create_time.c_str(), (int)_st_CppLogsIHeader.en_CppLogsLevel, _st_CppLogsIHeader.keyInfo.c_str(), _st_CppLogsIHeader.keyWarn.c_str(), \
			_st_CppLogsIHeader.keyError.c_str(), _st_CppLogsIHeader.stampRecord ? "y" : "n", _st_CppLogsIHeader.fileLineRecord ? "y" : "n", DEF_HEADER);
	}

	Error::EnErrorCode FileFormat::unformat_header(FileFormat::StCppLogsHeader& st_CppLogsHeader)
	{
		std::string data;
		std::string pattern = ToolBox::format("<#%s#>([\\s\\S]*?)<#/%s#>", DEF_HEADER, DEF_HEADER);
		Error::EnErrorCode ec = Error::ErrorCode_None;
		ToolBox::readfile(_filename, data);
		std::vector<std::string> result = ToolBox::regexmatch(data, pattern);
		//for (auto it : result) {
		//	CPPLOGS_DEBUG << it;
		//}
		if (result.size() != 1) {
			ec = Error::ErrorCode_HeaderDamage;
		}
		return ec;
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