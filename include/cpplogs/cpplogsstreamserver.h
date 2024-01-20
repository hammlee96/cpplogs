/*
* function		: logs data send to server
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.01.08
*
* change author	: hammlee
* change date	: 2024.01.08
* change log	: init
*/

#pragma once

#include "cpplogs/base.h"
#include "grpc++/grpc++.h"
#include "cpplogs_exchangedata.grpc.pb.h"
//#include "grpcpp/security/credentials.h"

namespace CppLogs
{
	class CPPLOGS_API CppLogsStreamServer : public CppLogsGreeter::Service
	{
	public:
		// for fix compile error: C2280
		CppLogsStreamServer& operator=(const CppLogsStreamServer&) = delete;
		CppLogsStreamServer(const CppLogsStreamServer&) = delete;

		CppLogsStreamServer();
		~CppLogsStreamServer();

		grpc::Status trans_data(grpc::ServerContext* context, const CppLogsExchangeData* request, CppLogsExchangeData* response) override;
	};
}