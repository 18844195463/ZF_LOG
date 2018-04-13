#pragma once
#ifndef DATATYPE_H
#define DATATYPE_H

#define MAX_STRING_SIZE 100
#include <iostream>
struct AA
{
	char p;
	unsigned int m;
};
typedef struct Temp
{
	char* buff;
	int length;
	int i_int;
	AA fff;
	char fmt_size[MAX_STRING_SIZE];
	static char* tostring()
	{
		char* p = " S_TEMP:{buff:%s, length:%d, i_int:%d, fff:{p:%c, m:%d}} ";
		return p;
	}
}S_Temp;

#endif // !DATATYPE_H

