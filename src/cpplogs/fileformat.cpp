#include "fileformat.h"
#include "base.h"

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
		return ToolBox::format("<#%s#>\n%s:%s\n%s:%d\n%s:%s\n%s:%s\n%s:%s\n%s:%s\n%s:%s\n<#/%s#>", \
			DEF_HEADER, \
			DEF_HEADER_CREATE_TIME, create_time.c_str(), \
			DEF_HEADER_LEVEL, (int)_st_CppLogsIHeader.en_CppLogsLevel, \
			DEF_HEADER_INFO, _st_CppLogsIHeader.keyInfo.c_str(), \
			DEF_HEADER_WARN, _st_CppLogsIHeader.keyWarn.c_str(), \
			DEF_HEADER_ERROR, _st_CppLogsIHeader.keyError.c_str(), \
			DEF_HEADER_TIME_STAMP, _st_CppLogsIHeader.stampRecord ? "y" : "n", \
			DEF_HEADER_FILE_LINE, _st_CppLogsIHeader.fileLineRecord ? "y" : "n", \
			DEF_HEADER);
	}

	Error::EnErrorCode FileFormat::unformat_header(FileFormat::StCppLogsHeader& st_CppLogsHeader)
	{
		std::string data;
		std::string pattern = ToolBox::format("<#%s#>([\\s\\S]*?)<#/%s#>", DEF_HEADER, DEF_HEADER);
		ToolBox::readfile(_filename, data);
		std::vector<std::string> result = ToolBox::regexmatch(data, pattern);
		//for (auto it : result) {
		//	CPPLOGS_DEBUG << it;
		//}
		if (result.size() != 1) {
			return Error::ErrorCode_HeaderDamage;
		}

		std::map<std::string, std::string> mm = ToolBox::regexmatchsplit(data, pattern, ":");
		if (mm.size() != 7) {
			return Error::ErrorCode_HeaderDamage;
		}
		for (auto it : mm) {
			if (it.first == DEF_HEADER_CREATE_TIME) {
				st_CppLogsHeader.create_time = it.first;
			}
			else if (it.first == DEF_HEADER_LEVEL) {
				st_CppLogsHeader.en_CppLogsLevel == (EnCppLogsLevel)stoi(it.second);
			}
			else if (it.first == DEF_HEADER_INFO) {
				st_CppLogsHeader.keyInfo = it.second;
			}
			else if (it.first == DEF_HEADER_WARN) {
				st_CppLogsHeader.keyWarn = it.second;
			}
			else if (it.first == DEF_HEADER_ERROR) {
				st_CppLogsHeader.keyError = it.second;
			}
			else if (it.first == DEF_HEADER_TIME_STAMP) {
				st_CppLogsHeader.stampRecord = it.second == "y" ? true : false;
			}
			else if (it.first == DEF_HEADER_FILE_LINE) {
				st_CppLogsHeader.fileLineRecord = it.second == "y" ? true : false;
			}
		}
		//for (auto it : mm) {
		//	CPPLOGS_DEBUG << it.first<<":"<<it.second;
		//}

		return Error::ErrorCode_None;
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