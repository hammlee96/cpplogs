#include"ExampleReadLog.h"
#include <cassert>

int main(int argc, char* argv[])
{
	if (argc != 2) {
		assert(false);
	}
	ExampleReadLog r(argv[1]);
	return 0;
}

ExampleReadLog::ExampleReadLog(const std::string& filepath)
{
	m_pCppLogs = new CppLogs::CppLogsR(filepath);

	CppLogs::DataFormat::StCppLogsHeader st_CppLogsHeader;
	CppLogs::Error::EnErrorCode ec = m_pCppLogs->get_item_type(st_CppLogsHeader);
	if (ec) {
		CPPLOGS_ERROR << ec;
	}
	CPPLOGS_DEBUG << "create_time: " << st_CppLogsHeader.create_time << "\n" << \
		"level: " << st_CppLogsHeader.en_CppLogsLevel << "\n" << \
		"stamp_status: " << st_CppLogsHeader.stampRecord << "\n" << \
		"information key word: " << st_CppLogsHeader.keyInfo << "\n" << \
		"warning key word: " << st_CppLogsHeader.keyWarn << "\n" << \
		"error key word: " << st_CppLogsHeader.keyError;
	std::vector<CppLogs::DataFormat::StCppLogsItem> st_CppLogsItemVector;
	ec = m_pCppLogs->get_items(st_CppLogsItemVector);
	if (ec) {
		CPPLOGS_ERROR << ec;
	}
	for (auto it : st_CppLogsItemVector) {
		CPPLOGS_WARNING << "*************************beg************************";
		CPPLOGS_DEBUG << "key word: " << it.key << "\n" << \
			"second key word: " << it.secondKey << "\n" << \
			"time_stamp: " << it.timeStamp << "\n" << \
			"data: " << it.data;
		CPPLOGS_WARNING << "*************************end************************";
	}
}

ExampleReadLog::~ExampleReadLog()
{
}
