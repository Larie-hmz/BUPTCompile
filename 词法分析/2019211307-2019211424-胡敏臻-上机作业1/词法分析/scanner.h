#pragma once
#include<iostream>
#include<fstream>

#define buffer_len 1024

class scanner
{
private:
	char buffer_1[buffer_len]; //�ϰ뻺����
	char buffer_2[buffer_len]; //�°뻺����

	char* lexemebegin = buffer_1;
	char* forwardp = buffer_1;

public:
	std::ifstream myfile;

private:
	std::string temps; //��Ŷ��������ַ���
	int flag = 0; //flagΪ0��ʾ�����ϰ뻺������flagΪ1��ʾ�����°뻺����
	char c;//������ַ���
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
