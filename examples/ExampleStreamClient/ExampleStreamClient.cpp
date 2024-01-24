#include "ExampleStreamClient.h"

int main()
{
	ExampleStreamClient client;
}

ExampleStreamClient::ExampleStreamClient()
{
	CppLogs::SocketTcp *pSocketTcp = new CppLogs::SocketTcp(CppLogs::SocketTcp::CppLogsSocketType_Server, "127.0.0.1");
}

ExampleStreamClient::~ExampleStreamClient()
{
}
