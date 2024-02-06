/*
* function		: error or warning code define
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2023.12.16
*
* change author	: hammlee
* change date	: 2023.12.16
* change log	: init
*/
#pragma once

#include "cpplogs/basetools/base.h"

namespace CppLogs {
	class CPPLOGS_API Error
	{
	public:
		enum EnErrorCode {
			ErrorCode_None = 0,
			ErrorCode_LogFileExist,
			ErrorCode_OpenFileFailed,
			ErrorCode_CreateItemFailed,
			ErrorCode_FindItemFailed,
			ErrorCode_HeaderDamage,
			ErrorCode_LevelNotMatch
		};
		enum EnCppLogsNetError {
			EnCppLogsNetError_None,
			EnCppLogsNetError_InitFailed,
			EnCppLogsNetError_CreateListenFailed,
			EnCppLogsNetError_DisconnectFailed,
			EnCppLogsNetError_GetAddrInfoFailed,
			EnCppLogsNetError_SetSocketFailed,
			EnCppLogsNetError_ConnectFailed,
			EnCppLogsNetError_SendFailed,
			EnCppLogsNetError_RecvFailed,
			EnCppLogsNetError_BindFailed,
			EnCppLogsNetError_ListenFailed,
			EnCppLogsNetError_AcceptFailed,
			EnCppLogsNetError_ClientSizeNull
		};
	};
}