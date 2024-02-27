/*
* function		: server command handler
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.02.23
*
* change author	: hammlee
* change date	: 2024.02.23
* change log	: init
*/

#include <iostream>
#include <memory>
#include "cpplogs/cpplogsmessage.h"

class CommandHandler
{
private:
	std::shared_ptr<CppLogs::CppLogsMessage> m_spCppLogsMessage;
	std::shared_ptr<CppLogs::CppLogsMessage> m_spCppLogsMessageResponse;
	std::string m_strAccountName;

public:
	CommandHandler();
	~CommandHandler();

	std::string ExecCommand(const std::string& data, std::string& response);

	inline std::string get_account_name() const
	{
		return m_strAccountName;
	}
};