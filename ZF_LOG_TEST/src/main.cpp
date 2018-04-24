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
#include <boost/any.hpp>
#include "logapi.h"
#include "datatype.h"
#include "readfromlog.h"
#include "loginfo.h"
//#define str(x) #x
float foo(float a, char b, const S_Temp& pp)
{
	return (a + 1);
}
const int fafa(bool flag, uint32_t integer, char p, char d)
{
	return 10;
}
//
//string xf_log(std::vector<boost::any>&& some_values)
//{
//	for (boost::any& val : some_values)
//	{
//		if (val.type() == typeid(int))
//		{
//			return  to_string(any_cast<int>(val)) + ":int"
//		}
//		else if (val.type() == typeid(double))
//		{
//			return  to_string(any_cast<int>(val)) + typeid(val.type()).name();
//		}
//	}
//
//	"10"
//}

int bar(std::vector<boost::any>&& some_values)
{
	for (auto const& val : some_values)
	{
		if (val.type() == typeid(int))
			std::cout << boost::any_cast<int>(val) << ":int ";
	}
	return 1;
}

int main()
{
	char *p = new char[100];
	ZF_LOG::log_init("E:\\mm\\log.txt");
	ZF_LOG::read_init();
	WRITELOG(ZF_LOG::Type::Function, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	WRITELOG(ZF_LOG::Type::Input, { "abc", 513, 2.206, 'r', false });
	//WRITELOG(ZF_LOG::Type::Output, { &p, 2.206, 'r', false });
	//	ZF_LOG::writebuffer(type::Buffer, buffer);
	ZF_LOG::write_to_file(p, 10000);
	ZF_LOG::read_next();
	ZF_LOG::read_next();
	ZF_LOG::ReadType rtp = ZF_LOG::read_next();
	cout << rtp.minute << rtp.millonsec << rtp.func_name << endl;
			if (rtp.day.size() != 0)
			{
				int size = 0;
				char* fp = ZF_LOG::read_memory(rtp, size);
				ZF_LOG::write_to_file_test(fp, size, "E:\\nn\\");
			}
		ZF_LOG::read_uninit();

	return 0;
}

