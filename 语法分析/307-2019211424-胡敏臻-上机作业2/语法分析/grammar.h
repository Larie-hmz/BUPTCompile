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

public:
	grammar();
	void read_grammer();
	void delete_left_recur(); //ɾ����ݹ�
	//void delete_common_factor();
	void test_print_grammar(); //���Դ�ӡ��ʱ�ķ�
};

