#include "ExampleStreamClient.h"

int main()
{
	ExampleStreamClient client;
}

ExampleStreamClient::ExampleStreamClient()
{
	CppLogs::CppLogsStreamClient* pCppLogsStreamClient = new CppLogs::CppLogsStreamClient();
	CppLogs::Error::EnCppLogsNetError ret = CppLogs::Error::EnCppLogsNetError_None;
	ret = pCppLogsStreamClient->init();
	if (ret) {
		CPPLOGS_ERROR << ret;
	}
	pCppLogsStreamClient->send_file_info("c:/new/aap.cpplog");
}

ExampleStreamClient::~ExampleStreamClient()
{
}
