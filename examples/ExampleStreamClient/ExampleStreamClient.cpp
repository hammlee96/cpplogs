#include "ExampleStreamClient.h"

int main()
{
	ExampleStreamClient client;
}

ExampleStreamClient::ExampleStreamClient()
{
	CppLogs::SocketTcp *pSocketTcp = new CppLogs::SocketTcp("127.0.0.1");
}

ExampleStreamClient::~ExampleStreamClient()
{
}
