#pragma once
#ifndef __LOGINFOH__
#define __LOGINFOH__
#include <windows.h>
#include "logapi.h"
#define MAX_STRING_SIZE_ALL 600
typedef struct time
{
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int millisecond;
};
namespace ZF_LOG
{
	extern int allrand;
	extern time tm;
}
void get_time(char* s_tm);
void get_pid(char* p_id);
char* get_loglevel(int p);
void get_rand(char* s_rand);
void union_string(char* p);

#endif // !__LOGINFOH__