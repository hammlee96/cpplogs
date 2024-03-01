# ⭐⭐⭐Sincerely invite all developers to jointly develop
# cpplogs - A cpp standard log library
## Contents
- [Functions](#functions)
- [Support Platform](#support-platform)
  - [Windows](#windows)
  - [Linux](#linux)
- [Build](#build)
- [Usage](#usage)
  - [Write log file to local](#write-log-file-to-local)
  - [Read log file from local](#read-log-file-from-local)
  - [Send log data to server](#send-log-data-to-server)
  - [Receive log data from remote](#receive-log-data-from-remote)
- [Third-party](#third-party)
## Functions
- [X] Create and read local log files
- [ ] Send and download local log files to the server
- [ ] Create and read remote log files
- [X] Send log data to the server (and forward it to the specified IP address, but you need to write server process by yourself, or use [server](#receive-log-data-from-remote) in example)
## Support Platform
- ### Windows
- ### Linux
## Build
- ### Options
	| option                                | function                                           |
	| ------------------------------------- | -------------------------------------------------- |
	| CPPLOGS_COMPILE_STATIC_OPTION         | If true, then use the static compile mode          |
	| CPPLOGS_COMPILE_EXAMPLE_OPTION        | If true, then compile with examples                |
## Usage
- ### Write log file to local
	To enable the function of writing local log files, you need include `cpplogsw.h`.
	Use the following code, will write log file to local file system</br>
	**Example:**
	```cpp
	#include "cpplogs/cpplogsw.h"
	#include "cpplogs/basetools/base.h"

	int main()
	{
		CppLogs::CppLogsW *pCppLogs = new CppLogs::CppLogsW("/home/log_files/test_log");
		pCppLogs->set_item_type({"", "infomation", "warning", "error", CppLogs::DataFormat::CppLogsLevel_High, true});
    		CppLogs::Error::EnErrorCode ec = pCppLogs->create_file("2024-02-01 15:34:30");
		if (ec) {
			CPPLOGS_ERROR << ec;
		}
		ec = pCppLogs->information("secondinfo", "this is a information");
		if (ec) {
			CPPLOGS_ERROR << ec;
			return ec;
		}
		ec = pCppLogs->warn("secondwarn", "this is a warning");
		if (ec) {
			CPPLOGS_ERROR << ec;
			return ec;
		}
		ec = pCppLogs->error("seconderror", "this is a error");
		if (ec) {
			CPPLOGS_ERROR << ec;
			return ec;
		}
		return 0;
	}
	```
- ### Read log file from local
	To enable the function of read local log files, you need include `cpplogsr.h`.
	Use the following code, will read log file from local file system</br>
	**Example:**
	```cpp
	#include "cpplogs/cpplogsr.h"
	#include "cpplogs/basetools/base.h"

	CppLogs::CppLogsR pCppLogs = new CppLogs::CppLogsR("/home/log_files/test_log");

	CppLogs::DataFormat::StCppLogsHeader st_CppLogsHeader;
	CppLogs::Error::EnErrorCode ec = pCppLogs->get_item_type(st_CppLogsHeader);
	if (ec) {
		CPPLOGS_ERROR << ec;
	}
	CPPLOGS_DEBUG << "create_time: " << st_CppLogsHeader.create_time << "\n" << \
		"level: " << st_CppLogsHeader.en_CppLogsLevel << "\n" << \
		"stamp_status: " << st_CppLogsHeader.stampRecord << "\n" << \
		"information key word: " << st_CppLogsHeader.keyInfo << "\n" << \
		"warning key word: " << st_CppLogsHeader.keyWarn << "\n" << \
		"error key word: " << st_CppLogsHeader.keyError;
	std::vector<CppLogs::DataFormat::StCppLogsItem> st_CppLogsItemVector;
	ec = pCppLogs->get_items(st_CppLogsItemVector);
	if (ec) {
		CPPLOGS_ERROR << ec;
	}
	for (auto it : st_CppLogsItemVector) {
		CPPLOGS_WARNING << "*************************beg************************";
		CPPLOGS_DEBUG << "key word: " << it.key << "\n" << \
			"second key word: " << it.secondKey << "\n" << \
			"time_stamp: " << it.timeStamp << "\n" << \
			"data: " << it.data;
		CPPLOGS_WARNING << "*************************end************************";
	}
	```
- ### Send log data to server
  	To enable the function of writing log files to server, you need include `cpplogsstreamclient.h`.
	Use the following code, will write log data to server file system</br>
	**Example:**
	```cpp
	#include "cpplogs/cpplogsstreamclient.h"
	#include "cpplogs/basetools/toolbox.h"

	CppLogs::CppLogsStreamClient* pCppLogsStreamClient = new CppLogs::CppLogsStreamClient("127.0.0.1", 9605);
	CppLogs::Error::EnCppLogsNetError ret = CppLogs::Error::EnCppLogsNetError_None;

	ret = pCppLogsStreamClient->init();
	if (ret) {
		CPPLOGS_ERROR << ret;
	}
	pCppLogsStreamClient->send_file_info("/home/log_files/test_log");

	pCppLogsStreamClient->send_log_type({"", "infomation", "warning", "error", CppLogs::DataFormat::CppLogsLevel_High, true});

	ret = pCppLogsStreamClient->set_account_name("client_test");
	if (ret) {
		CPPLOGS_ERROR << ret;
	}

	CppLogs::ToolBox::msleep(1000);

	ret = pCppLogsStreamClient->send_log_data_info("secondinfo", "this is a information");
	if (ret) {
		CPPLOGS_ERROR << ret;
	}

	CppLogs::ToolBox::msleep(1000);

	ret = pCppLogsStreamClient->send_log_data_warn("secondwarn", "this is a warning");
	if (ret) {
		CPPLOGS_ERROR << ret;
	}

	CppLogs::ToolBox::msleep(1000);

	ret = pCppLogsStreamClient->send_log_data_error("seconderror", "this is a error");
	if (ret) {
		CPPLOGS_ERROR << ret;
	}
	```
- ### Receive log data from remote
	This feature needs to support concurrency, receive addresses from various clients, 
	and then forward them to designated collection clients.</br>
	To use this feature, you can use the basic features written by examples/CppLogsStreamServer(**only support Linux**), 
	or you can implement server code with certain concurrency capabilities yourself.
## Third-party
Thanks for the third-party open-source library
- [cJSON](https://github.com/DaveGamble/cJSON)
