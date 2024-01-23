#include "ExampleStreamClient.h"

int main()
{
	ExampleStreamClient client;
}

ExampleStreamClient::ExampleStreamClient()
{
	CppLogs::SocketTcp *pSocketTcp = new CppLogs::SocketTcp("192.168.30.58");
}

ExampleStreamClient::~ExampleStreamClient()
{
}
