#include "readfromlog.h"
#include "datatype.h"
#include <fstream>
#include <string>
#include <climits>
#define LINE_MAX_CHAR_NUM 1000
#define MEMBER_COUNT_OF_LOGBINFILE 13 
#define MAX_MEMORY_CONTENT 1000000
using namespace std;
char* ZF_LOG::ReadLog::memory_src = NULL;
static ifstream readfile;
ZF_LOG::ReadLog::ReadLog()
{
	if (!ZF_LOG::log_file_name)
	{
		std::cout << "no file to read";
		return;
	}
	strcpy(file_name, ZF_LOG::log_file_name);
}
void ZF_LOG::read_init()
{
	ReadLog readlog;
	readfile.open(readlog.file_name, ios::in);
	if (!readfile.is_open())
	{
		printf("cannot open the file %s", readlog.file_name);
	}
	//readfile.close();
}
void ZF_LOG::ReadLog::read_log()
{
}
void ZF_LOG::read_uninit()
{
	if (!ReadLog::memory_src)
		return;
	delete[] ReadLog::memory_src;
	if (readfile && readfile.is_open())
		readfile.close();
}
char* ZF_LOG::read_memory(const ReadType& rtp, int& size)
{
	if (ReadLog::memory_src)
	{
		delete[] ReadLog::memory_src;
		ReadLog::memory_src = NULL;
	}
	ReadLog::memory_src = new char[MAX_MEMORY_CONTENT];
	string str;
	int file_index = 0;
	if (ZF_LOG::zlog_path[file_index] == 0)
	{
		if (ZF_LOG::log_file_name[file_index] == 0)
			cout << "can not open file!" << endl;
		else
		{
			cout << "no file Specified, use default" << endl;
			//#if defined (_WIN32) || defined (_WIN64)
			//	char* log_file_name_rev = strrev(ZF_LOG::log_file_name);
			//	string tmp;
			//	for (int i = 0; i < strlen(log_file_name_rev); ++i)
			//	{
			//		if (log_file_name_rev[i] != '\\')
			//			continue;
			//		else
			//		{
			//			for (int j = i; j < strlen(log_file_name_rev); ++j)
			//			{
			//				tmp.push_back(log_file_name_rev[j]);
			//			}
			//		}
			//	}
			//	reverse(tmp.begin(), tmp.end());
			//	cout << tmp;
			//	for (int i = 0; i < tmp.size(); ++i)
			//		zlog_path[i] = tmp[i];
			//#else
			//	char* log_file_name_rev = strrev(ZF_LOG::log_file_name);
			//	string tmp;
			//	for (int i = 0; i < strlen(log_file_name_rev); ++i)
			//	{
			//		if (log_file_name_rev[i] == '/')
			//			break;
			//		else
			//		{
			//			for (int j = i; j < strlen(log_file_name_rev); ++j)
			//			{
			//				tmp.push_back(log_file_name_rev[j]);
			//			}
			//		}
			//	}
			//	reverse(tmp.begin(), tmp.end());
			//	cout << tmp;
			//	for (int i = 0; i < tmp.size(); ++i)
			//		zlog_path[i] = tmp[i];
			//#endif
		}
	}
	while (ZF_LOG::zlog_path[file_index] != 0)
	{
		str.push_back(ZF_LOG::zlog_path[file_index++]);
	}
	if (rtp.month.empty())
		return 0;
	string month, day, hour, minute, second, millonsec;
	for (int i = 0; i < rtp.month.size(); ++i)
	{
		if (rtp.month[i] == '0' && month.empty())
		{
			continue;
		}
		month.push_back(rtp.month[i]);
		str.push_back(rtp.month[i]);
	}
	for (int i = 0; i < rtp.day.size(); ++i)
	{
		if (rtp.day[i] == '0' && day.empty())
		{
			i++;
			continue;
		}
		day.push_back(rtp.day[i]);
		str.push_back(rtp.day[i]);
	}
	for (int i = 0; i < rtp.hour.size(); ++i)
	{
		if (rtp.hour[i] == '0' && hour.empty())
		{
			continue;
		}
		hour.push_back(rtp.hour[i]);
		str.push_back(rtp.hour[i]);
	}
	for (int i = 0; i < rtp.minute.size(); ++i)
	{
		if (rtp.minute[i] == '0' && minute.empty())
		{
			continue;
		}
		minute.push_back(rtp.minute[i]);
		str.push_back(rtp.minute[i]);
	}
	//for (int i = 0; i < rtp.second.size(); ++i)
	//{
	//	if (rtp.second[i] == '0' && second.empty())
	//	{
	//		continue;
	//	}
	//	second.push_back(rtp.second[i]);
	//	str.push_back(rtp.second[i]);
	//}
	//for (int i = 0; i < rtp.millonsec.size(); ++i)
	//{
	//	if (rtp.millonsec[i] == '0' && millonsec.empty())
	//	{
	//		continue;
	//	}
	//	millonsec.push_back(rtp.millonsec[i]);
	//	str.push_back(rtp.millonsec[i]);
	//}
	for (int i = 0; i < rtp.rand.size(); ++i)
	{
		str.push_back(rtp.rand[i]);
	}
	char file_name[100];
	int index = 0;
	while (str[index] != 0)
	{
		file_name[index] = str[index];
		index++;
	}
	file_name[index] = 0;

	int file_Length = 0;
	ifstream read__file;
	read__file.open(file_name, ios::in | ios::binary);
	if (!(read__file && read__file.is_open()))
	{
		cout << "file is not open!" << endl;
		return NULL;
	}
	while (!read__file.eof())            // 若未到文件结束一直循环 
	{
		unsigned char p;
		p = read__file.get();
		ReadLog::memory_src[file_Length] = p;
		file_Length++;
	}
	read__file.close();
	size = file_Length;
	return ReadLog::memory_src;
}

ZF_LOG::ReadType ZF_LOG::read_next()
{
	ReadType temp;
	if (!(readfile.is_open()))
	{
		cout << "file is not open";
		return temp;
	}
	//if (!readfile)
	//{
	//	for (int i = 0; i < 100; i++) {
	//		printf("close the file..................................\n");
	//	}
	//	readfile.close();
	//}
	if (readfile.is_open())
	{
		cout << "111" << endl;
	}
	if (readfile.eof())
	{
		for (int i = 0; i < 100; i++) {
			printf("come to eof, exit, you get nothing\n");
		}
		readfile.close();
		return temp;
	}
	if (readfile.peek() == EOF)
	{
		for (int i = 0; i < 100; i++) {
			printf("come to eof, exit, you get nothing\n");
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
		
	//readfile.getline(line, LINE_MAX_CHAR_NUM);





	typedef enum { MONTH, DAY, HOUR, MINUTE, SECOND, MILLSECOND, PROCESS, RANDNUM, DEBUG_INFO, FUNC_NAME, FUNC_FILE, LINE} Logbinfile_Member;
	bool flag[MEMBER_COUNT_OF_LOGBINFILE + 1];	
	for (int i = 0; i < MEMBER_COUNT_OF_LOGBINFILE + 1; ++i)
		flag[i] = true;
	int line_index = 0;						//单行索引，指示line中第line_index个数据， 操作读取的每行数据
	int flag_index = 1;						//flag标志位索引
	/*
	* 将line数组中的数据写入到 ReadType 对象中
	*/
	while (line[line_index] != '\0')		//未达到字符串结尾
	{
		while (line[line_index] != ' ')
		{
			if (temp.month.empty() || flag[Logbinfile_Member::MONTH])
			{
				if (line[line_index] == '-')
				{
					flag[Logbinfile_Member::MONTH] = false;
					line_index++;
					continue;
				}
				temp.month.push_back(line[line_index++]);
				continue;
			}

			if (temp.day.empty() || flag[Logbinfile_Member::DAY])
			{
				temp.day.push_back(line[line_index++]);
				continue;
			}

			if (temp.hour.empty() || flag[Logbinfile_Member::HOUR])
			{
				if (line[line_index] == ':')
				{
					flag[Logbinfile_Member::HOUR] = false;
					line_index++;
					flag_index++;
					continue;
				}
				temp.hour.push_back(line[line_index++]);
				continue;
			}

			if (temp.minute.empty() || flag[Logbinfile_Member::MINUTE])
			{
				if (line[line_index] == ':')
				{
					flag[Logbinfile_Member::MINUTE] = false;
					line_index++;
					flag_index++;
					continue;
				}
				temp.minute.push_back(line[line_index++]);
				continue;
			}

			if (temp.second.empty() || flag[Logbinfile_Member::SECOND])
			{
				if (line[line_index] == '.')
				{
					flag[Logbinfile_Member::SECOND] = false;
					line_index++;
					flag_index++;
					continue;
				}
				temp.second.push_back(line[line_index++]);
				continue;
			}

			if (temp.millonsec.empty() || flag[Logbinfile_Member::MILLSECOND])
			{
				temp.millonsec.push_back(line[line_index++]);
				continue;
			}

			if (temp.process.empty() || flag[Logbinfile_Member::PROCESS])
			{
				temp.process.push_back(line[line_index++]);
				continue;
			}

			if (temp.rand.empty() || flag[Logbinfile_Member::RANDNUM])
			{
				temp.rand.push_back(line[line_index++]);
				continue;
			}

			if (flag[Logbinfile_Member::DEBUG_INFO])
			{
				temp.debug_info = line[line_index++];
				continue;
			}

			if (temp.func_name.empty() || flag[Logbinfile_Member::FUNC_NAME])
			{
				if (line[line_index] == '@')
				{
					flag[Logbinfile_Member::FUNC_NAME] = false;
					line_index++;
					flag_index++;
					continue;
				}
				temp.func_name.push_back(line[line_index++]);
				continue;
			}

			if (temp.func_file.empty() || flag[Logbinfile_Member::FUNC_FILE])
			{
				if (line[line_index] == ':')
				{
					flag[Logbinfile_Member::FUNC_FILE] = false;
					line_index++;
					flag_index++;
					continue;
				}
				temp.func_file.push_back(line[line_index++]);
				continue;
			}

			if (temp.line.empty() || flag[Logbinfile_Member::LINE])
			{
				temp.line.push_back(line[line_index++]);
				continue;
			}
			//if (temp.randnum.empty() || flag[Logbinfile_Member::LINE])
			//{
			//	temp.randnum.push_back(line[line_index++]);
			//	continue;
			//}

		}
		if (line_index > 1 && line[line_index - 1] == ' ')    //多个空格连起来时，跳过
		{
			line_index++;
			continue;
		}
		line_index++;
		flag[flag_index++] = false;
		if (flag_index == MEMBER_COUNT_OF_LOGBINFILE-1)		//除 param 中内容，其余部分已经全部读取
		{
			string rest_str;
			int backspace_num = 0;
			for (int j = line_index; line[j] != 0; ++j)
			{
				if (line[j] == ' ')
					backspace_num++;
				rest_str.push_back(line[j]);
			}
			//
			for (int m = 0; m < backspace_num; ++m)
			{
				while (line[line_index] != 0)
				{
					if (line[line_index] == ',')
					{
						line_index++;
						continue;
					}
					if (line[line_index] == ' ')
					{
						line_index++;
						m++;
						continue;
					}
					temp.param[m].push_back(line[line_index]);
					line_index++;
				}
			}
		}
	}
	//if (temp.day.size() == 0)
	//	readfile.close();

	return temp;
}