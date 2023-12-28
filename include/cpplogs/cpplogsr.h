/*
* function		: read logs file
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2023.12.28
*
* change author	: hammlee
* change date	: 2023.12.28
* change log	: init
*/

#include "base.h"
#include "fileformat.h"

namespace CppLogs {
	class CPPLOGS_API CppLogsR {
		CppLogsR(const std::string& filename) : public FileFormat(filename)
		{}
		~CppLogsR()
		{}
	};
}