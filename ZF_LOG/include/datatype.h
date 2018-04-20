#pragma once
#ifndef DATATYPE_H
#define DATATYPE_H
#define __FILERAND__ ZF_LOG::allrand
#define MAX_STRING_SIZE 100
#include <iostream>
struct AA
{
	char p;
	unsigned int m;
};
/*
1. 同步修改readfromlog.cpp中readnext方法
2. 注意#
3. 注意在每个自定义变量前面打#
*/
typedef struct Temp
{
	char* buff;
	int length;
	int i_int;
	AA fff;
	char fmt_size[MAX_STRING_SIZE];
	static const char* tostring()
	{
		const char* p = " #buff:%p, #length:%d, #i_int:%d, #p:%c, #m:%d ";
		return p;
	}
}S_Temp;

#endif // !DATATYPE_H

