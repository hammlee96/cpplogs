#include "fileformat.h"
#include "base.h"
#include <string>

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
			Error::EnErrorCode ec = unformat_header(_st_CppLogsIHeader);
			if (!ec) {
				return Error::ErrorCode_LogFileExist;
			}
			return ec;
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
		return ToolBox::format("<#%s#>\n%s:%s\n%s:%d\n%s:%s\n%s:%s\n%s:%s\n%s:%s\n<#/%s#>", \
			DEF_HEADER, \
			DEF_HEADER_CREATE_TIME, create_time.c_str(), \
			DEF_HEADER_LEVEL, (int)_st_CppLogsIHeader.en_CppLogsLevel, \
			DEF_HEADER_INFO, _st_CppLogsIHeader.keyInfo.c_str(), \
			DEF_HEADER_WARN, _st_CppLogsIHeader.keyWarn.c_str(), \
			DEF_HEADER_ERROR, _st_CppLogsIHeader.keyError.c_str(), \
			DEF_HEADER_TIME_STAMP, _st_CppLogsIHeader.stampRecord ? DEF_CPPLOGS_TRUE : DEF_CPPLOGS_FALSE, \
			DEF_HEADER);
	}

	Error::EnErrorCode FileFormat::unformat_header(FileFormat::StCppLogsHeader& st_CppLogsHeader)
	{
		std::string data;
		std::string pattern = ToolBox::format("<#%s#>([\\s\\S]*?)<#/%s#>", DEF_HEADER, DEF_HEADER);
		ToolBox::readfile(_filename, data);
		std::vector<std::string> result = ToolBox::regexmatch(data, pattern);

		if (result.size() != 1) {
			return Error::ErrorCode_HeaderDamage;
		}

		std::map<std::string, std::string> mm = ToolBox::regexmatchsplit(result.at(0), pattern, ":");
		if (mm.size() != 6) {
			return Error::ErrorCode_HeaderDamage;
		}
		for (auto it : mm) {
			if (it.first == DEF_HEADER_CREATE_TIME) {
				st_CppLogsHeader.create_time = it.second;
			}
			else if (it.first == DEF_HEADER_LEVEL) {
				st_CppLogsHeader.en_CppLogsLevel = (EnCppLogsLevel)std::stoi(it.second);
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
				st_CppLogsHeader.stampRecord = it.second == DEF_CPPLOGS_TRUE ? true : false;
			}
		}

		return Error::ErrorCode_None;
	}
	std::string FileFormat::format_data(const FileFormat::EnCppLogsItemType& key, const std::string secondKey, const std::string& data)
	{
		std::string keystr = "";
		switch (key) {
		case CppLogsItemType_Info: {
			keystr = _st_CppLogsIHeader.keyInfo;
		}break;
		case CppLogsItemType_Warn: {
			keystr = _st_CppLogsIHeader.keyWarn;
		}break;
		case CppLogsItemType_Error: {
			keystr = _st_CppLogsIHeader.keyError;
		}break;
		}
		std::string formatdata = ToolBox::format("<#%s#%s", \
			keystr.c_str(), secondKey.c_str());
		if (_st_CppLogsIHeader.stampRecord) {
			ToolBox::StCppLogsDateTime st_CppLogsDateTime = ToolBox::gettime();
			formatdata = ToolBox::format("%s#T%d-%d-%d %d:%d:%d", \
				formatdata.c_str(), \
				st_CppLogsDateTime.uiYear, st_CppLogsDateTime.uiMonth, st_CppLogsDateTime.uiDay, \
				st_CppLogsDateTime.uiHour, st_CppLogsDateTime.uiMinute, st_CppLogsDateTime.uiSecond);
		}

		return ToolBox::format("%s#>%s<#/%s#>", \
			formatdata.c_str(), data.c_str(), keystr.c_str());
	}

	Error::EnErrorCode FileFormat::unformat_data(std::vector<FileFormat::StCppLogsItem> &st_CppLogsItemVector)
	{
		std::string data;
		std::string pattern;
		if (_st_CppLogsIHeader.stampRecord) {
			pattern = "<#(.*)?#(.*)?#T(.*)?#>([\\s\\S]*?)<#/(.*)?#>";
		}
		else {
			pattern = "<#(.*)?#(.*)?#>([\\s\\S]*?)<#/(.*)?#>";
		}
		std::regex matchStr(pattern);
		std::smatch matched;
		ToolBox::readfile(_filename, data);
		std::istringstream iss(data);
		std::string line;
		while (getline(iss, line)) {
			if (std::regex_match(line, matched, matchStr)) {
				if (_st_CppLogsIHeader.stampRecord && matched.size() == 6) {
					st_CppLogsItemVector.push_back({ matched.str(1), matched.str(2), matched.str(3), \
						matched.str(4) });
				}
				else if (!_st_CppLogsIHeader.stampRecord && matched.size() == 5) {
					st_CppLogsItemVector.push_back({ matched.str(1), matched.str(2), matched.str(3), \
						matched.str(4) });
				}
			}
		}
		return Error::EnErrorCode();
	}
}