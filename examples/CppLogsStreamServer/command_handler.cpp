#include "command_handler.h"

CommandHandler::CommandHandler()
{
	m_spCppLogsMessage = std::make_shared<CppLogs::CppLogsMessage>();
	m_spCppLogsMessageResponse = std::make_shared<CppLogs::CppLogsMessage>();
}

CommandHandler::~CommandHandler()
{
}

bool CommandHandler::ExecCommand(const std::string& data, std::string& response)
{
	std::string std_command = "";
	m_spCppLogsMessageResponse.get()->Clear();
	m_spCppLogsMessage.get()->Parse(data);
	m_spCppLogsMessage.get()->Get(CPPLOGS_STR_COMMOND, std_command);
	m_spCppLogsMessageResponse.get()->Add(CPPLOGS_STR_COMMOND, std_command);
	if (std_command == CPPLOGS_STR_SET_ACCOUNT_NAME) {
		m_spCppLogsMessageResponse.get()->Add(CPPLOGS_STR_PARAM, "ok");
		m_spCppLogsMessageResponse.get()->ToString(response);
		return true;
	}
	else if (std_command == CPPLOGS_STR_SET_LOGDATA) {
		m_spCppLogsMessageResponse.get()->Add(CPPLOGS_STR_PARAM, "ok");
		m_spCppLogsMessageResponse.get()->ToString(response);
		return true;
	}
	m_spCppLogsMessageResponse.get()->Add(CPPLOGS_STR_PARAM, "failed");
	m_spCppLogsMessageResponse.get()->ToString(response);
	return false;
}

bool CommandHandler::set_forward_name(const std::string& name)
{
	return false;
}
