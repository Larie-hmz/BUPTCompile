#include<iostream>
#include<cstdio>
#include<fstream>
#include"scanner.h"
#include"dfa.h"

//#define buffer_len 1024

int main() {
	//双缓冲区读入文件

	std::string filename;
	std::cout << "情输入语法分析的文件路径" << std::endl;
	std::cin >> filename;

	scan.myfile.open(filename, std::ios::in);
	scan.init();
	dfa lexicial;
	lexicial.dfa_run();
	lexicial.print_static();
	lexicial.print_token();

	scan.myfile.close();
	

	return 0;
}