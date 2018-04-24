#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <boost/any.hpp>
#include <sstream>
#include "zf_log.h"
#include "loginfo.h"
#include "datatype.h"
#define MAX_STRING_SIZE_ALL 600
using namespace std;


namespace ZF_LOG
{
	char state[MAX_STRING_SIZE_ALL] = { 0 };
}
void ZF_LOG::writelog(int line, const char* file, Type type, const char* str)
{
	string lines;
	union_string(line, file, lines);
	lines += "    ";
	if (type == ZF_LOG::Type::Debug)
		lines += "[debug]:     ";
	if (type == ZF_LOG::Type::Info)
		lines += "[info]:      ";
	if (type == ZF_LOG::Type::Error)
		lines += "[error]:     ";
	if (type == ZF_LOG::Type::Function)
		lines += "[function]:  ";
	if (type == ZF_LOG::Type::Warn)
		lines += "[warn]:      ";
	lines += str;
	lines.push_back('\n');
	char aline[MAX_STRING_SIZE_ALL] = { 0 };
	int help = 0;
	while (!lines.empty())
	{
		aline[help++] = lines.back();
		lines.pop_back();
	}
	strrev(aline);
	fwrite(aline, sizeof(char), help, g_log_file);
	fflush(g_log_file);
}
void ZF_LOG::writelog(int line, const char* file, ZF_LOG::Type type, void* buf, uint32_t size)
{
	string lines;
	union_string(line, file, lines);
	lines += "    ";
	if (type == ZF_LOG::Type::Buffer)
		lines += "[buffer]:    ";
	lines += to_string(reinterpret_cast<int>(buf));
	lines += ":buffer, ";
	lines += to_string(size);
	lines += ":size, ";
	string fname;
	int index = 0;
	while (lines[++index] != ']')
	{
		if (lines[index] == '[')
			continue;
		else if (lines[index] == '-')
			continue;
		else if (lines[index] == ' ')
			continue;
		else if (lines[index] == ':')
			continue;
		else if (lines[index] == '.')
			continue;
		else
			fname.push_back(lines[index]);
	}
	int filerand = __FILERAND__;
	fname += to_string(filerand);
	lines += fname;
	lines += ";filename";
	lines.push_back('\n');
	char aline[MAX_STRING_SIZE_ALL] = { 0 };
	int help = 0;
	while (!lines.empty())
	{
		aline[help++] = lines.back();
		lines.pop_back();
	}
	strrev(aline);
	fwrite(aline, sizeof(char), help, g_log_file);
	fflush(g_log_file);
}
void ZF_LOG::writelog(int line, const char* file, Type type, vector<boost::any>&& params)
{
	string lines;
	union_string(line, file, lines);
	lines += "    ";
	if (type == ZF_LOG::Type::Input || type == ZF_LOG::Type::Output)
	{
		if(type == ZF_LOG::Type::Input)
			lines += "[input]:     ";
		else
			lines += "[output]:    ";
		for (auto const& val : params)
		{
			if (val.type() == typeid(int) || val.type() == typeid(unsigned __int64) || val.type() == typeid(unsigned int) || val.type() == typeid(__int64))
			{
				int help;
				//assert(v, a, c == log_read([4 - 23 15:31 : 19.866]).param[0], )
				if (val.type() == typeid(unsigned __int64))
					lines = lines + to_string(boost::any_cast<unsigned __int64>(val));
				if (val.type() == typeid(int))
					lines = lines + to_string(boost::any_cast<int>(val));
				if (val.type() == typeid(unsigned int))
					lines = lines + to_string(boost::any_cast<unsigned int>(val));
				if (val.type() == typeid(__int64))
					lines = lines + to_string(boost::any_cast<__int64>(val));
				lines += ":int";
				lines += ", ";
				continue;
			}
			if (val.type() == typeid(double) || val.type() == typeid(float))
			{
				lines += to_string(boost::any_cast<double>(val));
				lines += ":double";
				lines += ", ";
				continue;
			}
			if (val.type() == typeid(char))
			{
				lines.push_back(boost::any_cast<char>(val));
				lines += ":char";
				lines += ", ";
				continue;
			}
			if (val.type() == typeid(std::string))
			{
				lines += ":string";
				lines += ", ";
				continue;
			}
			if (!strcmp(val.type().name(), "char const *"))
			{
				//lines += "\"" + string(boost::any_cast<char const *>(val)) + "\"";
				lines += string(boost::any_cast<char const *>(val));
				lines += ":string";
				lines += ", ";
				continue;
			}
			if (val.type() == typeid(bool))
			{
				bool flag = boost::any_cast<bool>(val);
				if (flag)
					lines += string("true");
				else
					lines += string("false");
				lines += ":bool";
				lines += ", ";
				continue;
			}
			if (val.type() == typeid(void*))
			{
				std::ostringstream strs;
				strs << "0x" << boost::any_cast<void*>(val);
				lines += strs.str();
				lines += ":void*";
				lines += ", ";
				cout << "pointer" << endl;
				continue;
			}
			else
			{
				//auto exception_msg = std::string("[Error]: Unsupported Type - ") + val.type().name();
				//throw exception(exception_msg.c_str());
				cout << "cannot specific the type";
				cout << val.type().name();
			}
		}
	}
	lines.push_back('\n');
	char aline[MAX_STRING_SIZE_ALL] = { 0 };
	int help = 0;
	while (!lines.empty())
	{
		aline[help++] = lines.back();
		lines.pop_back();
	}
	strrev(aline);
	if (!g_log_file)
		cout << "cannot open the file!";
	fwrite(aline, sizeof(char), help, g_log_file);
	fflush(g_log_file);
}


void ZF_LOG::write_to_file(char* src, uint32_t buflen)
{
	int filerand = __FILERAND__;
	void* buf = src;
	zf_write_log(ZF_LOG::Type::Buffer, buf, buflen );
	char file_name[FILENAME_MAX] = { 0 };
	strcat(file_name, ZF_LOG::zlog_path);

	char month[20];
	char day[20];
	char hour[20];
	char minute[20];
	char second[20];
	char wsecond[20];

#if defined(_WIN32) || defined(_WIN64)
	sprintf(month, "%hu", ZF_LOG::tm.month);
	sprintf(day, "%hu", ZF_LOG::tm.day);
	sprintf(hour, "%hu", ZF_LOG::tm.hour);
	sprintf(minute, "%hu", ZF_LOG::tm.minute);
	sprintf(second, "%hu", ZF_LOG::tm.second);
	sprintf(wsecond, "%hu", ZF_LOG::tm.millisecond);
	strcat(file_name, month);
	strcat(file_name, day);
	strcat(file_name, hour);
	strcat(file_name, minute);
	strcat(file_name, second);
	strcat(file_name, wsecond);
	char str[100];
	int index = 0;
	while (filerand > 0)
	{
		str[index++] = filerand %10+48;
		filerand = filerand / 10;
	}
	str[index] = 0;
	strrev(str);
	strcat(file_name, str);
	
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
	//strcat(file_name, second);
	//strcat(file_name, wsecond);
	char str[100];
	int index = 0;
	while (filerand > 1)
	{
		str[index++] = filerand % 10;
		filerand = filerand % 10;
	}
	str[index] = 0;
	strrev(str);
	strcat(file_name, str);
#endif

	/*FILE *fp;*/
	//if ((fp = fopen(file_name, "w")) == NULL) {
	//	printf("File cannot be opened\n");
	//	//exit(0);
	//}
	//else
	//	printf("File opened for writing\n");
	ofstream wfile;
	wfile.open(file_name, ios::out | ios::binary);
	if (!(wfile && wfile.is_open()))
	{
		cout << "file is not open!" << endl;
		return;
	}
	char* ptr = src;
	wfile.write(ptr, buflen);
	//for(int i = 0; i < buflen; ++i)
	//	fprintf(fp, "%c", (unsigned char)ptr[i]);
	//fflush(fp);
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
	//fclose(fp);
	wfile.close();
}
void ZF_LOG::write_to_file_test(char* src, uint32_t buflen, const char* dst_plate)
{
	int filerand = __FILERAND__;

	char file_name[FILENAME_MAX] = { 0 };
	strcat(file_name, dst_plate);

	char month[20];
	char day[20];
	char hour[20];
	char minute[20];
	char second[20];
	char wsecond[20];

#if defined(_WIN32) || defined(_WIN64)
	sprintf(month, "%hu", ZF_LOG::tm.month);
	sprintf(day, "%hu", ZF_LOG::tm.day);
	sprintf(hour, "%hu", ZF_LOG::tm.hour);
	sprintf(minute, "%hu", ZF_LOG::tm.minute);
	sprintf(second, "%hu", ZF_LOG::tm.second);
	sprintf(wsecond, "%hu", ZF_LOG::tm.millisecond);
	strcat(file_name, month);
	strcat(file_name, day);
	strcat(file_name, hour);
	strcat(file_name, minute);
	strcat(file_name, second);
	strcat(file_name, wsecond);
	char str[100];
	int index = 0;
	while (filerand > 0)
	{
		str[index++] = filerand % 10 + 48;
		filerand = filerand / 10;
	}
	str[index] = 0;
	strrev(str);
	strcat(file_name, str);

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
	//strcat(file_name, second);
	//strcat(file_name, wsecond);
	char str[100];
	int index = 0;
	while (filerand > 1)
	{
		str[index++] = filerand % 10;
		filerand = filerand % 10;
	}
	str[index] = 0;
	strrev(str);
	strcat(file_name, str);
#endif
	ofstream wfile;
	wfile.open(file_name, ios::out | ios::binary);
	if (!(wfile && wfile.is_open()))
	{
		cout << "file is not open!" << endl;
		return;
	}
	char* ptr = src;
	wfile.write(ptr, buflen);
	wfile.close();
}