#pragma once
#ifndef _READFROMLOG_H_
#define _READFROMLOG_H_
#include <iostream>
#include <logapi.h>
#include <string>
#include <vector>
using namespace std;
namespace ZF_LOG
{
	struct ReadType
	{
		string month;
		string day;
		string hour;
		string minute;
		string second;
		string millonsec;
		string process;
		string thread;
		char debug_info;
		string func_name;
		string func_file;
		string line;
		string param_num;
		string param[10];
	};
	class ReadLog
	{
	public:
		ReadLog();
		void read_log();
		void read_all(vector <ReadType>& type);
	private:
		FILE *log_file;
		char file_name[100];
	public:
		static unsigned char* memory_src;
	};
	void read_init();
	unsigned char* read_memory(const ReadType& rtp, const char* dst_plate, int& size);
	void read_uninit();
	ReadType& read_next();
}
#endif