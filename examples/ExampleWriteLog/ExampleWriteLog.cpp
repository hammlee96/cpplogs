#include "ExampleWriteLog.h"
#include "basetools/base.h"
#include "basetools/toolbox.h"

int main()
{
	ExampleWriteLog w;
	return 0;
}

ExampleWriteLog::ExampleWriteLog()
{
	CppLogs::ToolBox::StCppLogsDateTime st_CppLogsDateTime = CppLogs::ToolBox::gettime();
#if defined(CPPLOGS_SYSTEM_WINDOWS)
	std::string logPathName = CppLogs::ToolBox::format("F:/test_field/test_cpplogs/%d%d%d_1.0.0", \
		st_CppLogsDateTime.uiYear, st_CppLogsDateTime.uiMonth, st_CppLogsDateTime.uiDay);
	m_pCppLogs = new CppLogs::CppLogsW(logPathName);
#else
	std::string logPathName = CppLogs::ToolBox::format("/root/test_field/cpplogs/%d%d%d_1.0.0", \
		st_CppLogsDateTime.uiYear, st_CppLogsDateTime.uiMonth, st_CppLogsDateTime.uiDay);
	m_pCppLogs = new CppLogs::CppLogsW(logPathName);
#endif
	m_pCppLogs->set_item_type({"", "infomation", "warning", "error", CppLogs::FileFormat::CppLogsLevel_High, true});
	CppLogs::Error::EnErrorCode ec = m_pCppLogs->create_file("2023-12-16 22:03:00");
	if (ec) {
		CPPLOGS_ERROR << ec;
	}
	ec = m_pCppLogs->information("secondinfo", "this is a information");
	if (ec) {
		CPPLOGS_ERROR << ec;
	}
	ec = m_pCppLogs->warn("secondwarn", "this is a warning");
	if (ec) {
		CPPLOGS_ERROR << ec;
	}
	ec = m_pCppLogs->error("seconderror", "this is a error");
	if (ec) {
		CPPLOGS_ERROR << ec;
	}
}

ExampleWriteLog::~ExampleWriteLog()
{
}
