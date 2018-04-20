
#include <stdlib.h>
#include <string>
#include "zf_log.h"
using namespace std;
namespace ZF_LOG
{
	void file_output_callback(const zf_log_message *msg, void *arg);
	void file_output_open(const char *const log_path);
	void file_output_close(void);
	FILE *g_log_file;
	char zlog_path[100] = { 0 };
	char log_file_name[100] = { 0 };
}
void ZF_LOG::file_output_callback(const zf_log_message *msg, void *arg)
{
	(void)arg;
	*msg->p = '\n';
	fwrite(msg->buf, msg->p - msg->buf + 1, 1, g_log_file);
	fflush(g_log_file);
}

void ZF_LOG::file_output_close(void)
{
	fclose(g_log_file);
}


void ZF_LOG::file_output_open(const char *const log_path)
{
	g_log_file = fopen(log_path, "a");
	if (!g_log_file)
	{
		ZF_LOGW("Failed to open log file %s", log_path);
		return;
	}
	strcpy(log_file_name, log_path);
#if defined (_WIN32) || defined (_WIN64)
	
	char* log_file_name_rev = log_file_name;
	strrev(log_file_name_rev);
	string tmp;
	bool help = true;
	for (int i = 0; i <= strlen(log_file_name_rev); ++i)
	{
		if (log_file_name_rev[i] != '\\' && help)
		{
			continue;
		}
		help = false;
			for (int j = i; j <= strlen(log_file_name_rev); ++j)
			{
				tmp.push_back(log_file_name_rev[j]);
			}
			break;
	}
	reverse(tmp.begin(), tmp.end());
	cout << tmp;
	for (int i = 0; i < tmp.size()-1; ++i)
		zlog_path[i] = tmp[i+1];
	strrev(log_file_name_rev);
#else
	char* log_file_name_rev = log_file_name;
	strrev(log_file_name_rev);
	string tmp;
	for (int i = 0; i < strlen(log_file_name_rev); ++i)
	{
		if (log_file_name_rev[i] == '/')
			break;
		else
		{
			for (int j = i; j < strlen(log_file_name_rev); ++j)
			{
				tmp.push_back(log_file_name_rev[j]);
			}
		}
	}
	reverse(tmp.begin(), tmp.end());
	cout << tmp;
	for (int i = 0; i < tmp.size(); ++i)
		zlog_path[i] = tmp[i];
	strrev(log_file_name_rev);
#endif
	atexit(file_output_close);

}

void ZF_LOG::log_init(char* file_name)
{
	file_output_open(file_name);
}

