#include "dataformat.h"

namespace CppLogs {
	CppLogs::DataFormat::DataFormat()
	{
	}

	CppLogs::DataFormat::~DataFormat()
	{
	}

	std::string CppLogs::DataFormat::format_data(const std::string& data)
	{
		return std::string();
	}

	DataFormat::StCppLogsItem CppLogs::DataFormat::unformat_data(const std::string& data)
	{
		return StCppLogsItem();
	}
}
