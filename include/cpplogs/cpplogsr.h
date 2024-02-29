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

#include "cpplogs/basetools/base.h"
#include "cpplogs/fileformat.h"

namespace CppLogs {
	class CPPLOGS_API CppLogsR : public CppLogs::FileFormat
	{
	public:
		CppLogsR(const std::string& filename) : CppLogs::FileFormat(filename)
		{}
		~CppLogsR()
		{}

		/*
		* @brief get log header information
		* @param st_CppLogsItem : header information
		* @return error code
		*/
		CppLogs::Error::EnErrorCode get_item_type(CppLogs::DataFormat::StCppLogsHeader& st_CppLogsItem)
		{
			if (!existfile()) {
				return CppLogs::Error::ErrorCode_OpenFileFailed;
			}
			return unformat_file_header(st_CppLogsItem);
		}

		/*
		* @brief get log item data
		* @param st_CppLogsItemVector : get item info
		* @return error code
		*/
		CppLogs::Error::EnErrorCode get_items(std::vector<CppLogs::DataFormat::StCppLogsItem>& st_CppLogsItemVector)
		{
			if (!existfile()) {
				return CppLogs::Error::ErrorCode_OpenFileFailed;
			}
			return unformat_file_data(st_CppLogsItemVector);
		}
	};
}