#include "CppLogsStreamServer.h"

#define DEF_THREAD_NUM		1

int main()
{
	CppLogsStreamServer server(9605);
	server.init();
	while (true);
	return 0;
}

CppLogsStreamServer::CppLogsStreamServer(const int& port)
{
	m_spCThreadBase = std::make_shared<CThreadBase>();
	//m_spNetForward = std::make_shared<CppLogs::CppLogsStreamClient>("192.168.30.61");
	m_spNetServer = std::make_shared<CppLogs::NetServer>(port);
	CppLogs::Error::EnCppLogsNetError ec = m_spNetServer->init();
	//ec = m_spNetForward.get()->init();
	//if (ec) {
	//	CPPLOGS_ERROR << ec;
	//}
	m_spCThreadPool = std::make_shared<CThreadPool>();
	m_spCThreadPool.get()->thread_pool_create(DEF_THREAD_NUM);
}

CppLogsStreamServer::~CppLogsStreamServer()
{
}

void CppLogsStreamServer::init()
{
	m_spCThreadBase.get()->force_create_thread(std::mem_fn(&CppLogsStreamServer::manager_thread), this);
}

CppLogs::Error::EnCppLogsNetError CppLogsStreamServer::recv(char* data, int& size)
{
	return m_spNetServer.get()->recv(data, size);
}

void CppLogsStreamServer::manager_thread()
{
	while (true) {
		CppLogs::Error::EnCppLogsNetError ec = m_spNetServer.get()->accept();
		if (ec) {
			CPPLOGS_ERROR << ec;
		}
		StThreadPoolUse *st_ThreadPoolUse = new StThreadPoolUse;
		st_ThreadPoolUse->pCppLogsStreamServer = this;
		st_ThreadPoolUse->st_CppLogsNetAddrInfo = m_spNetServer.get()->\
			get_connect_info().at(m_spNetServer.get()->get_connect_info().size() - 1);
		CPPLOGS_DEBUG << m_spNetServer.get()->get_connect_info().size();
		m_spCThreadPool.get()->thread_pool_add((Function)net_process_thread, (void*)st_ThreadPoolUse);
	}
}

void CppLogsStreamServer::net_process_thread(StThreadPoolUse* pst_ThreadPoolUse)
{
	int size = 0;
	char data[CPPLOGS_NET_SIZE];
	do {
		memset(data, 0, CPPLOGS_NET_SIZE);
		size = pst_ThreadPoolUse->pCppLogsStreamServer->recv(data, size);
		CPPLOGS_DEBUG <<
	"[" << pst_ThreadPoolUse->st_CppLogsNetAddrInfo.str_ip.c_str()<<":" << pst_ThreadPoolUse->st_CppLogsNetAddrInfo.port<<"]"<<
			":"<< data;
	} while (size > 0);
	//pst_ThreadPoolUse->pCppLogsStreamServer->m_spNetForward.get()->send_string(data);
	CPPLOGS_WARNING << "[" << pst_ThreadPoolUse->st_CppLogsNetAddrInfo.str_ip << ":" << pst_ThreadPoolUse->st_CppLogsNetAddrInfo.port << "] " << "exit";
	delete pst_ThreadPoolUse;
	pst_ThreadPoolUse = nullptr;
}
