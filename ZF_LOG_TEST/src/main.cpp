// ConsoleApplication5.cpp : 定义控制台应用程序的入口点。
//
/*
 *ZF_LOGI(state, a, b, pp.buff, pp.length, pp.i_int, pp.fff.p, pp.fff.m);
 *write_to_file(pp.buff, pp.length, __FUNCTION__);
 *setfmt(3, "int", "int", "S_Temp"); //first param indicates num of string
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "logapi.h"
#include "datatype.h"
#include "readfromlog.h"
float foo(float a, char b, const S_Temp& pp)
{
	return (a + 1);
}
const int fafa(bool flag, uint32_t integer, char p, char d)
{
	return 10;
}
int main()
{
	ZF_LOG::log_init("E:\\log.txt");
	ZF_LOG::setfmt(4, "bool", "uint32", "char", "char");
	ZF_LOGWI(ZF_LOG::state, false, 1000, 'c', 'm');
	int t = fafa(false, 1000, 'c', 'm');
	char* ps = "daawflkmdcldalwdnwnfnasda;das";
	ZF_LOG::write_to_file(ps, 24000, __FUNCTION__, "E:\\");
	ZF_LOGWI(ZF_LOG::state, t);
	S_Temp temp;
	char *p = new char[100];
	temp.buff = (char*)p;
	temp.length = 100;
	temp.i_int = 31;
	strcpy(temp.fmt_size, "xhm");
	temp.fff.m = 10;
	temp.fff.p = 'a';
	ZF_LOG::setfmt(3, "float", "char", "S_Temp");
	ZF_LOGWI(ZF_LOG::state, 1.1, 'm', temp.buff, temp.length, temp.i_int, temp.fff.p, temp.fff.m);
	foo(1.1, 'm', temp);
	ZF_LOG::read_init();
	ZF_LOG::ReadType rtp = ZF_LOG::read_next();
	int size = 0;
	unsigned char* fp = ZF_LOG::read_memory(rtp, "E:\\", size);
	ZF_LOG::read_uninit();
	system("pause");
	return 0;
}

