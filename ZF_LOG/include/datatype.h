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
1. ͬ���޸�readfromlog.cpp��readnext����
2. ע��#
3. ע����ÿ���Զ������ǰ���#
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

