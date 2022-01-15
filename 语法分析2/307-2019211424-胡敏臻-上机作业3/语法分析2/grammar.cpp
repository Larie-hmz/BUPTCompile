#include "grammar.h"

//初始化
grammar::grammar() {
	S = "E";
	terminal = { "+", "-", "*", "/", "(", ")", "num" };
	non_ter = { "E", "T", "F" };
	all_gra.resize(non_ter.size());
	all_gra[0].resize(3);
	all_gra[0][0] = { "E","+","T" };
	all_gra[0][1] = { "E","-","T" };
	all_gra[0][2] = { "T" };
	all_gra[1].resize(3);
	all_gra[1][0] = { "T","*","F" };
	all_gra[1][1] = { "T","/","F" };
	all_gra[1][2] = { "F" };
	all_gra[2].resize(2);
	all_gra[2][0] = { "(","E",")" };
	all_gra[2][1] = { "num" };
	len_non = non_ter.size();
	len_ter = terminal.size();
	first.resize(len_non);
	follow.resize(len_non);
}

void grammar::test_print_grammar() {
	for (int i = 0; i < all_gra.size(); i++) {
		for (int j = 0; j < all_gra[i].size(); j++) {
			if (j == 0) {
				std::cout << non_ter[i] << "->";
			}
			else {
				std::cout << "|";
			}
			for (int k = 0; k < all_gra[i][j].size(); k++) {
				std::cout << all_gra[i][j][k];
			}
		}
		std::cout << "\n";
	}
}

//读取文法
void grammar::read_grammer() {
	std::cout << "请输入开始符号\n";
	std::cin >> S;
	std::cout << "请输入非终结符个数及非终结符\n";
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		std::string s;
		std::cin >> s;
		non_ter.push_back(s);
	}
	std::cout << "请输入终结符个数及终结符\n";
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		std::string s;
		std::cin >> s;
		terminal.push_back(s);
	}
	std::cout << "请输入产生式行数及产生式 产生式以#结尾\n";
	std::cin >> n;
	all_gra.resize(non_ter.size());
	for (int i = 0; i < n; i++) {
		std::string s;
		std::cin >> s;
		std::vector<std::string> temps;
		int pi = std::distance(non_ter.begin(), find(non_ter.begin(), non_ter.end(), s));
		std::cin >> s; std::cin >> s;
		while (s != "#") {
			if (s != "|") {
				temps.push_back(s);
			}
			else {
				all_gra[pi].push_back(temps);
				temps.clear();
			}
			std::cin >> s;
		}
		all_gra[pi].push_back(temps);
	}
}


void grammar::get_first() {
	first[0] = { "(","num" };
	first[1] = { "(","num" };
	first[2] = { "(","num" };
}


void grammar::print_first() {
	for (int i = 0; i < len_non; i++) {
		std::cout << "first[" <<  non_ter[i] << "]:";
		for (int j = 0; j < first[i].size(); j++) {
			std::cout << " " << first[i][j] << " ";
		}
		std::cout << "\n";
	}
}

//计算follow集
void grammar::get_follow() {
	follow[0] = { "+","-",")","$" };
	follow[1] = { "*","/","+","-",")","$" };
	follow[2] = { "*","/","+","-",")","$" };
}


void grammar::print_follow() {
	for (int i = 0; i < len_non; i++) {
		std::cout << "follow[" <<  non_ter[i] << "]:";
		for (int j = 0; j < follow[i].size(); j++) {
			std::cout << " " << follow[i][j] << " ";
		}
		std::cout << "\n";
	}
}
