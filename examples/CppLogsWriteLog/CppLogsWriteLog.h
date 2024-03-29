/*
* function		: create and write logs
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2023.12.11
* 
* change author	: hammlee
* change date	: 2023.12.11
* change log	: init
*/

#include "cpplogs/cpplogsw.h"

class CppLogsWriteLog
{
public:
	CppLogsWriteLog();
	~CppLogsWriteLog();

private:
	CppLogs::CppLogsW* m_pCppLogs;
};