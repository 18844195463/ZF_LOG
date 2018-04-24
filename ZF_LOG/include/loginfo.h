#pragma once
#ifndef __LOGINFOH__
#define __LOGINFOH__
#include <windows.h>
#include <string>
#include "logapi.h"
#define MAX_STRING_SIZE_ALL 600
#define tostr(a) #a
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

void union_string(int, const char*, std::string& p);

#endif // !__LOGINFOH__