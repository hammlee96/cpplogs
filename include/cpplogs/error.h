#include "base.h"

#pragma once
namespace CppLogs {
	class CPPLOGS_API Error
	{
	public:
		enum EnErrorCode {
			ErrorCode_None,
			ErrorCode_OpenFileFailed,
			ErrorCode_CreateItemFailed
		};
	};
}