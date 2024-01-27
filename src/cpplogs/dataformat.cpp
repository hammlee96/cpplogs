#include "cpplogs/dataformat.h"

namespace CppLogs {

	std::string DataFormat::format_header(const DataFormat::StCppLogsHeader& st_CppLogsHeader)
	{
		return ToolBox::format("<#%s#>\n%s:%s\n%s:%d\n%s:%s\n%s:%s\n%s:%s\n%s:%s\n<#/%s#>", \
			CPPLOGS_DEF_HEADER, \
			CPPLOGS_DEF_HEADER_CREATE_TIME, st_CppLogsHeader.create_time.c_str(), \
			CPPLOGS_DEF_HEADER_LEVEL, (int)st_CppLogsHeader.en_CppLogsLevel, \
			CPPLOGS_DEF_HEADER_INFO, st_CppLogsHeader.keyInfo.c_str(), \
			CPPLOGS_DEF_HEADER_WARN, st_CppLogsHeader.keyWarn.c_str(), \
			CPPLOGS_DEF_HEADER_ERROR, st_CppLogsHeader.keyError.c_str(), \
			CPPLOGS_DEF_HEADER_TIME_STAMP, st_CppLogsHeader.stampRecord ? CPPLOGS_DEF_CPPLOGS_TRUE : CPPLOGS_DEF_CPPLOGS_FALSE, \
			CPPLOGS_DEF_HEADER);
	}

	Error::EnErrorCode DataFormat::unformat_header(const std::string& data, DataFormat::StCppLogsHeader& st_CppLogsHeader)
	{
		std::string pattern = ToolBox::format("<#%s#>([\\s\\S]*?)<#/%s#>", CPPLOGS_DEF_HEADER, CPPLOGS_DEF_HEADER);
		std::vector<std::string> result = ToolBox::regexmatch(data, pattern);

		if (result.size() != 1) {
			return Error::ErrorCode_HeaderDamage;
		}

		std::map<std::string, std::string> mm = ToolBox::regexmatchsplit(result.at(0), pattern, ":");
		if (mm.size() != 6) {
			return Error::ErrorCode_HeaderDamage;
		}
		for (auto it : mm) {
			if (it.first == CPPLOGS_DEF_HEADER_CREATE_TIME) {
				st_CppLogsHeader.create_time = it.second;
			}
			else if (it.first == CPPLOGS_DEF_HEADER_LEVEL) {
				st_CppLogsHeader.en_CppLogsLevel = (EnCppLogsLevel)std::stoi(it.second);
			}
			else if (it.first == CPPLOGS_DEF_HEADER_INFO) {
				st_CppLogsHeader.keyInfo = it.second;
			}
			else if (it.first == CPPLOGS_DEF_HEADER_WARN) {
				st_CppLogsHeader.keyWarn = it.second;
			}
			else if (it.first == CPPLOGS_DEF_HEADER_ERROR) {
				st_CppLogsHeader.keyError = it.second;
			}
			else if (it.first == CPPLOGS_DEF_HEADER_TIME_STAMP) {
				st_CppLogsHeader.stampRecord = it.second == CPPLOGS_DEF_CPPLOGS_TRUE ? true : false;
			}
		}

		return Error::ErrorCode_None;
	}

	std::string DataFormat::format_data(const DataFormat::EnCppLogsItemType& key, const std::string secondKey, const std::string& data, const DataFormat::StCppLogsHeader& st_CppLogsHeader)
	{
		std::string keystr = "";
		switch (key) {
		case CppLogsItemType_Info: {
			keystr = st_CppLogsHeader.keyInfo;
		}break;
		case CppLogsItemType_Warn: {
			keystr = st_CppLogsHeader.keyWarn;
		}break;
		case CppLogsItemType_Error: {
			keystr = st_CppLogsHeader.keyError;
		}break;
		}
		std::string formatdata = ToolBox::format("<#%s#%s", \
			keystr.c_str(), secondKey.c_str());
		if (st_CppLogsHeader.stampRecord) {
			ToolBox::StCppLogsDateTime st_CppLogsDateTime = ToolBox::gettime();
			formatdata = ToolBox::format("%s#T%d-%d-%d %d:%d:%d", \
				formatdata.c_str(), \
				st_CppLogsDateTime.uiYear, st_CppLogsDateTime.uiMonth, st_CppLogsDateTime.uiDay, \
				st_CppLogsDateTime.uiHour, st_CppLogsDateTime.uiMinute, st_CppLogsDateTime.uiSecond);
		}

		return ToolBox::format("%s#>%s<#/%s#>", \
			formatdata.c_str(), data.c_str(), keystr.c_str());
	}

	Error::EnErrorCode DataFormat::unformat_data(const std::string& data, std::vector<DataFormat::StCppLogsItem>& st_CppLogsItemVector, const DataFormat::StCppLogsHeader& st_CppLogsHeader)
	{
		std::string pattern;
		if (st_CppLogsHeader.stampRecord) {
			pattern = "<#(.*)?#(.*)?#T(.*)?#>([\\s\\S]*?)<#/(.*)?#>";
		}
		else {
			pattern = "<#(.*)?#(.*)?#>([\\s\\S]*?)<#/(.*)?#>";
		}
		std::regex matchStr(pattern);
		std::smatch matched;
		std::istringstream iss(data);
		std::string line;
		bool isFind = false;
		while (getline(iss, line)) {
			if (std::regex_match(line, matched, matchStr)) {
				if (st_CppLogsHeader.stampRecord && matched.size() == 6) {
					st_CppLogsItemVector.push_back({ matched.str(1), matched.str(2), matched.str(3), \
						matched.str(4) });
					isFind = true;
				}
				else if (!st_CppLogsHeader.stampRecord && matched.size() == 5) {
					st_CppLogsItemVector.push_back({ matched.str(1), matched.str(2), matched.str(3), \
						matched.str(4) });
					isFind = true;
				}
			}
		}
		return (isFind ? Error::ErrorCode_None : Error::ErrorCode_FindItemFailed);
	}
}