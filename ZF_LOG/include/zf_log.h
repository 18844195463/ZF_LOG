
#ifndef ZFLOG_H
#define ZFLOG_H

#include <iostream>
#include <boost/any.hpp>
#include <string>
#include "readfromlog.h"
using namespace std;
#define zf_write_log( ... ) ZF_LOG::writelog( __LINE__, __FUNCTION__, __VA_ARGS__)
namespace ZF_LOG
{
	enum Type { Info, Function, Input, Output, Debug, Error, Warn, Buffer };
	void writelog(int line, const char* file, Type type, const char* cc);
	void writelog(int, const char*, Type type, vector<boost::any>&& some_values);
	void writelog(int line, const char* file, Type type, void* buf, uint32_t size);
}
void zf_log_init(char* file_name);
void zf_write_to_file(char* src, uint32_t buflen);

void zf_write_to_file_test(char* src, uint32_t buflen, const char* dst_plate);
void zf_read_init();
char* zf_read_memory(const ZF_LOG::ReadType& rtp, int& size);
void zf_read_uninit();
void zf_log_uninit();
ZF_LOG::ReadType zf_read_next();

#endif