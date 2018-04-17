#include "readfromlog.h"
#include "datatype.h"
#include <fstream>
#include <string>
#include <climits>
#define UINT32_MAX_INT UINT32_MAX
using namespace std;
static std::vector <ZF_LOG::ReadType> type;
static std::vector<ZF_LOG::ReadType>::iterator iter;
unsigned char* ZF_LOG::ReadLog::memory_src = NULL;
ZF_LOG::ReadLog::ReadLog()
{
	//if (ZF_LOG::g_log_file)
	//{
	//	std::cout << "please first close the logfile";
	//	return;
	//}
	if (!ZF_LOG::log_file_name)
	{
		std::cout << "no file to read";
		return;
	}
	log_file = ZF_LOG::g_log_file;
	strcpy(file_name, ZF_LOG::log_file_name);
}
void ZF_LOG::read_init()
{
	ReadLog readlog;
	readlog.read_all(type);
	cout << std::endl << std::endl << std::endl;
	//ReadLog::memory_src = new unsigned char[1000000];
	/*for (int i = 0; i< type.size(); ++i)
		std::cout << type[i].month << " " << type[i].day << " " << type[i].hour << " " << type[i].minute << " " << type[i].second << " " << type[i].func_file << " " << type[i].param[3] << std::endl;*/
}
ZF_LOG::ReadType& ZF_LOG::read_next()
{
	ReadType temp;
	if (type.empty())
		return temp;
	iter = type.begin();
	return *iter++;
}
void ZF_LOG::ReadLog::read_log()
{
	//ifstream readfile;
	//readfile.open(file_name, ios::in);
	//char a[300];
	//int i = 0;
	//while (!readfile.eof())            // 若未到文件结束一直循环 
	//{
	//	readfile.getline(a, 300);
	//	cout << a << endl;
	//}
	//readfile.close();
}
void ZF_LOG::read_uninit()
{
	if (!ReadLog::memory_src)
		return;
	delete[] ReadLog::memory_src;
}
unsigned char* ZF_LOG::read_memory(const ReadType& rtp, const char* dst_plate, int& size)
{
	if (ReadLog::memory_src)
	{
		delete[] ReadLog::memory_src;
		ReadLog::memory_src = NULL;
	}
	ReadLog::memory_src = new unsigned char[1000000];
	if (!dst_plate)
		return 0;
	string str;
	int file_index = 0;
	while (dst_plate[file_index] != 0)
	{
		str.push_back(dst_plate[file_index]);
		file_index++;
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
	for (int i = 0; i < rtp.second.size(); ++i)
	{
		if (rtp.second[i] == '0' && second.empty())
		{
			continue;
		}
		second.push_back(rtp.second[i]);
		str.push_back(rtp.second[i]);
	}
	for (int i = 0; i < rtp.millonsec.size(); ++i)
	{
		if (rtp.millonsec[i] == '0' && millonsec.empty())
		{
			continue;
		}
		millonsec.push_back(rtp.millonsec[i]);
		str.push_back(rtp.millonsec[i]);
	}
	for (int i = 0; i < rtp.func_name.size(); ++i)
	{
		str.push_back(rtp.func_name[i]);
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
	ifstream readfile;
	readfile.open(file_name, ios::in | ios::binary);

	while (!readfile.eof())            // 若未到文件结束一直循环 
	{
		unsigned char p;
		p = readfile.get();
		ReadLog::memory_src[file_Length] = p;
		file_Length++;
	}
	readfile.close();
	size = file_Length;
	return ReadLog::memory_src;
}
void ZF_LOG::ReadLog::read_all(vector<ReadType>& type)
{
	ifstream readfile;
	readfile.open(file_name, ios::in);
	char a[300];
	int i = 0;
	while (!readfile.eof())            // 若未到文件结束一直循环 
	{
		readfile.getline(a, 300);
		cout << a << endl;
		ReadType temp;
		int i = 0, index = 1;
		bool flag[13] = { };
		for (int i = 0; i < 13; ++i)
			flag[i] = true;
		while (a[i] != 0)
		{
			while (a[i] != ' ')
			{
				if (temp.month.empty() || flag[0])
				{
					if (a[i] == '-')
					{
						flag[0] = false;
						i++;
						continue;
					}
					temp.month.push_back(a[i++]);
					continue;
				}

				if (temp.day.empty() || flag[1])
				{
					temp.day.push_back(a[i++]);
					continue;
				}

				if (temp.hour.empty() || flag[2])
				{
					if (a[i] == ':')
					{
						flag[2] = false;
						i++;
						index++;
						continue;
					}
					temp.hour.push_back(a[i++]);
					continue;
				}

				if (temp.minute.empty() || flag[3])
				{
					if (a[i] == ':')
					{
						flag[3] = false;
						i++;
						index++;
						continue;
					}
					temp.minute.push_back(a[i++]);
					continue;
				}

				if (temp.second.empty() || flag[4])
				{
					if (a[i] == '.')
					{
						flag[4] = false;
						i++;
						index++;
						continue;
					}
					temp.second.push_back(a[i++]);
					continue;
				}

				if (temp.millonsec.empty() || flag[5])
				{
					temp.millonsec.push_back(a[i++]);
					continue;
				}

				if (temp.process.empty() || flag[6])
				{
					temp.process.push_back(a[i++]);
					continue;
				}

				if (temp.thread.empty() || flag[7])
				{
					temp.thread.push_back(a[i++]);
					continue;
				}

				if (flag[8])
				{
					temp.debug_info = a[i++];
					continue;
				}

				if (temp.func_name.empty() || flag[9])
				{
					if (a[i] == '@')
					{
						flag[9] = false;
						i++;
						index++;
						continue;
					}
					temp.func_name.push_back(a[i++]);
					continue;
				}

				if (temp.func_file.empty() || flag[10])
				{
					if (a[i] == ':')
					{
						flag[10] = false;
						i++;
						index++;
						continue;
					}
					temp.func_file.push_back(a[i++]);
					continue;
				}

				if (temp.line.empty() || flag[11])
				{
					temp.line.push_back(a[i++]);
					continue;
				}
			}
			if (i > 1 && a[i - 1] == ' ')
			{
				i++;
				continue;
			}
			i++;
			flag[index++] = false;
			if (index == 12)
			{
				string rest_str;
				int backspace_num = 0;
				for (int j = i; a[j] != 0; ++j)
				{
					if (a[j] == ' ')
						backspace_num++;
					rest_str.push_back(a[j]);
				}
				//
				for (int m = 0; m < backspace_num; ++m)
				{
					while (a[i] != 0)
					{
						if (a[i] == ',')
						{
							i++;
							continue;
						}
						if (a[i] == ' ')
						{
							i++;
							m++;
							continue;
						}
						temp.param[m].push_back(a[i]);
						i++;
					}
				}
				//
				break;
			}
		}
		type.push_back(temp);
	}
	readfile.close();
}