#include<iostream>
#include<cstdio>
#include"grammar.h"
#include"LL1.h"

int main() {
	
	LL1 model1;
	model1.get_table();
	//model1.print_table();

	std::string waits;
	std::cout << "������Ҫʶ����ַ���\n";
	std::cin >> waits;
	model1.parse(waits);

	return 0;
}