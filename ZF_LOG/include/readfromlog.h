#pragma once
#ifndef _READFROMLOG_H_
#define _READFROMLOG_H_
#define MAX_PARAM_NUM 10			//所有使用日志模块的接口中， 最大可能的参数数量
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
		int randnum;
		string param_num;
		string param[MAX_PARAM_NUM];
	};
	class ReadLog
	{
	public:
		ReadLog();
		void read_log();
		char file_name[_MAX_PATH];
		static char* memory_src;
	};
	void read_init();
	char* read_memory(const ReadType& rtp, int& size);
	void read_uninit();
	ReadType read_next();
}
#endif