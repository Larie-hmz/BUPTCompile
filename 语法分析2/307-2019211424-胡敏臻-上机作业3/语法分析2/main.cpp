#include<iostream>
#include<cstdio>
#include"grammar.h"
#include"LR1.h"

int main() {

	LR1 lr1;
	lr1.get_states();
	lr1.get_table();

	std::string w;
	std::cout << "请输入要规约的字符串\n";
	std::cin >> w;
	lr1.parse(w);

	return 0;
}