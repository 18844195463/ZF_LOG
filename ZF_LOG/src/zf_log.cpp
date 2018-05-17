#include "zf_log.h"
#include "datatype.h"
#include "logapi.h"

bool zf_log_init(string file_name)
{
	return ZF_LOG::log_init(file_name);
}
bool zf_write_to_file(char* src, uint32_t buflen)
{
	return ZF_LOG::write_to_file(src, buflen);
}
bool zf_write_to_file_test(char* src, uint32_t buflen, const string& dst_plate)
{
	return ZF_LOG::write_to_file_test(src, buflen, dst_plate);
}
bool zf_read_init()
{
	return ZF_LOG::read_init();
}
char* zf_read_memory(const ZF_LOG::ReadType& rtp, int& size)
{
	return ZF_LOG::read_memory(rtp, size);
}
void zf_read_uninit()
{
	ZF_LOG::read_uninit();
}
ZF_LOG::ReadType zf_read_next()
{
	return ZF_LOG::read_next();
}
void zf_log_uninit()
{
	void ZF_LOG::file_output_close(void);
}