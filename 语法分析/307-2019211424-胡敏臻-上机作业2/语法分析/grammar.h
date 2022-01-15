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
	std::string S;//开始符号
	std::vector<std::string> terminal; //终结符
	std::vector<std::string> non_ter;  //非终结符
	std::vector<std::vector<std::vector<std::string>>> all_gra; //所有文法关系

public:
	grammar();
	void read_grammer();
	void delete_left_recur(); //删除左递归
	//void delete_common_factor();
	void test_print_grammar(); //测试打印此时文法
};

