#pragma once
#include"grammar.h"


class LL1
{
	grammar Gra; //ʵ����Gra��
	int len_non = Gra.non_ter.size(); //���ս���ĳ���
	int len_ter = Gra.terminal.size(); //�ս������
	std::vector<std::vector<std::string>> first; //first��
	std::vector<std::vector<std::string>> follow; //follow��
	std::vector<int> has_first; //�Ƿ�����first����0��ʾ�ޣ�1��ʾ��
	std::vector<int> has_follow; //�Ƿ�����follow����0��ʾ�ޣ�1��ʾ��
	std::vector <std::vector<int>> include_of; //��ʾ��follow���еĵݹ���ù�ϵ
	std::vector<std::vector<std::vector<std::string>>> table; //Ԥ�������
	std::vector<std::string> pre_stack; //Ԥ�����ջ
	std::vector<std::string> parse_s; //�����ַ���
public:
	void init(); //��ʼ��
	void get_first(); //�õ�first��
	void get_first_element(int symbol);//�õ�first����ÿ��Ԫ��
	void print_first(); //��ӡfirst��
	void get_follow(); //�õ�follow��
	void get_follow_element(int symbol); //�õ�follow����ÿ��Ԫ��
	void print_follow(); //��ӡfollow��
	void get_table(); //�õ�Ԥ�������
	void add_error_table(); //���Ӵ�����
	void print_table(); //��ӡԤ�������
	void parse(std::string s); //��������
	void parse_string(std::string s); //��ӡ�ַ���
	void print_parse(int pi, std::vector<std::string> s); //Ԥ������������д�ʱ���ַ�������Ҫ����dfaģ�ͷ�������
};

