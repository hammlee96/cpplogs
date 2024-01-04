#include "ExampleWriteLog.h"
#include "base.h"
#include "toolbox.h"
#include <filesystem>

int main()
{
	ExampleWriteLog w;
	return 0;
}

ExampleWriteLog::ExampleWriteLog()
{
	CppLogs::ToolBox::StCppLogsDateTime st_CppLogsDateTime = CppLogs::ToolBox::gettime();
#if defined(CPPLOGS_SYSTEM_WINDOWS)
#define LOGSPATH		"F:/test_field/test_cpplogs"
	std::filesystem::create_directories(LOGSPATH);
	std::string logPathName = CppLogs::ToolBox::format("%s/%d%02d%02d_1.0.0", \
		LOGSPATH, st_CppLogsDateTime.uiYear, st_CppLogsDateTime.uiMonth, st_CppLogsDateTime.uiDay);
	m_pCppLogs = new CppLogs::CppLogsW(logPathName);
#else
#define LOGSPATH		"/root/test_field/cpplogs"
	std::filesystem::create_directories(LOGSPATH);
	std::string logPathName = CppLogs::ToolBox::format("%s/%d%d%d_1.0.0", \
		LOGSPATH, st_CppLogsDateTime.uiYear, st_CppLogsDateTime.uiMonth, st_CppLogsDateTime.uiDay);
	m_pCppLogs = new CppLogs::CppLogsW(logPathName);
#endif
	m_pCppLogs->set_item_type({"", "infomation", "warning", "error", CppLogs::FileFormat::CppLogsLevel_High, true});
	CppLogs::Error::EnErrorCode ec = m_pCppLogs->create_file(CppLogs::ToolBox::format("%d-%02d-%02d %02d:%02d:%02d", \
		st_CppLogsDateTime.uiYear, st_CppLogsDateTime.uiMonth, st_CppLogsDateTime.uiDay, \
		st_CppLogsDateTime.uiHour, st_CppLogsDateTime.uiMinute, st_CppLogsDateTime.uiSecond));
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
