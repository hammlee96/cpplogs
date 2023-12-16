#include <iostream>
#include <fstream>
#include "error.h"
#include "dataformat.h"

namespace CppLogs {
	class FileFormat : public DataFormat {
	public:
		enum EnCppLogsLevel {
			CppLogsLevel_High = 1,
			CppLogsLevel_Middle,
			CppLogsLevel_Low
		};
		struct StCppLogsHeader {
			std::string keyInfo;
			std::string keyWarn;
			std::string keyError;
			EnCppLogsLevel en_CppLogsLevel;
			bool		stampRecord;
			bool		fileLineRecord;
		};

	public:
		FileFormat(const std::string& filename) :
			_filename(filename) {}
		~FileFormat();

		bool existfile();
		FileFormat::StCppLogsHeader analysis_header();

		Error::EnErrorCode set_log_header(const StCppLogsHeader& st_CppLogsHeader);
		Error::EnErrorCode create_log_file(const StCppLogsHeader& st_CppLogsHeader);
		Error::EnErrorCode writefile(const std::string& key, const std::string secondKey, const std::string& data);

	private:
		std::string _filename;
	};
}