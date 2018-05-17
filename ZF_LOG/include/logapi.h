#pragma once
#ifndef LOGAPI_H
#define LOGAPI_H

#include <iostream>
#include <boost/any.hpp>
#include <string>
#include "readfromlog.h"
using namespace std;
namespace ZF_LOG
{
	bool log_init(string file_name);
	bool is_logfile_open();
	bool write_to_file(char* src, uint32_t buflen);
	bool write_to_file_test(char* src, uint32_t buflen, const string& dst_plate);
	void file_output_close(void);
	extern FILE * g_log_file;
	extern char log_file_name[_MAX_FNAME];
	extern char zlog_path[_MAX_DIR];
}

#endif