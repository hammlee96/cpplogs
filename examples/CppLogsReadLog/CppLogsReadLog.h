/*
* function		: read logs
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2024.01.01
*
* change author	: hammlee
* change date	: 2024.01.01
* change log	: init
*/

#include "cpplogs/cpplogsr.h"
#include "cpplogs/basetools/base.h"

class CppLogsReadLog
{
public:
	CppLogsReadLog(const std::string& filepath);
	~CppLogsReadLog();

private:
	CppLogs::CppLogsR *m_pCppLogs;
};