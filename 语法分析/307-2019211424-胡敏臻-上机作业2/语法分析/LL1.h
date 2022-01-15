#pragma once
#include"grammar.h"


class LL1
{
	grammar Gra; //实例化Gra类
	int len_non = Gra.non_ter.size(); //非终结符的长度
	int len_ter = Gra.terminal.size(); //终结符长度
	std::vector<std::vector<std::string>> first; //first集
	std::vector<std::vector<std::string>> follow; //follow集
	std::vector<int> has_first; //是否已有first集，0表示无，1表示有
	std::vector<int> has_follow; //是否已有follow集，0表示无，1表示有
	std::vector <std::vector<int>> include_of; //表示在follow集中的递归调用关系
	std::vector<std::vector<std::vector<std::string>>> table; //预测分析表
	std::vector<std::string> pre_stack; //预测分析栈
	std::vector<std::string> parse_s; //分析字符串
public:
	void init(); //初始化
	void get_first(); //得到first集
	void get_first_element(int symbol);//得到first集的每个元素
	void print_first(); //打印first集
	void get_follow(); //得到follow集
	void get_follow_element(int symbol); //得到follow集的每个元素
	void print_follow(); //打印follow集
	void get_table(); //得到预测分析表
	void add_error_table(); //增加错误处理
	void print_table(); //打印预测分析表
	void parse(std::string s); //分析程序
	void parse_string(std::string s); //打印字符串
	void print_parse(int pi, std::vector<std::string> s); //预处理分析程序中此时的字符串，主要是用dfa模型分析数字
};

