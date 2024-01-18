#include "cpplogs/fileformat.h"

namespace CppLogs {
	FileFormat::~FileFormat()
	{
	}

	DataFormat::StCppLogsHeader FileFormat::get_header()
	{
		return _st_CppLogsIHeader;
	}

	Error::EnErrorCode FileFormat::set_log_header(const DataFormat::StCppLogsHeader& st_CppLogsHeader)
	{
		if (existfile()) {
			Error::EnErrorCode ec = unformat_file_header(_st_CppLogsIHeader);
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
			return ToolBox::writefile(_filename, format_file_header(create_time)) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
		}
		return Error::ErrorCode_LogFileExist;
	}

	Error::EnErrorCode FileFormat::writefile(const DataFormat::EnCppLogsItemType& key, const std::string secondKey, const std::string& data)
	{
		if (existfile()) {
			return ToolBox::writefile(_filename, format_file_data(key, secondKey, data)) ? Error::ErrorCode_None : Error::ErrorCode_OpenFileFailed;
		}
		return Error::ErrorCode_OpenFileFailed;
	}

	std::string FileFormat::format_file_header(const std::string& create_time)
	{
		_st_CppLogsIHeader.create_time = create_time;
		return DataFormat::format_header(_st_CppLogsIHeader);
	}

	Error::EnErrorCode FileFormat::unformat_file_header(DataFormat::StCppLogsHeader& st_CppLogsHeader)
	{
		std::string data;
		ToolBox::readfile(_filename, data);
		return DataFormat::unformat_header(data, st_CppLogsHeader);
	}
	std::string FileFormat::format_file_data(const DataFormat::EnCppLogsItemType& key, const std::string secondKey, const std::string& data)
	{
		return DataFormat::format_data(key, secondKey, data, _st_CppLogsIHeader);
	}

	Error::EnErrorCode FileFormat::unformat_file_data(std::vector<DataFormat::StCppLogsItem> &st_CppLogsItemVector)
	{
		std::string data;
		ToolBox::readfile(_filename, data);
		return DataFormat::unformat_data(data, st_CppLogsItemVector, _st_CppLogsIHeader);
	}
}