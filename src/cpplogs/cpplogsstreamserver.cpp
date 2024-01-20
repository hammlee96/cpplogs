#include "cpplogs/cpplogsstreamserver.h"
#include "cpplogs/base.h"

namespace CppLogs {
	CppLogsStreamServer::CppLogsStreamServer()
	{
	}

	CppLogsStreamServer::~CppLogsStreamServer()
	{
	}

	grpc::Status CppLogsStreamServer::trans_data(grpc::ServerContext* context, const CppLogsExchangeData* request, CppLogsExchangeData* response)
	{
		CPPLOGS_DEBUG<<request->test();
		return grpc::Status::OK;
	}
}
