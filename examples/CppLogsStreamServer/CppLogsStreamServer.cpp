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
	m_spCommandHandler = std::make_shared<CommandHandler>();
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
		CppLogs::ServerBase::StNetDataInfo* st_NetDataInfo = nullptr;
		CppLogs::Error::EnCppLogsNetError ec = m_spNetServer.get()->accept(&st_NetDataInfo);

		for (int i = 0; i < st_NetDataInfo[0].ready_num; i++) {
			switch (st_NetDataInfo[i].net_event_type) {
			case CppLogs::ServerBase::NetEventType_Conn:
				CPPLOGS_DEBUG << "[" << st_NetDataInfo[i].st_net_addr_info.addr << ":" \
					<< st_NetDataInfo[i].st_net_addr_info.port << "] - " << "connect" << std::endl;
				//CPPLOGS_DEBUG << m_spNetServer.get()->send(st_NetDataInfo[i].st_net_addr_info.fd, "connect succeed", 14) << std::endl;
				break;
			case CppLogs::ServerBase::NetEventType_DisConn:
				CPPLOGS_DEBUG << "[" << st_NetDataInfo[i].st_net_addr_info.addr << ":" \
					<< st_NetDataInfo[i].st_net_addr_info.port << "] - " << "disconnect" << std::endl;
				break;
			case CppLogs::ServerBase::NetEventType_Recv:
				CPPLOGS_DEBUG << "[" << st_NetDataInfo[i].st_net_addr_info.addr << ":" \
					<< st_NetDataInfo[i].st_net_addr_info.port << "] - \n" << st_NetDataInfo[i].data << std::endl;
				//CPPLOGS_DEBUG << m_spNetServer.get()->send(st_NetDataInfo[i].st_net_addr_info.fd, "recv succeed", 12) << std::endl;
				//m_spNetServer.get()->send("client_recv", st_NetDataInfo[i].data.c_str(), st_NetDataInfo[i].data.size());
				std::string response;
				m_spCommandHandler.get()->ExecCommand(st_NetDataInfo[i].data.c_str(), response);

				CPPLOGS_DEBUG << m_spNetServer.get()->send(st_NetDataInfo[i].st_net_addr_info.fd, response.c_str(), response.size()) << std::endl;
				break;
			}
		}
		m_spNetServer.get()->free_struct(st_NetDataInfo);
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
	"[" << pst_ThreadPoolUse->st_CppLogsNetAddrInfo.addr<<":" << pst_ThreadPoolUse->st_CppLogsNetAddrInfo.port<<"]"<<
			":"<< data;
	} while (size > 0);
	//pst_ThreadPoolUse->pCppLogsStreamServer->m_spNetForward.get()->send_string(data);
	CPPLOGS_WARNING << "[" << pst_ThreadPoolUse->st_CppLogsNetAddrInfo.addr << ":" << pst_ThreadPoolUse->st_CppLogsNetAddrInfo.port << "] " << "exit";
	delete pst_ThreadPoolUse;
	pst_ThreadPoolUse = nullptr;
}
