
#pragma once

#include <iostream>
#include "base.h"

namespace CppLogs
{
	class CPPLOGS_API CompareFile
	{
	public: 
		CompareFile(const std::string& left_file_pathname, const std::string& right_file_pathname) : 
			_left_file_pathname(left_file_pathname), _right_file_pathname(right_file_pathname)
		{}
		~CompareFile()
		{}

	private:
		CPPLOGS_DISABLE4251(const std::string _left_file_pathname);
		CPPLOGS_DISABLE4251(const std::string _right_file_pathname);
	};
}