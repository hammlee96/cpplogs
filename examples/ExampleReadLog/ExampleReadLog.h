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

#include "cpplogsr.h"
#include "base.h"

class ExampleReadLog
{
public:
	ExampleReadLog(const std::string& filepath);
	~ExampleReadLog();

private:
	CppLogs::CppLogsR *m_pCppLogs;
};