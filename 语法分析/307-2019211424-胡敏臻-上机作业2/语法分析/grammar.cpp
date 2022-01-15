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

//消除左递归
void grammar::delete_left_recur() {
	std::string temps;
	int n = all_gra.size();
	int flag = 0;
	for (int i = 0; i < n ; i++) {
		temps = non_ter[i];
		flag = 0;
		for (int j = 0; j < all_gra[i].size(); j++) {
			if (all_gra[i][j][0] == temps) {
				flag = 1;
				non_ter.push_back(temps+'\'');
				break;
			}
		}
		if (flag == 1) {
			int newn = non_ter.size();
			all_gra.resize(newn);
			int tempn = all_gra[i].size();
			for (int j = 0; j < all_gra[i].size(); j++) {
				if (all_gra[i][j][0] == temps) {
					all_gra[i][j].erase(all_gra[i][j].begin());
					all_gra[i][j].push_back(non_ter[newn - 1]);
					all_gra[newn-1].push_back(all_gra[i][j]);
					all_gra[i].erase(all_gra[i].begin() + j);
					j--;
				}
				else {
					all_gra[i][j].push_back(non_ter[newn - 1]);
				}
			}
			if (find(terminal.begin(), terminal.end(), "epsilon")==terminal.end()) {
				terminal.push_back("epsilon");
			}
			std::vector<std::string> tempss;
			tempss.push_back("epsilon");
			all_gra[newn - 1].push_back(tempss);
		}
	}
}
