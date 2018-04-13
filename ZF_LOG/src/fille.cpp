
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "zf_log.h"
 static FILE *g_log_file;
namespace ZF_LOG
{
	void file_output_callback(const zf_log_message *msg, void *arg);
	void file_output_open(const char *const log_path);
	void file_output_close(void);
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
	atexit(file_output_close);
	zf_log_set_output_v(ZF_LOG_PUT_STD, 0, file_output_callback);
}

void ZF_LOG::log_init(char* file_name)
{
	file_output_open(file_name);
}

