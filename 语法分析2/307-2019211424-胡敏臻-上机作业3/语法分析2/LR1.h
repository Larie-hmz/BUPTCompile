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
		int lefti, rightj;  //����ķ���������ұ�
		int dotPos;         //��¼���λ��
		std::vector<std::string> tail;   //��¼Сβ��
	};

	struct State
	{
		int serial; //���
		std::vector<Item> items;           //��¼��ϵʽ
		std::unordered_map<std::string, int> trans;  //ת�ƹ�ϵ
	};

	std::vector<State> states;    //��¼������Ŀ���淶��
	std::vector<std::vector<std::string>> reduces{{"1","2","3"},{"4","5","6"},{"7","8"},{"0"}}; //��¼��Լ��ı��
	std::vector<std::vector<std::string>> Action;  //Action������
	std::vector<std::vector<std::string>> Goto;    //Goto������
	grammar gra;
	int count = 0;

	std::vector<int> s_states; //״̬ջ
	std::vector<std::string> s_symbols; //�ַ�ջ
	std::vector<std::string> parse_s; //�����ַ���

public:
	auto my_find(std::vector<Item>::iterator beg, std::vector<Item>::iterator end, int pos); //�ҵ��Ƿ��Ѵ���item
	int is_ter(std::string a); //�ж��ս��
	int is_unter(std::string a); //�жϷ��ս��
	void extension_grammar(); //��չ�ķ�
	void init_i0();  //��ʼ����һ��״̬
	void get_items(std::vector<Item>& items, Item item); //�õ�ÿ��״̬������Ŀ��
	void get_closure(std::vector<std::string>& sstring, std::vector<std::string>& first); //��first�հ�
	void find_after(std::vector<Item>& items,std::vector<std::string>& after); //�ҵ���Ҫת�Ƶ����
	int is_same_items(std::vector<Item>& items, std::vector<State>& state);  //����״̬��state���Ƿ����
	void get_states(); //����״̬
	void push_dot(std::vector<Item> old_item, std::vector<Item>& new_item, std::string a); //����ƶ����״̬
	void get_table();//���������
	void test_print_items(std::vector<Item>& items);
	void test_print_states(std::vector<State>& states);
	void test_print_table();

	void parse_string(std::string s); //Ԥ�����ַ���
	void parse(std::string w); //�����ַ���
	void print_process(int ip); //��ӡ����

};

