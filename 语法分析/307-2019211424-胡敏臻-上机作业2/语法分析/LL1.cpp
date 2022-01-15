#include "LL1.h"

void LL1::init() {
	//Gra.read_grammer();
	//Gra.test_print_grammar();
	Gra.delete_left_recur();
	//Gra.test_print_grammar();
	len_non = Gra.non_ter.size();
	len_ter = Gra.terminal.size();
	first.resize(len_non);
	follow.resize(len_non);
	has_first.resize(len_non);
	has_follow.resize(len_non);
	include_of.resize(len_non);
	for (int i = 0; i < len_non; i++) {
		has_first[i] = 0;
	}
	for (int i = 0; i < len_non; i++) {
		has_follow[i] = 0;
	}
	for (int i = 0; i < len_non; i++) {
		include_of[i].resize(len_non);
	}
}

void LL1::get_first() {
	init();
	for (int i = 0; i < len_non; i++) {
		if (has_first[i] != 0) {
			continue;
		}
		get_first_element(i);
	}
}

void LL1::get_first_element(int symbol) {
	int i = symbol;
	for (int j = 0; j < Gra.all_gra[i].size(); j++) { //�����������ÿһ������ʽ
		if (find(Gra.terminal.begin(), Gra.terminal.end(), Gra.all_gra[i][j][0]) != Gra.terminal.end()) { //��һ�������ս��
			if (find(first[i].begin(), first[i].end(), Gra.all_gra[i][j][0]) == first[i].end()) { //���first����û�������
				first[i].push_back(Gra.all_gra[i][j][0]);
				sort(first[i].begin(), first[i].end());
			}
		}
		else {//����һλ�Ƿ��ս��ʱ
			std::vector<std::string> s = Gra.all_gra[i][j];//sΪ��ǰ����ʽ
			std::vector<std::string> temps_u;
			std::vector<std::string> temps_k;
			for (int k = 0; k < s.size(); k++) { //����ĳһ������ʽ
				if (find(Gra.terminal.begin(), Gra.terminal.end(), s[k]) != Gra.terminal.end()) {//������ս��,��ֱ���˳�
					if (find(first[i].begin(), first[i].end(), s[k]) == first[i].end()) { //���first����û�������
						first[i].push_back(Gra.all_gra[i][j][0]);
						sort(first[i].begin(), first[i].end());
					}
					break;
				}
				int pk = std::distance(Gra.non_ter.begin(), find(Gra.non_ter.begin(), Gra.non_ter.end(), s[k])); //s[k]�ڷ��ս���е��±�
				if (has_first[pk] != 0) { //������Ѿ��������
					temps_k = first[pk];
					//�����е�������
					std::set_union(first[i].begin(), first[i].end(), first[pk].begin(), first[pk].end(), std::back_inserter(temps_u));
					first[i] = temps_u;
					if (find(temps_k.begin(), temps_k.end(), "epsilon") == temps_k.end()) { //���������������ռ������˳�
						break;
					}
					else if (k == s.size() - 1) { //��������ռ����Ǳ��ʽ���һλ
						if (find(first[i].begin(), first[i].end(), "epsilon") == first[i].end()) { //�ж���û�пռ���û�������
							first[i].push_back("epsilon");
							sort(first[i].begin(), first[i].end());
						}
					}
				}
				else { //��δ�������
					get_first_element(pk);
					k--;
				}
			}
		}
	}
	has_first[symbol] = 1;
}

void LL1::print_first() {
	for (int i = 0; i < len_non; i++) {
		std::cout << "first[" << Gra.non_ter[i] << "]:";
		for (int j = 0; j < first[i].size(); j++) {
			std::cout << " " << first[i][j] << " ";
		}
		std::cout << "\n";
	}
}

//����follow��
void LL1::get_follow() {
	get_first();
	int pi = std::distance(Gra.non_ter.begin(), find(Gra.non_ter.begin(), Gra.non_ter.end(), Gra.S));
	follow[pi].push_back("$");
	for (int i = 0; i < len_non; i++) { //����ÿ�����ս��
		if (has_follow[i] != 0) {
			continue;
		}
		get_follow_element(i);
	}
	for (int i = 0; i < len_non; i++) {
		auto it = find(follow[i].begin(), follow[i].end(), "epsilon");
		if (it != follow[i].end()) {
			follow[i].erase(it);
		}
	}
}

void LL1::get_follow_element(int symbol) {
	int i = symbol;
	for (int j = 0; j < len_non; j++) {
		for (int k = 0; k < Gra.all_gra[j].size(); k++) {
			auto pi = Gra.all_gra[j][k].begin();
			pi = find(pi, Gra.all_gra[j][k].end(), Gra.non_ter[i]);//���Ƿ��е�ǰ�ķ��ս��
			while (pi != Gra.all_gra[j][k].end()) {
				//pi = find(pi, Gra.all_gra[j][k].end(), Gra.non_ter[i]);//���Ƿ��е�ǰ�ķ��ս��
				if (pi != Gra.all_gra[j][k].end()) {
					pi++;
					//�����ʱ�����һ��
					if (pi == Gra.all_gra[j][k].end()) { 
						//follow[j]��follow[i]������
						if (has_follow[j] == 0) {
							if (include_of[i][j] == 1 && include_of[j][i] == 1) { //����ݹ����
								std::vector<std::string> temps_u;
								std::set_union(follow[j].begin(), follow[j].end(), follow[i].begin(), follow[i].end(), std::back_inserter(temps_u));
								follow[i] = temps_u;
								follow[j] = temps_u;
							}
							else {
								include_of[i][j] = 1;
								get_follow_element(j);
							}
							
						}
						if (has_follow[j] != 0) {
							std::vector<std::string> temps_u;
							std::set_union(follow[j].begin(), follow[j].end(), follow[i].begin(), follow[i].end(), std::back_inserter(temps_u));
							follow[i] = temps_u;
						}
					}
					//��һ��Ϊ���ս��
					else if (find(Gra.non_ter.begin(), Gra.non_ter.end(), *pi) != Gra.non_ter.end()) { 
						int pt = distance(Gra.non_ter.begin(),find(Gra.non_ter.begin(), Gra.non_ter.end(), *pi));
						//first[j]��follow[i]������
						std::vector<std::string> temps_u;
						std::set_union(first[pt].begin(), first[pt].end(), follow[i].begin(), follow[i].end(), std::back_inserter(temps_u));
						follow[i] = temps_u;
						//�����ս�����п�
						if (find(first[pt].begin(), first[pt].end(), "epsilon") != first[pt].end()) {
							//pi++;
						}
						else {
							pi = find(pi, Gra.all_gra[j][k].end(), Gra.non_ter[i]);
						}
					}
					//��һ��Ϊ�ս��
					else { 
						if (find(follow[i].begin(), follow[i].end(), *pi) == follow[i].end()) {
							follow[i].push_back(*pi);
							sort(follow[i].begin(), follow[i].end());
						}
						pi = find(pi, Gra.all_gra[j][k].end(), Gra.non_ter[i]);
					}
				}
			}

		}
	}
	has_follow[i] = 1;
}

void LL1::print_follow() {
	for (int i = 0; i < len_non; i++) {
		std::cout << "follow[" << Gra.non_ter[i] << "]:";
		for (int j = 0; j < follow[i].size(); j++) {
			std::cout << " " << follow[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void LL1::get_table() {
	get_follow();
	table.resize(len_non);
	//�޸��ս���� ���ո�Ϊ$
	auto it = find(Gra.terminal.begin(), Gra.terminal.end(), "epsilon");
	if (it == Gra.terminal.end()) {
		Gra.terminal.push_back("$");
	}
	else {
		Gra.terminal.erase(it);
		Gra.terminal.push_back("$");
	}
	int lenter = Gra.terminal.size();
	for (int i = 0; i < len_non; i++) {
		table[i].resize(lenter);
	}
	for (int i = 0; i < len_non; i++) {
		for (int j = 0; j < Gra.all_gra[i].size(); j++) {
			for (int k = 0; k < Gra.all_gra[i][j].size(); k++) {
				std::string s = Gra.all_gra[i][j][k];
				//���Ϊ�գ����ռ���follow[i]
				if (s == "epsilon") {
					for (int m = 0; m < follow[i].size(); m++) {
						auto pf = find(Gra.terminal.begin(), Gra.terminal.end(), follow[i][m]);
						int dpf = std::distance(Gra.terminal.begin(), pf);
						table[i][dpf] = Gra.all_gra[i][j];
					}
					break;
				}
				//������ս��
				else if (find(Gra.terminal.begin(), Gra.terminal.end(), s) != Gra.terminal.end()) { 
					int pi = distance(Gra.terminal.begin(), find(Gra.terminal.begin(), Gra.terminal.end(), s));
					table[i][pi] = Gra.all_gra[i][j];
					break;
				}
				//����Ƿ��ս��
				else {
					auto pf = find(Gra.non_ter.begin(), Gra.non_ter.end(), s);
					int dpf = std::distance(Gra.non_ter.begin(), pf);
					int flag = 0;
					for (int m = 0; m < first[dpf].size(); m++) {
						if (first[dpf][m] == "epsilon") {
							flag = 1;
						}
						else {
							int pi = distance(Gra.terminal.begin(), find(Gra.terminal.begin(), Gra.terminal.end(), first[dpf][m]));
							table[i][pi] = Gra.all_gra[i][j];
						}
					}
					if (flag == 0) {
						break;
					}
				}
			}
		}
	}
	add_error_table();
}

//���Ӵ�����
void LL1::add_error_table() {
	for (int i = 0; i < len_non; i++) {
		for (int j = 0; j < follow[i].size(); j++) {
			if (table[i][j].size() == 0) {
				table[i][j].push_back("synch");
			}
		}
	}
}

void LL1::print_table() {
	int lenter = Gra.terminal.size();
	std::cout << "\t";
	for (int i = 0; i < lenter; i++) {
		std::cout << Gra.terminal[i] << "\t";
	}
	std::cout << "\n";
	for (int i = 0; i < len_non; i++) {
		std::cout << Gra.non_ter[i] << "\t";
		for (int j = 0; j < lenter; j++) {
			if (table[i][j].size()!=0) {
				if (table[i][j][0] == "synch") {
					std::cout << table[i][j][0];
				}
				else {
					std::cout << Gra.non_ter[i] << "->";
					for (int k = 0; k < table[i][j].size(); k++) {
						std::cout << table[i][j][k];
					}
				}

			}
			std::cout << "\t";
		}
		std::cout << "\n";
	}
}

void LL1::parse(std::string s) {
	pre_stack.push_back("$");
	pre_stack.push_back(Gra.S);
	s += "$";
	parse_string(s);
	int len = parse_s.size();
	int ip = 0;
	std::string topx;
	std::string tempa;
	do {
		topx = pre_stack.back();
		tempa = parse_s[ip];
		auto terp = find(Gra.terminal.begin(), Gra.terminal.end(), topx);
		int terni = std::distance(Gra.non_ter.begin(), find(Gra.non_ter.begin(), Gra.non_ter.end(), topx));
		int terai = std::distance(Gra.terminal.begin(), find(Gra.terminal.begin(), Gra.terminal.end(), tempa));
		if (tempa[0]=='0') {
			terai = std::distance(Gra.terminal.begin(), find(Gra.terminal.begin(), Gra.terminal.end(), "num"));
		}
		print_parse(ip, parse_s);
		if (terp != Gra.terminal.end() || topx == "$") {
			if (topx == tempa) {
				pre_stack.pop_back();
				ip++;
				std::cout << "ƥ��ɹ�\n";
			}
			else if (topx == "num" && tempa[0]=='0') {
				pre_stack.pop_back();
				ip++;
				std::cout << "ƥ��ɹ�\n";
			}
			else {
				std::cout << "error!������һ�ַ�\n";
				//break;
				ip++;
			}
		}
		else {
			if (table[terni][terai].size() != 0) {
				pre_stack.pop_back();
				if (table[terni][terai][0] == "synch") {
					std::cout << "error!�ַ���ջ����\n";
					
				}
				else {
					if (table[terni][terai][0] != "epsilon") {
						for (int i = table[terni][terai].size() - 1; i >= 0; i--) {
							pre_stack.push_back(table[terni][terai][i]);
						}
					}
					std::cout << Gra.non_ter[terni] << "->";
					for (int i = 0; i < table[terni][terai].size(); i++) {
						std::cout << table[terni][terai][i];
					}
					std::cout << "\n";
				}

			}
			else {
				std::cout << "error!������һ�ַ�\n";
				ip++;
				//break;
			}
		}
		//std::cout << "\n";
	} while (topx != "$" && ip < len);
}

void LL1::print_parse(int pi, std::vector<std::string> s) {
	for (int i = 0; i < pre_stack.size(); i++) {
		std::cout << pre_stack[i];
	}
	std::cout << "       ";
	for (int i = pi; i < s.size(); i++) {
		if (s[i][0] == '0') {
			s[i].erase(s[i].begin());
		}
		std::cout << s[i];
	}
	std::cout << "       ";

}

//Ԥ������������д�ʱ���ַ�������Ҫ����dfaģ�ͷ�������
void LL1::parse_string(std::string s) {
	int state = 0;
	int ip = 0;
	int len_s = s.size();
	std::string temps;
	while (ip < len_s) {
		switch (state)
		{
		case 0:
			temps = "0";
			if (s[ip] == '+' || s[ip] == '-' || s[ip] == '*' || s[ip] == '/' || s[ip] == '(' || s[ip] == ')'||s[ip]=='$') {
				temps = s[ip];
				parse_s.push_back(temps);
				state = 0;
				ip++;
			}
			else if (isdigit(s[ip])) {
				temps += s[ip];
				state = 1;
				ip++;
			}
			break;
		case 1:
			if (isdigit(s[ip])) {
				temps += s[ip];
				state = 1;
				ip++;
			}
			else if (s[ip] == 'E' || s[ip] == 'e') {
				temps += s[ip];
				state = 4;
				ip++;
			}
			else if (s[ip] == '.') {
				temps += s[ip];
				state = 2;
				ip++;
			}
			else {
				parse_s.push_back(temps);
				state = 0;
			}
			break;
		case 2:
			if (isdigit(s[ip])) {
				temps += s[ip];
				state = 3;
				ip++;
			}
			break;
		case 3:
			if (isdigit(s[ip])) {
				temps += s[ip];
				state = 3;
				ip++;
			}
			else if (s[ip] == 'E' || s[ip] == 'e') {
				temps += s[ip];
				state = 4;
				ip++;
			}
			else {
				parse_s.push_back(temps);
				state = 0;
			}
			break;
		case 4:
			if (isdigit(s[ip])) {
				temps += s[ip];
				state = 6;
				ip++;
			}
			else if (s[ip] == '+' || s[ip] == '-') {
				temps += s[ip];
				state = 5;
				ip++;
			}
			break;
		case 5:
			if (isdigit(s[ip])) {
				temps += s[ip];
				state = 6;
				ip++;
			}
			break;
		case 6:
			if (isdigit(s[ip])) {
				temps += s[ip];
				state = 6;
				ip++;
			}
			else {
				parse_s.push_back(temps);
				state = 0;
			}
			break;
		default:
			std::cout<< "error";
			break;
		}
	}
}