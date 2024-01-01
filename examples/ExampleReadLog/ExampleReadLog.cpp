#include"ExampleReadLog.h"

int main()
{
	ExampleReadLog r;
	return 0;
}

ExampleReadLog::ExampleReadLog()
{
#if defined(CPPLOGS_SYSTEM_WINDOWS)
	//m_pCppLogs = new CppLogs::CppLogsR("");
#else
	//m_pCppLogs = new CppLogs::CppLogsR("");
#endif
}

ExampleReadLog::~ExampleReadLog()
{
}
