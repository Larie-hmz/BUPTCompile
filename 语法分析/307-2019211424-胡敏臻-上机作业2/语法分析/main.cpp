#include<iostream>
#include<cstdio>
#include"grammar.h"
#include"LL1.h"

int main() {
	
	LL1 model1;
	model1.get_table();
	//model1.print_table();

	std::string waits;
	std::cout << "请输入要识别的字符串\n";
	std::cin >> waits;
	model1.parse(waits);

	return 0;
}