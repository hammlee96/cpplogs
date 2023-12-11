/*
* function		: logs library entry
* author		: hammlee
* e-mail		: hammlee@163.com
* create date	: 2023.12.10
* 
* change author	: hammlee
* change date	: 2023.12.10
* change log	: init
*/

#pragma once

#include <iostream>
#include "base.h"
#include "error.h"

namespace CppLogs {

	using PrivateString = struct {
		std::string data;
	};

	class CPPLOGS_API CppLogs
	{
	public:
		CppLogs(const std::string& filename) :
			_filename(PrivateString{ filename }) {}
		~CppLogs();

		Error::EnErrorCode create_log_file();
		Error::EnErrorCode information(const std::string& data);
		Error::EnErrorCode warning(const std::string& data);
		Error::EnErrorCode error(const std::string& data);

	private:
		PrivateString _filename;
	};
}
