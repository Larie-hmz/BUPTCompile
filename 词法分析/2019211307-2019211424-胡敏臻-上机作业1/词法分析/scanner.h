#pragma once
#include<iostream>
#include<fstream>

#define buffer_len 1024

class scanner
{
private:
	char buffer_1[buffer_len]; //上半缓冲区
	char buffer_2[buffer_len]; //下半缓冲区

	char* lexemebegin = buffer_1;
	char* forwardp = buffer_1;

public:
	std::ifstream myfile;

private:
	std::string temps; //存放读进来的字符串
	int flag = 0; //flag为0表示正在上半缓冲区，flag为1表示正在下半缓冲区
	char c;//读入的字符串
public:
	int line=0,row=0;
	int t_row=0;
public:
	void init();
	void get_nbc();
	char get_char();
	void read_half(char buffer[]);
	void retract();
	char get_c();
	//bool is_end();
};
extern scanner scan;
