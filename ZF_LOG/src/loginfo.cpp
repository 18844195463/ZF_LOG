#include "loginfo.h"
#include <iostream>
namespace ZF_LOG{
	int allrand = 1;
	time tm;
}
void get_time(char* s_tm)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	ZF_LOG::tm.month = st.wMonth;
	ZF_LOG::tm.day = st.wDay;
	ZF_LOG::tm.hour = st.wHour;
	ZF_LOG::tm.minute = st.wMinute;
	ZF_LOG::tm.second = st.wSecond;
	ZF_LOG::tm.millisecond = st.wMilliseconds;
	char temp[10] = { 0 };
	char rest[10] = { 0 };
	int index = 0;
	int month = ZF_LOG::tm.month;
	while (month != 0)
	{
		temp[index++] = (char)(month % 10 + 48);
		month = month / 10;
	}
	strcat(s_tm, strrev(temp));
	strcpy(temp, rest);
	strcat(s_tm, "-");
	index = 0;
	int day = ZF_LOG::tm.day;
	while (day != 0)
	{
		temp[index++] = (char)(day % 10 + 48);
		day = day / 10;
	}
	strcat(s_tm, strrev(temp));
	strcpy(temp, rest);
	strcat(s_tm, " ");
	index = 0;
	int hour = ZF_LOG::tm.hour;
	while (hour != 0)
	{
		temp[index++] = (char)(hour % 10 + 48);
		hour = hour / 10;
	}
	strcat(s_tm, strrev(temp));
	strcpy(temp, rest);
	strcat(s_tm, ":");
	index = 0;
	int minute = ZF_LOG::tm.minute;
	while (minute != 0)
	{
		temp[index++] = (char)(minute % 10 + 48);
		minute = minute / 10;
	}
	strcat(s_tm, strrev(temp));
	strcpy(temp, rest);
	strcat(s_tm, ":");
	index = 0;
	int second = ZF_LOG::tm.second;
	while (second != 0)
	{
		temp[index++] = (char)(second % 10 + 48);
		second = second / 10;
	}
	strcat(s_tm, strrev(temp));
	strcpy(temp, rest);
	strcat(s_tm, ".");
	index = 0;
	int millisecon = ZF_LOG::tm.millisecond;
	while (millisecon != 0)
	{
		temp[index++] = (char)(millisecon % 10 + 48);
		millisecon = millisecon / 10;
	}
	strcat(s_tm, strrev(temp));
}
void get_pid(char* p_id)
{
	int pid = GetCurrentProcessId();
	int index = 0;
	while (pid != 0)
	{
		p_id[index++] = (char)(pid % 10 + 48);
		pid = pid / 10;
	}
	strrev(p_id);
}
char* get_loglevel(int p)
{
	return "I";
}
void get_rand(char* s_rand)
{
	int index = 0;
	while (ZF_LOG::allrand != 0)
	{
		s_rand[index++] = (char)(ZF_LOG::allrand % 10 + 48);
		ZF_LOG::allrand = ZF_LOG::allrand / 10;
	}
	strrev(s_rand);
	ZF_LOG::allrand++;
}
void union_string(char* p)
{
	if (p == NULL)
		return;
	char s_tm[100] = { 0 };
	char pid[20] = { 0 };
	char rand[9] = { 0 };
	get_time(s_tm);
	get_pid(pid);
	get_rand(rand);
	strcat(p, s_tm);
	strcat(p, " ");
	strcat(p, pid);
	strcat(p, " ");
	strcat(p, rand);
	strcat(p, " ");
	strcat(p, get_loglevel(1));
	strcat(p, " ");
	strcat(p, "main@main.cpp:44");
	strcat(p, " ");
}