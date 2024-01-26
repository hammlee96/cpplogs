#include "ExamplePackMessage.h"
#include <string>

int main(char argc, char* argv[])
{
	ExamplePackMessage epm;
	return 0;
}

ExamplePackMessage::ExamplePackMessage()
{
	CppLogs::CppLogsMessage cm;
	std::string value;

	bool ret = cm.CommandSetFileInfo("C:/user/cpplogs_test.cpplog", value);
	CPPLOGS_DEBUG << value;
}

ExamplePackMessage::~ExamplePackMessage()
{
}
