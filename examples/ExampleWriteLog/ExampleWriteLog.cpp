#include "ExampleWriteLog.h"
#include "../../include/basetools/base.h"

int main()
{
	ExampleWriteLog w;
	return 0;
}

ExampleWriteLog::ExampleWriteLog()
{
	m_pCppLogs = new CppLogs::CppLogsW("D:/test_field/test_cpplogs/231216_testapp");
	m_pCppLogs->set_item_type({ "infomation", "warning", "error", CppLogs::FileFormat::CppLogsLevel_High, true, true });
	CppLogs::Error::EnErrorCode ec = m_pCppLogs->create_log_file("2023-12-16 22:03:00");
	CppLogs::FileFormat::StCppLogsHeader st_CppLogsHeader;
	ec = m_pCppLogs->_fileFormat->unformat_header(st_CppLogsHeader);
	CPPLOGS_DEBUG << ec;
}

ExampleWriteLog::~ExampleWriteLog()
{
}
