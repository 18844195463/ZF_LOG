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
	void log_init(char* file_name);

	void write_to_file(char* src, uint32_t buflen);
	void write_to_file_test(char* src, uint32_t buflen, const char* dst_plate);
	void file_output_close(void);
	extern FILE * g_log_file;
	extern char log_file_name[100];
	extern char zlog_path[100];
}

#endif