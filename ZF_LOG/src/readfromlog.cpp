#include "readfromlog.h"
#include "datatype.h"
#include "zf_log.h"
#include <fstream>
#include <string>
#include "logapi.h"
#define LINE_MAX_CHAR_NUM 1000
#define MAX_MEMORY_CONTENT 1000000
using namespace std;
char* ZF_LOG::ReadLog::memory_src = NULL;
static ifstream readfile;
ZF_LOG::ReadLog::ReadLog()
{
	if (!ZF_LOG::log_file_name)
	{
		std::cout << "no file to read， please first use \"zf_log_init\" method";
		return;
	}
	strcpy(file_name, ZF_LOG::log_file_name);
}
bool ZF_LOG::read_init()
{
	ZF_LOG::ReadLog readlog;
	readfile.open(readlog.file_name, ios::in);
	if (!readfile.is_open())
	{
		printf("cannot open the file %s", readlog.file_name);
		return false;
	}
	return true;
	//readfile.close();
}
void ZF_LOG::ReadLog::read_log()
{
}
void ZF_LOG::read_uninit()
{
	if (!ZF_LOG::ReadLog::memory_src)
		return;
	delete[] ZF_LOG::ReadLog::memory_src;
	if (readfile && readfile.is_open())
		readfile.close();
}
char* ZF_LOG::read_memory(const ZF_LOG::ReadType& rtp, int& size)
{
	if (ZF_LOG::ReadLog::memory_src)
	{
		delete[] ZF_LOG::ReadLog::memory_src;
		ZF_LOG::ReadLog::memory_src = NULL;
	}
	ZF_LOG::ReadLog::memory_src = new char[MAX_MEMORY_CONTENT];
	string str;
	str += string(ZF_LOG::zlog_path);
	if (rtp.filename.empty())
	{
		cout << "no buffer to read" << endl;
		return 0;
	}
	str += rtp.filename;
	int file_Length = 0;
	ifstream read__file;
	read__file.open(str.c_str(), ios::in | ios::binary);
	if (!(read__file && read__file.is_open()))
	{
		cout << "file is not open!" << endl;
		return NULL;
	}
	while (!read__file.eof())            // 若未到文件结束一直循环 
	{
		unsigned char p;
		p = read__file.get();
		ZF_LOG::ReadLog::memory_src[file_Length] = p;
		file_Length++;
	}
	read__file.close();
	size = file_Length-1;
	return ZF_LOG::ReadLog::memory_src;
}

ZF_LOG::ReadType ZF_LOG::read_next()
{
	ZF_LOG::ReadType temp;
	if (!(readfile.is_open()))
	{
		cout << "file is not open";
		if(is_logfile_open())
			zf_write_log(ZF_LOG::Error, "please use method read_init() before read_next()");
		return temp;
	}
	if (readfile.eof())
	{
		for (int i = 0; i < 100; i++) {
			printf("come to eof, exit, you get nothing\n");
			if (is_logfile_open())
				zf_write_log(ZF_LOG::Info, "come to eof, exit!");
		}
		readfile.close();
		return temp;
	}
	if (readfile.peek() == EOF)
	{
		for (int i = 0; i < 100; i++) {
			printf("come to eof, exit\n");
			if (is_logfile_open())
				zf_write_log(ZF_LOG::Info, "come to eof, exit!");
		}
		readfile.close();
		return temp;
	}
	char line[LINE_MAX_CHAR_NUM] = { 0 };		//保存读取log.txt中的每行数据, 保存在line数组中

	int index = 0;
	while (true)
	{
		if((line[index++] = readfile.get()) == '\n')
			break;
	}
	int line_index = 0;						//单行索引，指示line中第line_index个数据， 操作读取的每行数据	
	/*
	* 将line数组中的数据写入到 ReadType 对象中
	*/
	line_index++;
	while (line[line_index] != '-')
		temp.month.push_back(line[line_index++]);
	line_index++;
	while (line[line_index] != ' ')
		temp.day.push_back(line[line_index++]);
	line_index++;
	while (line[line_index] != ':')
		temp.hour.push_back(line[line_index++]);
	line_index++;
	while (line[line_index] != ':')
		temp.minute.push_back(line[line_index++]);
	line_index++;
	while (line[line_index] != '.')
		temp.second.push_back(line[line_index++]);
	line_index++;
	while (line[line_index] != ']')
		temp.millonsec.push_back(line[line_index++]);
	line_index++;
	while (line[line_index++] != ':')
		continue;
	while (line[line_index] != ']')
		temp.line.push_back(line[line_index++]);
	line_index++;
	while (line[line_index++] == ' ')
		continue;
	line_index--;
	while (line[line_index] != ' ')
		temp.func_name.push_back(line[line_index++]);
	line_index++;
	while (line[line_index++] == ' ')
		continue;
	line_index--;
	while (line[line_index] != ' ')
		temp.debug_info.push_back(line[line_index++]);
	line_index++;
	while (line[line_index] == ' ')
	{
		line_index++;
	}
	string str;
	vector<boost::any> vec;
	while (line[line_index] != '\n')
	{
		if (-1 != temp.debug_info.find("buffer"))
		{
			string buf, siz, fi;
			while (line[line_index] != ':')
				buf.push_back(line[line_index++]);
			while (line[line_index++] != ',')
				continue;
			line_index++;
			while (line[line_index] != ':')
				siz.push_back(line[line_index++]);
			while (line[line_index++] != ',')
				continue;
			line_index++;
			while (line[line_index] != ';')
				fi.push_back(line[line_index++]);
			temp.buffer = buf;
			temp.size = siz;
			temp.filename = fi;
			return temp;
		}
		if (-1 != temp.debug_info.find("function") || -1 != temp.debug_info.find("info") || -1 != temp.debug_info.find("warn") || -1 != temp.debug_info.find("debug") || -1 != temp.debug_info.find("error"))
		{
			str.push_back(line[line_index]);
			line_index++;
		}
		if (temp.debug_info.find("input")!=-1 || temp.debug_info.find("output")!=-1)
		{
			if (line[line_index] != ':')
				str.push_back(line[line_index]);
			else
			{
				string tp;
				while (line[line_index] != ',')
				{
					tp.push_back(line[line_index]);
					line_index++;
				}
				if (-1 != tp.find("char"))
				{
					vec.push_back(char(str[0]));
					str.clear();
				}
				else if (-1 != tp.find("int"))
				{
					vec.push_back(stoi(str));
					str.clear();
				}
				else if (-1 != tp.find("double"))
				{
					vec.push_back(stod(str));
					str.clear();
				}
				else if (-1 != tp.find("bool"))
				{
					if(-1 != str.find("true"))
					{
						vec.push_back(bool(true));
						str.clear();
					}
					else if (-1 != str.find("false"))
					{
						vec.push_back(bool(false));
						str.clear();
					}
				}
				else if (-1 != tp.find("string"))
				{
					vec.push_back(str);
					str.clear();
				}
				else (-1 != tp.find("void*"));
			}
			line_index++;
		}
	}
	if (-1 != temp.debug_info.find("function") || -1 != temp.debug_info.find("info") || -1 != temp.debug_info.find("warn") || -1 != temp.debug_info.find("debug") || -1 != temp.debug_info.find("error"))
	{
		vec.push_back(str);
	}
	temp.param = vec;
	return temp;
}