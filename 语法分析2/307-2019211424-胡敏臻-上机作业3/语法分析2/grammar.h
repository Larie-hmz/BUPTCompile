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

	int len_non; //非终结符的长度
	int len_ter; //终结符长度
	std::vector<std::vector<std::string>> first; //first集
	std::vector<std::vector<std::string>> follow; //follow集

public:
	grammar();
	void read_grammer();
	void test_print_grammar(); //测试打印此时文法
	void get_first(); //得到first集
	void print_first(); //打印first集
	void get_follow(); //得到follow集
	void print_follow(); //打印follow集
};

