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

#include "cpplogs/base.h"
#include "cpplogs/fileformat.h"

namespace CppLogs {
	class CPPLOGS_API CppLogsR : public FileFormat
	{
	public:
		CppLogsR(const std::string& filename) : FileFormat(filename)
		{}
		~CppLogsR()
		{}

		/*
		* @brief get log header information
		* @param st_CppLogsItem : header information
		* @return error code
		*/
		Error::EnErrorCode get_item_type(DataFormat::StCppLogsHeader& st_CppLogsItem)
		{
			if (!existfile()) {
				return Error::ErrorCode_OpenFileFailed;
			}
			return unformat_file_header(st_CppLogsItem);
		}

		/*
		* @brief get log item data
		* @param st_CppLogsItemVector : get item info
		* @return error code
		*/
		Error::EnErrorCode get_items(std::vector<DataFormat::StCppLogsItem>& st_CppLogsItemVector)
		{
			if (!existfile()) {
				return Error::ErrorCode_OpenFileFailed;
			}
			return unformat_file_data(st_CppLogsItemVector);
		}
	};
}