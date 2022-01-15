#pragma once
#include<string>
#include<iostream>
#include<vector>
#include<iterator>
#include<cstdlib>
#include <algorithm>


class grammar
{
public:
	std::string S;//��ʼ����
	std::vector<std::string> terminal; //�ս��
	std::vector<std::string> non_ter;  //���ս��
	std::vector<std::vector<std::vector<std::string>>> all_gra; //�����ķ���ϵ

	int len_non; //���ս���ĳ���
	int len_ter; //�ս������
	std::vector<std::vector<std::string>> first; //first��
	std::vector<std::vector<std::string>> follow; //follow��

public:
	grammar();
	void read_grammer();
	void test_print_grammar(); //���Դ�ӡ��ʱ�ķ�
	void get_first(); //�õ�first��
	void print_first(); //��ӡfirst��
	void get_follow(); //�õ�follow��
	void print_follow(); //��ӡfollow��
};

