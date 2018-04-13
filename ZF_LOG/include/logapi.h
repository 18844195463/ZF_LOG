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
	void write_to_file(char* src, size_t buflen, const char* filename);
	extern char state[];
}

#endif