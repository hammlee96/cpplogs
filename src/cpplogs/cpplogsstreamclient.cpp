#include "cpplogs/cpplogsstreamclient.h"
#include "cpplogs_exchangedata.grpc.pb.h"
#include "cpplogs_exchangedata.pb.h"
#include "grpcpp/security/credentials.h"

namespace CppLogs {
	CppLogsStreamClient::CppLogsStreamClient()
	{
		grpc::ChannelArguments channel_args;
		channel_args.SetInt("grpc.max_receive_message_length", 1024 * 1024 * 60);
		std::unique_ptr<CppLogs::CppLogsGreeter::Stub> _stub = \
			CppLogs::CppLogsGreeter::NewStub(grpc::CreateCustomChannel("127.0.0.1:1289", grpc::InsecureChannelCredentials(), channel_args));
		grpc::ClientContext context;
		CppLogs::CppLogsExchangeData cppLogsExchangeDataRequest;
		CppLogs::CppLogsExchangeData cppLogsExchangeDataResponse;
		cppLogsExchangeDataRequest.set_test("hello world!");
		_stub.get()->trans_data(&context, cppLogsExchangeDataRequest, &cppLogsExchangeDataResponse);
	}
	CppLogsStreamClient::~CppLogsStreamClient()
	{
	}
}