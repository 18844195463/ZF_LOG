
#ifndef _READFROMLOG_H_
#define _READFROMLOG_H_
#include <iostream>
#include <boost/any.hpp>
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
		string line;
		string debug_info;
		string func_name;
		std::vector<boost::any> param;
		string buffer;
		string size;
		string filename;
	};
	class ReadLog
	{
	public:
		ReadLog();
		void read_log();
		char file_name[_MAX_PATH];
		static char* memory_src;
	};
	bool read_init();
	char* read_memory(const ReadType& rtp, int& size);
	void read_uninit();
	ReadType read_next();
}
#endif