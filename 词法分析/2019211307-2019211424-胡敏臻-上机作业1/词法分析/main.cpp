#include<iostream>
#include<cstdio>
#include<fstream>
#include"scanner.h"
#include"dfa.h"

//#define buffer_len 1024

int main() {
	//˫�����������ļ�

	std::string filename;
	std::cout << "�������﷨�������ļ�·��" << std::endl;
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