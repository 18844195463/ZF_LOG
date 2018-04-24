#include "loginfo.h"
#include <iostream>
namespace ZF_LOG{
	int allrand = 1;
	time tm;
}
using namespace std;
void get_time(string& s_tm)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	ZF_LOG::tm.month = st.wMonth;
	ZF_LOG::tm.day = st.wDay;
	ZF_LOG::tm.hour = st.wHour;
	ZF_LOG::tm.minute = st.wMinute;
	ZF_LOG::tm.second = st.wSecond;
	ZF_LOG::tm.millisecond = st.wMilliseconds;
	s_tm.push_back('[');
	int temp = ZF_LOG::tm.month;
	s_tm += to_string(temp);
	s_tm.push_back('-');

	temp = ZF_LOG::tm.day;
	s_tm += to_string(temp);
	s_tm.push_back(' ');

	temp = ZF_LOG::tm.hour;
	s_tm += to_string(temp);
	s_tm.push_back(':');

	temp = ZF_LOG::tm.minute;
	s_tm += to_string(temp);
	s_tm.push_back(':');

	temp = ZF_LOG::tm.second;
	s_tm += to_string(temp);
	s_tm.push_back('.');

	temp = ZF_LOG::tm.millisecond;
	s_tm += to_string(temp);
	s_tm.push_back(']');
}
void get_rand(string& s_rand)
{
	int help = ZF_LOG::allrand;
	s_rand += to_string(help);
	ZF_LOG::allrand++;
}
void union_string(int line, const char* file, string& str)
{
	if (!str.empty())
		str.clear();
	get_time(str);
	while (str.size() < 23)
		str.push_back(' ');
	string temp = to_string(line);
	temp.push_back(']');
	while (temp.size() < 7)
	{
		temp.push_back(' ');
	}
	str += "[line:";
	str += temp;
	temp.clear();
	temp = string(file);
	while (temp.size() < 23)
		temp.push_back(' ');
	str += temp;
	//get_rand(str);
	//str += "    ";
}