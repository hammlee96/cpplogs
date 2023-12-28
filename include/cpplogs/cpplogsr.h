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
	class CPPLOGS_API CppLogsR : public FileFormat
	{
	public:
		CppLogsR(const std::string& filename) : FileFormat(filename)
		{}
		~CppLogsR()
		{}

		Error::EnErrorCode get_item_type(FileFormat::StCppLogsHeader& st_CppLogsItem)
		{
			if (!existfile()) {
				return Error::ErrorCode_OpenFileFailed;
			}
			return st_CppLogsItem = unformat_header();
		}

		Error::EnErrorCode get_items(std::vector<FileFormat::StCppLogsItem>& st_CppLogsItemVector)
		{
			if (!existfile()) {
				return Error::ErrorCode_OpenFileFailed;
			}
			return unformat_data(st_CppLogsItemVector);
		}
	};
}