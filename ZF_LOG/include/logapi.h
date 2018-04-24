#pragma once
#ifndef LOGAPI_H
#define LOGAPI_H

#include <iostream>
#include <boost/any.hpp>
#include <string>
using namespace std;
namespace ZF_LOG
{
	enum Type { Info, Function, Input, Output, Debug, Error, Warn, Buffer };
	void log_init(char* file_name);
	void setfmt(int count, ...);
	//void writelog(int count, ...);
	//void writelog(Type type, string str);
	void writelog(int line, const char* file, Type type, const char* cc);
	void writelog(int, const char*, Type type, vector<boost::any>&& some_values);
	void writelog(int line, const char* file, Type type, void* buf, uint32_t size);
	void write_to_file(char* src, uint32_t buflen);
	void write_to_file_test(char* src, uint32_t buflen, const char* dst_plate);
	void file_output_close(void);
	extern char state[];
	extern FILE * g_log_file;
	extern char log_file_name[100];
	extern char zlog_path[100];
}

#endif