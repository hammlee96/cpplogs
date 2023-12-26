#include "ExampleWriteLog.h"
#include "basetools/base.h"

int main()
{
	ExampleWriteLog w;
	return 0;
}

ExampleWriteLog::ExampleWriteLog()
{
#if defined(CPPLOGS_SYSTEM_WINDOWS)
	m_pCppLogs = new CppLogs::CppLogsW("D:/test_field/test_cpplogs/231216_testapp");
#else
	m_pCppLogs = new CppLogs::CppLogsW("/root/test_field/cpplogs/231216_testapp");
#endif
	m_pCppLogs->set_item_type({"", "infomation", "warning", "error", CppLogs::FileFormat::CppLogsLevel_High, true});
	CppLogs::Error::EnErrorCode ec = m_pCppLogs->create_file("2023-12-16 22:03:00");
	ec = m_pCppLogs->information("secondinfo", "jkfaweofjoejr");
	std::vector<CppLogs::FileFormat::StCppLogsItem> st_CppLogsItemVector;
	m_pCppLogs->unformat_data(st_CppLogsItemVector);
	//CppLogs::FileFormat::StCppLogsHeader st_CppLogsHeader;
	//ec = m_pCppLogs->unformat_header(st_CppLogsHeader);
	CPPLOGS_DEBUG << ec;
}

ExampleWriteLog::~ExampleWriteLog()
{
}
