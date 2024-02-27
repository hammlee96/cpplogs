#include "CppLogsStreamClient.h"

int main()
{
	CppLogsStreamClient client;
	return 0;
}

CppLogsStreamClient::CppLogsStreamClient()
{
	CppLogs::CppLogsStreamClient* pCppLogsStreamClient = new CppLogs::CppLogsStreamClient("192.168.30.58");
	CppLogs::Error::EnCppLogsNetError ret = CppLogs::Error::EnCppLogsNetError_None;

	CppLogs::ToolBox::StCppLogsDateTime st_CppLogsDateTime = CppLogs::ToolBox::gettime();
#if defined(CPPLOGS_SYSTEM_WINDOWS)
#define LOGSPATH		"F:/test_field/test_cpplogs"
#else
#define LOGSPATH		"/root/test_field/cpplogs"
#endif
	std::string logPathName = CppLogs::ToolBox::format("%s/%d%02d%02d_1.0.0", \
		LOGSPATH, st_CppLogsDateTime.uiYear, st_CppLogsDateTime.uiMonth, st_CppLogsDateTime.uiDay);

	ret = pCppLogsStreamClient->init();
	if (ret) {
		CPPLOGS_ERROR << ret;
	}

	pCppLogsStreamClient->send_file_info(logPathName);
	//if (ret) {
	//	CPPLOGS_ERROR << ret;
	//}

	pCppLogsStreamClient->send_log_type({"", "infomation", "warning", "error", CppLogs::DataFormat::CppLogsLevel_High, true});
	//if (ret) {
	//	CPPLOGS_ERROR << ret;
	//}

	ret = pCppLogsStreamClient->set_account_name("client_test");
	if (ret) {
		CPPLOGS_ERROR << ret;
	}

	CppLogs::ToolBox::msleep(1000);

	ret = pCppLogsStreamClient->send_log_data_info("secondinfo", "this is a information");
	if (ret) {
		CPPLOGS_ERROR << ret;
	}

	CppLogs::ToolBox::msleep(1000);

	ret = pCppLogsStreamClient->send_log_data_warn("secondwarn", "this is a warning");
	if (ret) {
		CPPLOGS_ERROR << ret;
	}

	CppLogs::ToolBox::msleep(1000);

	ret = pCppLogsStreamClient->send_log_data_error("seconderror", "this is a error");
	if (ret) {
		CPPLOGS_ERROR << ret;
	}

	size_t size = 0;
	char data[CPPLOGS_NET_SIZE] = { 0 };
	do {
		memset(data, 0, CPPLOGS_NET_SIZE);
		pCppLogsStreamClient->recv(data, size);
		CPPLOGS_DEBUG << data;
	} while (size > 0);
}

CppLogsStreamClient::~CppLogsStreamClient()
{
}
