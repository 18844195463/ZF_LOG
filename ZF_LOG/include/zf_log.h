
#ifndef ZFLOG_H
#define ZFLOG_H

#include <iostream>
#include <boost/any.hpp>
#include <string>
#include "readfromlog.h"
/*
 * @ param1 : ZF_LOG::Info, ZF_LOG::Debug ...
 * @ param2 : you can use a temp vector or a string or a void* buffer
 * @ param3 : if you use void* buffer in param2, then you must figure out a length using this param
*/
#define zf_write_log( ... ) ZF_LOG::writelog( __LINE__, __FUNCTION__, __VA_ARGS__)
namespace ZF_LOG
{
	enum Type { Info, Function, Input, Output, Debug, Error, Warn, Buffer };
	bool writelog(int line, const char* file, Type type, const string& cc);
	bool writelog(int, const char*, Type type, vector<boost::any>&& some_values);
	bool write_to_file(char * src, uint32_t buflen);
	bool write_to_file_test(char * src, uint32_t buflen, const string & dst_plate);
	bool writelog(int line, const char* file, Type type, void* buf, uint32_t size);
}
bool zf_log_init(string file_name);
bool zf_write_to_file(char* src, uint32_t buflen);

bool zf_write_to_file_test(char* src, uint32_t buflen, const string& dst_plate);
bool zf_read_init();
char* zf_read_memory(const ZF_LOG::ReadType& rtp, int& size);
void zf_read_uninit();
void zf_log_uninit();
// you must use method zf_read_uninit before zf_read_next
ZF_LOG::ReadType zf_read_next();

#endif