#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <boost/any.hpp>
#include <sstream>
#include "zf_log.h"
#include "loginfo.h"
#include "datatype.h"
#define MAX_STRING_SIZE_ALL 600
using namespace std;


namespace ZF_LOG
{
	char state[MAX_STRING_SIZE_ALL] = { 0 };
}
bool ZF_LOG::writelog(int line, const char* file, Type type, const string& str)
{
	string lines;
	union_string(line, file, lines);
	lines += "    ";
	if (type == ZF_LOG::Type::Input)
		lines += "[input]:     ";
	if (type == ZF_LOG::Type::Output)
		lines += "[output]:    ";
	if (type == ZF_LOG::Type::Debug)
		lines += "[debug]:     ";
	if (type == ZF_LOG::Type::Info)
		lines += "[info]:      ";
	if (type == ZF_LOG::Type::Error)
		lines += "[error]:     ";
	if (type == ZF_LOG::Type::Function)
		lines += "[function]:  ";
	if (type == ZF_LOG::Type::Warn)
		lines += "[warn]:      ";
	lines += str;
	lines.push_back('\n');
	if (!g_log_file)
	{
		cout << "please first initalize log module" << endl;
		return false;
	}
	fwrite(lines.c_str(), sizeof(char), lines.size(), g_log_file);
	fflush(g_log_file);
	return true;
}
bool ZF_LOG::writelog(int line, const char* file, ZF_LOG::Type type, void* buf, uint32_t size)
{
	string lines;
	union_string(line, file, lines);
	lines += "    ";
	if (type == ZF_LOG::Type::Buffer)
		lines += "[buffer]:    ";
	std::ostringstream ostr;
	ostr << "0x" << buf;
	lines += ostr.str();
	lines += ":buffer, ";
	lines += to_string(size);
	lines += ":size, ";
	string fname;
	int index = 0;
	while (lines[++index] != ']')
	{
		if (lines[index] == '[')
			continue;
		else if (lines[index] == '-')
			continue;
		else if (lines[index] == ' ')
			continue;
		else if (lines[index] == ':')
			continue;
		else if (lines[index] == '.')
			continue;
		else
			fname.push_back(lines[index]);
	}
	int filerand = __FILERAND__;
	fname += to_string(filerand);
	lines += fname;
	lines += ";filename";
	lines.push_back('\n');
	if (!g_log_file)
	{
		cout << "please first initalize log module" << endl;
		return false;
	}
	fwrite(lines.c_str(), sizeof(char), lines.size(), g_log_file);
	fflush(g_log_file);
	return true;
}
bool ZF_LOG::writelog(int line, const char* file, Type type, vector<boost::any>&& params)
{
	string lines;
	union_string(line, file, lines);
	lines += "    ";

	if(type == ZF_LOG::Type::Input)
		lines += "[input]:     ";
	if(type == ZF_LOG::Type::Output)
		lines += "[output]:    ";
	if (type == ZF_LOG::Type::Debug)
		lines += "[debug]:     ";
	if (type == ZF_LOG::Type::Info)
		lines += "[info]:      ";
	if (type == ZF_LOG::Type::Error)
		lines += "[error]:     ";
	if (type == ZF_LOG::Type::Function)
		lines += "[function]:  ";
	if (type == ZF_LOG::Type::Warn)
		lines += "[warn]:      ";
	for (auto const& val : params)
	{
		if (val.type() == typeid(int) || val.type() == typeid(unsigned __int64) || val.type() == typeid(unsigned int) || val.type() == typeid(__int64))
		{
			//assert(v, a, c == log_read([4 - 23 15:31 : 19.866]).param[0], )
			if (val.type() == typeid(unsigned __int64))
				lines = lines + to_string(boost::any_cast<unsigned __int64>(val));
			if (val.type() == typeid(int))
				lines = lines + to_string(boost::any_cast<int>(val));
			if (val.type() == typeid(unsigned int))
				lines = lines + to_string(boost::any_cast<unsigned int>(val));
			if (val.type() == typeid(__int64))
				lines = lines + to_string(boost::any_cast<__int64>(val));
			lines += ":int";
			lines += ", ";
			continue;
		}
		if (val.type() == typeid(double) || val.type() == typeid(float))
		{
			lines += to_string(boost::any_cast<double>(val));
			lines += ":double";
			lines += ", ";
			continue;
		}
		if (val.type() == typeid(char))
		{
			lines.push_back(boost::any_cast<char>(val));
			lines += ":char";
			lines += ", ";
			continue;
		}
		if (val.type() == typeid(std::string))
		{
			lines += ":string";
			lines += ", ";
			continue;
		}
		if (!strcmp(val.type().name(), "char const *"))
		{
			//lines += "\"" + string(boost::any_cast<char const *>(val)) + "\"";
			lines += string(boost::any_cast<char const *>(val));
			lines += ":string";
			lines += ", ";
			continue;
		}
		if (val.type() == typeid(bool))
		{
			bool flag = boost::any_cast<bool>(val);
			if (flag)
				lines += string("true");
			else
				lines += string("false");
			lines += ":bool";
			lines += ", ";
			continue;
		}
		if (val.type() == typeid(void*))
		{
			std::ostringstream strs;
			strs << "0x" << boost::any_cast<void*>(val);
			lines += strs.str();
			lines += ":void*";
			lines += ", ";
			cout << "pointer" << endl;
			continue;
		}
		else
		{
			//auto exception_msg = std::string("[Error]: Unsupported Type - ") + val.type().name();
			//throw exception(exception_msg.c_str());
			cout << "cannot figure out the type";
			cout << val.type().name() << endl;
			string tp = string("cannot figure out the type ") + val.type().name();
			if (is_logfile_open())
				zf_write_log(ZF_LOG::Error, tp);
			return false;
		}
	}
	lines.push_back('\n');
	if (!g_log_file)
	{
		cout << "please first initalize log module" << endl;
		return false;
	}
	fwrite(lines.c_str(), sizeof(char), lines.size(), g_log_file);
	fflush(g_log_file);
	return true;
}


bool ZF_LOG::write_to_file(char* src, uint32_t buflen)
{
	int filerand = __FILERAND__;
	if (!src)
	{
		if (is_logfile_open())
			zf_write_log(ZF_LOG::Type::Error, "cannot write to nullptr");
		return false;
	}
	void* buf = src;
	if (is_logfile_open())
		zf_write_log(ZF_LOG::Type::Buffer, buf, buflen );
	string fname;
	if (!ZF_LOG::zlog_path)
		fname = "./";
	else
		fname = string(ZF_LOG::zlog_path);
	fname += to_string(ZF_LOG::tm.month);
	fname += to_string(ZF_LOG::tm.day);
	fname += to_string(ZF_LOG::tm.hour);
	fname += to_string(ZF_LOG::tm.minute);
	fname += to_string(ZF_LOG::tm.second);
	fname += to_string(ZF_LOG::tm.millisecond);
	fname += to_string(filerand);
	const char* file_name = fname.c_str();
	ofstream wfile;
	wfile.open(file_name, ios::out | ios::binary);
	if (!(wfile && wfile.is_open()))
	{
		cout << "file is not open!" << endl;
		return false;
	}
	char* ptr = src;
	wfile.write(ptr, buflen);
	wfile.close();
	return true;
}
bool ZF_LOG::write_to_file_test(char* src, uint32_t buflen, const string& dst_plate)
{
	int filerand = __FILERAND__;
	if (!src)
	{
		zf_write_log(ZF_LOG::Type::Error, "cannot write to nullptr");
		return false;
	}
	void* buf = src;
	zf_write_log(ZF_LOG::Type::Buffer, buf, buflen);
	string fname;
	if (dst_plate.size()  == 0)
		printf("a dictionary is needed");
	else
		fname = dst_plate;
	fname += to_string(ZF_LOG::tm.month);
	fname += to_string(ZF_LOG::tm.day);
	fname += to_string(ZF_LOG::tm.hour);
	fname += to_string(ZF_LOG::tm.minute);
	fname += to_string(ZF_LOG::tm.second);
	fname += to_string(ZF_LOG::tm.millisecond);
	fname += to_string(filerand);
	const char* file_name = fname.c_str();
	ofstream wfile;
	wfile.open(file_name, ios::out | ios::binary);
	if (!(wfile && wfile.is_open()))
	{
		cout << "file is not open!" << endl;
		return false;
	}
	char* ptr = src;
	wfile.write(ptr, buflen);
	wfile.close();
	return true;
}