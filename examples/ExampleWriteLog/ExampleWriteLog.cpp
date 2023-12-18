#include "ExampleWriteLog.h"
#include "../../include/basetools/base.h"

int main()
{
	ExampleWriteLog w;
	return 0;
}

ExampleWriteLog::ExampleWriteLog()
{
	m_pCppLogs = new CppLogs::CppLogsW("D:/test_field/test_cpplogs/231216_testapp.log");
	CppLogs::Error::EnErrorCode ec = m_pCppLogs->create_log_file("2023-12-16 22:03:00");
	CPPLOGS_DEBUG << ec;
}

ExampleWriteLog::~ExampleWriteLog()
{
}
