/*
* function		: use net receive logs data
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.02.05
*
* change author	: hammlee
* change date	: 2024.02.05
* change log	: init
*/

#include "cpplogs/basetools/toolbox.h"
#include "cpplogs/basetools/net/netserver.h"
#include "cpplogs/cpplogsstreamclient.h"
#include "cthreadpool.h"
#include "command_handler.h"
#include <memory>

class CppLogsStreamServer
{
private:
	std::shared_ptr<CppLogs::NetServer> m_spNetServer;
	//std::shared_ptr<CppLogs::CppLogsStreamClient> m_spNetForward;
	std::shared_ptr<CThreadPool> m_spCThreadPool;
	std::shared_ptr<CThreadBase> m_spCThreadBase;
	std::shared_ptr<CommandHandler> m_spCommandHandler;
	struct StThreadPoolUse
	{
		CppLogsStreamServer* pCppLogsStreamServer;
		CppLogs::ServerBase::StCppLogsNetAddrInfo st_CppLogsNetAddrInfo;
	};

public:
	CppLogsStreamServer(const int& port = 9605);
	~CppLogsStreamServer();

	void init();
	CppLogs::Error::EnCppLogsNetError recv(char* data, int& size);
	void manager_thread();
	static void net_process_thread(StThreadPoolUse* pst_ThreadPoolUse);
};