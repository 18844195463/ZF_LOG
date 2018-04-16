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
float foo(float a, char b, const S_Temp& pp)
{
	ZF_LOG::setfmt(3, "float", "char", "S_Temp");
	ZF_LOGWI(ZF_LOG::state, a, b, pp.buff, pp.length, pp.i_int, pp.fff.p, pp.fff.m);
	//fprintf(ZF_LOG::g_log_file, ZF_LOG::state, a, b, pp);
	ZF_LOG::write_to_file(pp.buff, 100, __FUNCTION__, "./");
	return (a + 1);
}
const int fafa(bool flag, uint32_t integer, char p, char d)
{
	ZF_LOG::setfmt(4, "bool", "uint32", "char", "char");
	ZF_LOGWI(ZF_LOG::state, flag, integer, p, d);
	char* ps = "hello world";
	ZF_LOG::write_to_file(ps, 12, __FUNCTION__, "./");
	ZF_LOG::setfmt(1, "int");
	ZF_LOGWI(ZF_LOG::state, 10);
	return 10;
}
int main()
{
	ZF_LOG::log_init("./log.txt");

	//fafa(false, 1000, 'c', 'm');
	S_Temp temp;
	char *p = new char[100];
	temp.buff = (char*)p;
	temp.length = 100;
	temp.i_int = 31;
	strcpy(temp.fmt_size, "xhm");
	temp.fff.m = 10;
	temp.fff.p = 'a';
	foo(1.1, 'm', temp);
    return 0;
}

