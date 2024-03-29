#include "CppLogsWriteLog.h"
#include "cpplogs/basetools/base.h"
#include "cpplogs/basetools/toolbox.h"
#include <filesystem>

int main()
{
	CppLogsWriteLog w;
	return 0;
}

CppLogsWriteLog::CppLogsWriteLog()
{
	CppLogs::ToolBox::StCppLogsDateTime st_CppLogsDateTime = CppLogs::ToolBox::gettime();
#if defined(CPPLOGS_SYSTEM_WINDOWS)
#define LOGSPATH		"D:/test_field/test_cpplogs"
#else
#define LOGSPATH		"/root/test_field/cpplogs"
#endif
	std::filesystem::create_directories(LOGSPATH);
	std::string logPathName = CppLogs::ToolBox::format("%s/%d%02d%02d_1.0.0", \
		LOGSPATH, st_CppLogsDateTime.uiYear, st_CppLogsDateTime.uiMonth, st_CppLogsDateTime.uiDay);
	m_pCppLogs = new CppLogs::CppLogsW(logPathName);

	m_pCppLogs->set_item_type({"", "infomation", "warning", "error", CppLogs::DataFormat::CppLogsLevel_High, true});
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

CppLogsWriteLog::~CppLogsWriteLog()
{
}
