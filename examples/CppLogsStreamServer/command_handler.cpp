#include "command_handler.h"

CommandHandler::CommandHandler()
{
	m_spCppLogsMessage = std::make_shared<CppLogs::CppLogsMessage>();
	m_spCppLogsMessageResponse = std::make_shared<CppLogs::CppLogsMessage>();
	m_strAccountName = "";
}

CommandHandler::~CommandHandler()
{
}

std::string CommandHandler::ExecCommand(const std::string& data, std::string& response)
{
	bool ret = true;
	std::string str_command = "";
	m_spCppLogsMessageResponse.get()->Clear();
	m_spCppLogsMessage.get()->Parse(data);
	m_spCppLogsMessage.get()->Get(CPPLOGS_STR_COMMOND, str_command);
	m_spCppLogsMessageResponse.get()->Add(CPPLOGS_STR_COMMOND, str_command);
	if (str_command == CPPLOGS_STR_SET_ACCOUNT_NAME) {
		m_spCppLogsMessageResponse.get()->Add(CPPLOGS_STR_PARAM, "ok");
		m_spCppLogsMessage.get()->Get(CPPLOGS_STR_ACCOUNT_NAME, m_strAccountName);
	}
	else if (str_command == CPPLOGS_STR_SET_LOGDATA) {
		m_spCppLogsMessageResponse.get()->Add(CPPLOGS_STR_PARAM, "ok");
	}
	else {
		m_spCppLogsMessageResponse.get()->Add(CPPLOGS_STR_PARAM, "failed");
	}
	m_spCppLogsMessageResponse.get()->ToString(response);
	return str_command;
}
