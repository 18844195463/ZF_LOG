#include <iostream>
#include "zf_log.h"
#include "datatype.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#if defined(_WIN32) || defined(_WIN64)
	#include <windows.h>
#else
	#include <unistd.h>
	#include <sys/time.h>
	extern inline int tcache_get(const struct timeval *const tv, struct tm *const tm);
	extern inline void tcache_set(const struct timeval *const tv, struct tm *const tm);
#endif
//# define ZF_LOGPUT(...) \
	//ZF_LOGI(state, __VA_ARGS__)

namespace ZF_LOG
{
	char state[MAX_STRING_SIZE_ALL] = { 0 };
	char* getUserDefinedType(char* str);
	char* get_type(char* type);
}


char* ZF_LOG::getUserDefinedType(char* str)
{
	if (!strcmp(str, "S_Temp"))
		return S_Temp::tostring();
	else
		return "";
}

char* ZF_LOG::get_type(char* type)
{
	if (type == nullptr)
		return nullptr;
	if (!strcmp(type, "double"))
		return "%.4f, ";
	if (!strcmp(type, "float"))
		return "%.2f, ";
	if (!strcmp(type, "int32"))
		return "%d, ";
	if (!strcmp(type, "int64"))
		return "%d, ";
	if (!strcmp(type, "uint32"))
		return "%d, ";
	if (!strcmp(type, "uint64"))
		return "%d, ";
	if (!strcmp(type, "bool"))
		return "%d, ";
	if (!strcmp(type, "char"))
		return "%c, ";
	if (!strcmp(type, "int"))
		return "%d, ";
	if (!strcmp(type, "*"))
		return "%p, ";
	char* str = getUserDefinedType(type);
	return str;
}
void ZF_LOG::setfmt(int count, ...)
{
	if (!count)
		return;
	char wanted[MAX_STRING_SIZE_ALL] = {0};
	va_list va;
	va_start(va, count);
	if (strcmp(state, ""))
	{
		for (int i = 0; i < MAX_STRING_SIZE_ALL; ++i)
			state[i] = 0;
	}
	for (int num = 0; num < count; ++num)
	{
		char* type;
		type = va_arg(va, char*);
		strcat(state, ZF_LOG::get_type(type));
	}
	va_end(va);
	//strcpy(Log::state, wanted);
	//return wanted;
}



void ZF_LOG::write_to_file(char* src, size_t buflen, const char* filename, const char* dst_plate)
{
	char file_name[FILENAME_MAX] = { 0 };
	if (!filename)
		return;
	if (!dst_plate)
		return;
	strcat(file_name, dst_plate);

	char month[20];
	char day[20];
	char hour[20];
	char minute[20];
	char second[20];
	char wsecond[20];

#if defined(_WIN32) || defined(_WIN64)
	SYSTEMTIME st;
	GetLocalTime(&st);

	sprintf(month, "%hu", st.wMonth);
	sprintf(day, "%hu", st.wDay);
	sprintf(hour, "%hu", st.wHour);
	sprintf(minute, "%hu", st.wMinute);
	sprintf(second, "%hu", st.wSecond);
	sprintf(wsecond, "%hu", st.wMilliseconds);
	strcat(file_name, month);
	strcat(file_name, day);
	strcat(file_name, hour);
	strcat(file_name, minute);
	strcat(file_name, second);
	strcat(file_name, wsecond);
	strcat(file_name, filename);
	
#else // unix like system
	struct timeval tv;
	gettimeofday(&tv, 0);
	struct tm tm;

	if (!tcache_get(&tv, &tm))
	{
		localtime_r(&tv.tv_sec, &tm);
		tcache_set(&tv, &tm);
	}

	sprintf(month, "%hu", tm.tm_mon);
	sprintf(hour, "%hu", tm.tm_mday);
	sprintf(hour, "%hu", tm.tm_hour);
	sprintf(minute, "%hu", tm.tm_min);
	sprintf(second, "%hu", tm.tm_sec);
	sprintf(wsecond, "%hu", (unsigned)tv.tv_usec / 1000);
	strcat(file_name, month);
	strcat(file_name, day);
	strcat(file_name, hour);
	strcat(file_name, minute);
	strcat(file_name, second);
	strcat(file_name, wsecond);
	strcat(file_name, filename);
#endif

	FILE *fp;
	std::cout << file_name;
	if ((fp = fopen(file_name, "w")) == NULL) {
		printf("File cannot be opened\n");
		//exit(0);
	}
	else
		printf("File opened for writing\n");
	char* ptr = src;
	for(int i = 0; i < buflen; ++i)
		fprintf(fp, "%c", (unsigned char)ptr[i]);
	fflush(fp);
	//for (size_t i = 0; i < buflen; i += 64)
	//{
	//	for (size_t j = 0; j < 64; ++j)
	//	{
	//		if (i + j < buflen)
	//		{
	//			fprintf(fp, "%c", (unsigned char)ptr[i + j]);
	//		}
	//	}
	//	fflush(fp);
	//}
	fclose(fp);
}
