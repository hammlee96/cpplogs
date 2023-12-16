#include "ExampleWriteLog.h"

int main()
{
	ExampleWriteLog w;
	return 0;
}

ExampleWriteLog::ExampleWriteLog()
{
	m_pCppLogs = new CppLogs::CppLogsW("F:/test_field/test_cpplogs/231216_testapp.log");
	m_pCppLogs->create_log_file("2023-12-16 22:03:00");
}

ExampleWriteLog::~ExampleWriteLog()
{
}
