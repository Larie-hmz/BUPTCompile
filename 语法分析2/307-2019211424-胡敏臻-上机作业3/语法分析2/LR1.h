#pragma once
#include"grammar.h"
#include<map>
#include<unordered_map>
#include<stack>
#include<iomanip>

class LR1
{
	struct Item
	{
		int lefti, rightj;  //标记文法的左边与右边
		int dotPos;         //记录点的位置
		std::vector<std::string> tail;   //记录小尾巴
	};

	struct State
	{
		int serial; //序号
		std::vector<Item> items;           //记录关系式
		std::unordered_map<std::string, int> trans;  //转移关系
	};

	std::vector<State> states;    //记录所有项目集规范族
	std::vector<std::vector<std::string>> reduces{{"1","2","3"},{"4","5","6"},{"7","8"},{"0"}}; //记录待约项的编号
	std::vector<std::vector<std::string>> Action;  //Action分析表
	std::vector<std::vector<std::string>> Goto;    //Goto分析表
	grammar gra;
	int count = 0;

	std::vector<int> s_states; //状态栈
	std::vector<std::string> s_symbols; //字符栈
	std::vector<std::string> parse_s; //分析字符串

public:
	auto my_find(std::vector<Item>::iterator beg, std::vector<Item>::iterator end, int pos); //找到是否已存在item
	int is_ter(std::string a); //判断终结符
	int is_unter(std::string a); //判断非终结符
	void extension_grammar(); //扩展文法
	void init_i0();  //初始化第一个状态
	void get_items(std::vector<Item>& items, Item item); //得到每个状态集的项目集
	void get_closure(std::vector<std::string>& sstring, std::vector<std::string>& first); //求first闭包
	void find_after(std::vector<Item>& items,std::vector<std::string>& after); //找到需要转移的情况
	int is_same_items(std::vector<Item>& items, std::vector<State>& state);  //看此状态在state中是否包含
	void get_states(); //计算状态
	void push_dot(std::vector<Item> old_item, std::vector<Item>& new_item, std::string a); //求解移动点的状态
	void get_table();//构造分析表
	void test_print_items(std::vector<Item>& items);
	void test_print_states(std::vector<State>& states);
	void test_print_table();

	void parse_string(std::string s); //预处理字符串
	void parse(std::string w); //分析字符串
	void print_process(int ip); //打印过程

};

