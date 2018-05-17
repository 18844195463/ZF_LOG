
#include <stdlib.h>
#include <string>
#include "zf_log.h"
#include "logapi.h"
using namespace std;
namespace ZF_LOG
{
	bool file_output_open(const string& log_path);
	//void file_output_close(void);
	FILE *g_log_file;
	/*日志路径，和内存记录文件路径一致*/
	char zlog_path[_MAX_DIR] = { 0 }; 
	/*日志文件名*/
	char log_file_name[_MAX_FNAME] = { 0 }; 
}

void ZF_LOG::file_output_close(void)
{
	if (g_log_file)
	{
		printf("close the file %s", log_file_name);
		fclose(g_log_file);
	}
	memset(zlog_path, 0, strlen(zlog_path));
	memset(log_file_name, 0, strlen(log_file_name));
}

bool ZF_LOG::file_output_open(const string& log_path)
{
	char path[_MAX_DIR + _MAX_FNAME] = { 0 };
	if(log_path.size() == 0)
		strcpy(path, "./log.txt");
	else
		strcpy(path, log_path.c_str());
	g_log_file = fopen(path, "a");
	if (!g_log_file)
	{
		printf("fail to open the file: %s", path);
		return false;
	}
	strcpy(log_file_name, path);
	string temp(path);
	char c;
	while ((c = temp[temp.size() - 1]) != '/' && c != '\\')
		temp.pop_back();
	for (int i = 0; i < temp.size(); ++i)
		zlog_path[i] = temp[i];
	atexit(file_output_close);
	return true;
}
bool ZF_LOG::is_logfile_open()
{
	if (!g_log_file)
		return false;
	return true;
}
bool ZF_LOG::log_init(string file_name)
{
	return ZF_LOG::file_output_open(file_name);
}

