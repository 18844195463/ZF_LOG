#pragma once
#ifndef LOGAPI_H
#define LOGAPI_H

#include <iostream>
#include "zf_log.h"
#define ZF_LOGWI(...) ZF_LOGI(ZF_LOG::state, __VA_ARGS__)
	
namespace ZF_LOG
{
	void log_init(char* file_name);
	void setfmt(int count, ...);
	void write_to_file(char* src, long buflen, int filerand, const char* dst_plate);
	void file_output_close(void);
	extern char state[];
	extern FILE * g_log_file;
	extern char log_file_name[100];
	extern char zlog_path[100];
}

#endif