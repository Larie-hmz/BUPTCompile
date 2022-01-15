#include "LR1.h"


void LR1::extension_grammar() {
	gra.S = "E'";
	int len = gra.all_gra.size();
	gra.all_gra.resize(len + 1);
	gra.all_gra[len].resize(1);
	gra.all_gra[len][0] = { "E"};
	gra.non_ter.push_back("E'");
	gra.terminal.push_back("$");
}


auto LR1::my_find(std::vector<Item>::iterator beg, std::vector<Item>::iterator end, int pos) {
	auto i = beg;
	for (i; i != end; i++) {
		if ((*i).lefti == pos && (*i).dotPos == 0) {
			return i;
		}
	}
	return end;
}


//������ս������λ�ã�������Ƿ���-1
int LR1::is_ter(std::string a) {
	auto it = find(gra.terminal.begin(), gra.terminal.end(), a);
	if (it == gra.terminal.end()) { //��������ս��������-1
		return -1;
	}
	return distance(gra.terminal.begin(), it);
}

//����Ƿ��ս������λ�ã�������Ƿ���-1
int LR1::is_unter(std::string a) {
	auto it = find(gra.non_ter.begin(), gra.non_ter.end(), a);
	if (it == gra.non_ter.end()) { //������Ƿ��ս��������-1
		return -1;
	}
	return distance(gra.non_ter.begin(), it);
}


void LR1::init_i0() {
	gra.get_first();
	gra.get_follow();
	extension_grammar();
	Item item;
	item.lefti= gra.all_gra.size()-1;
	item.rightj = 0;
	item.dotPos = 0;
	item.tail.push_back( "$");
	std::vector<Item> items;
	items.push_back(item);
	for (int i = 0; i < items.size(); i++) {
		get_items(items, items[i]);
	}
	//test_print_items(items);
	State state0;
	state0.items = items;
	state0.serial = count;
	states.push_back(state0);
}

void LR1::get_items(std::vector<Item>& items,Item item) {
	if (item.dotPos >= gra.all_gra[item.lefti][item.rightj].size()) {  //����Ǵ�Լ��Ŀ
		return;
	}
	std::string after = gra.all_gra[item.lefti][item.rightj][item.dotPos];
	if (is_ter(after) != -1){  //������ս��
		return;
	}
	else {  //����Ƿ��ս��
		auto it = find(gra.non_ter.begin(), gra.non_ter.end(), after);
		int pos=distance(gra.non_ter.begin(), it);
		if (item.dotPos + 1 == gra.all_gra[item.lefti][item.rightj].size()) {  //��Լ֮��Ϊ�գ��̳�Сβ��
			//auto pitem = find(items.begin(), items.end(), [&](Item A)-> bool {return A.lefti == pos && A.dotPos == 0; }); 
			auto pitem = my_find(items.begin(), items.end(), pos);
			if (pitem == items.end()) { ////�����item��û���ֹ�
				for (int i = 0; i < gra.all_gra[pos].size(); i++) {
					Item temp_item;
					temp_item.lefti = pos;
					temp_item.rightj = i;
					temp_item.dotPos = 0;
					temp_item.tail = item.tail;
					items.push_back(temp_item);
				}
			}
			else { //����Ѿ����ֹ���,����ʱ��β����û�м���
				if (pitem != items.end()) {
					int posi = distance(items.begin(), pitem);
					auto pitem2 = pitem;
					while (pitem2 != items.end()) {    //����������ֵĲ���ʽ
						int pos2 = distance(items.begin(), pitem2);
						for (int k = 0; k < item.tail.size(); k++) {
							if (find(items[pos2].tail.begin(), items[pos2].tail.end(), items[pos2].tail[k]) == items[posi].tail.end()) {
								items[pos2].tail.push_back(item.tail[k]);
							}
						}
						sort(items[pos2].tail.begin(), items[pos2].tail.end());
						//pitem2 = find(++pitem2, items.end(), [&](Item A)-> bool {return A.lefti == pos && A.dotPos == 0; });
						pitem2 = my_find(++pitem2, items.end(), pos);
					}
					//pitem = find(++pitem, items.end(), [&](Item A)-> bool {return A.lefti == pos && A.dotPos == 0; });
					//pitem = my_find(++pitem, items.end(), pos);
				}
			}
		}
		else {  //��֮���first�հ�  //��Լ֮��Ϊ��
			std::vector<std::string> tfirst;
			std::vector<std::string> tstring(gra.all_gra[item.lefti][item.rightj].begin() + item.dotPos + 1, gra.all_gra[item.lefti][item.rightj].end());
			get_closure(tstring, tfirst);
			//auto pitem = find(items.begin(), items.end(), [&](Item A)-> bool {return A.lefti == pos && A.dotPos == 0; });
			auto pitem = my_find(items.begin(), items.end(), pos);
			if (pitem == items.end()) { ////�����item��û���ֹ�
				for (int i = 0; i < gra.all_gra[pos].size(); i++) {
					Item temp_item;
					temp_item.lefti = pos;
					temp_item.rightj = i;
					temp_item.dotPos = 0;
					int flag = 0;//���first�Ƿ��п�
					for (int j = 0; j < tfirst.size(); j++) {
						if (tfirst[j] == "epsilon") {
							flag = 1;
						}
						else {
							temp_item.tail.push_back(tfirst[j]);
						}
					}
					if (flag == 1) {  //���п�
						for (int k = 0; k < item.tail.size(); k++) {
							if (find(temp_item.tail.begin(), temp_item.tail.end(), temp_item.tail[i]) == temp_item.tail.end()) {
								temp_item.tail.push_back(item.tail[i]);
							}
						}
					}
					sort(temp_item.tail.begin(), temp_item.tail.end());
					items.push_back(temp_item);
				}
			}
			else {    //����Ѿ����ֹ�
				if (pitem != items.end()) {
					int posi = distance(items.begin(), pitem);
					auto pitem2 = my_find(items.begin(), items.end(), pos);
					while (pitem2 != items.end()) {    //����������ֵĲ���ʽ
						int pos2 = distance(items.begin(), pitem2);
						int flag = 0;//���first�Ƿ��п�
						for (int j = 0; j < tfirst.size(); j++) {
							if (tfirst[j] == "epsilon") {
								flag = 1;
							}
							else {
								if (find(items[pos2].tail.begin(), items[pos2].tail.end(), tfirst[j]) == items[pos2].tail.end()) {
									items[pos2].tail.push_back(tfirst[j]);
								}
							}
						}
						if (flag == 1) {  //���п�
							for (int k = 0; k < item.tail.size(); k++) {
								if (find(items[pos2].tail.begin(), items[pos2].tail.end(), items[pos2].tail[k]) == items[posi].tail.end()) {
									items[pos2].tail.push_back(item.tail[k]);
								}
							}
						}
						sort(items[pos2].tail.begin(), items[pos2].tail.end());
						//pitem2 = find(++pitem2, items.end(), [&](Item A)-> bool {return A.lefti == pos && A.dotPos == 0; });
						pitem2 = my_find(++pitem2, items.end(), pos);
					}
					//pitem = find(++pitem, items.end(), [&](Item A)-> bool {return A.lefti == pos && A.dotPos == 0; });
					//pitem = my_find(++pitem, items.end(), pos);
				}
			}
		}
	}

}

//��first�հ�
void LR1::get_closure(std::vector<std::string>& sstring , std::vector<std::string>& first) {
	int flag = 0;
	for (int i = 0; i < sstring.size(); i++) {
		if (is_ter(sstring[i]) != -1) { //������ս��
			first.push_back(sstring[i]);
			return;
		}
		else {   //����Ƿ��ս��
			auto it=find(gra.non_ter.begin(), gra.non_ter.end(), sstring[i]) ;
			int pos = distance(gra.terminal.begin(), it);
			flag = 0;  //����Ƿ��п�
			for (int j = 0; j < gra.first[pos].size(); j++) {
				if (gra.first[pos][i] == "epsilon") {
					flag = 1;
				}
				first.push_back(gra.first[pos][j]);
			}
			if (flag == 0) {
				return;
			}
		}
	}
	if (flag == 1) {
		first.push_back("epsilon");
	}
}

//���ҵ�֮����ַ�
void LR1::find_after(std::vector<Item>& items, std::vector<std::string>& after) {
	for (int i = 0; i < items.size(); i++) {
		if (items[i].dotPos < gra.all_gra[items[i].lefti][items[i].rightj].size()) {
			std::string temp = gra.all_gra[items[i].lefti][items[i].rightj][items[i].dotPos];
			if (find(after.begin(), after.end(), temp) == after.end()) {
				after.push_back(temp);
			}
		}
	}
}

//����״̬��state���Ƿ����
//-1��ʶ������ �������ֱ�ʶ���ص�state��
int LR1::is_same_items(std::vector<Item>& items, std::vector<State>& state) {
	for (int i = 0; i < state.size(); i++) {
		if (state[i].items.size() == items.size()) {
			int j;
			for (j = 0; j < items.size(); j++) {
				if (!(state[i].items[j].lefti == items[j].lefti && state[i].items[j].rightj == items[j].rightj
					&& state[i].items[j].tail == items[j].tail && state[i].items[j].dotPos == items[j].dotPos)) {
					break;
				}
			}
			if (j == items.size()) {
				return i;
			}
		}
	}
	return -1;
}

void LR1::get_states() {
	init_i0();
	for (int i = 0; i < states.size(); i++) {
		std::vector<std::string> after;
		find_after(states[i].items, after);   //�ҵ�֮�����ת�����ַ�
		for (int j = 0; j < after.size(); j++) { //����ת���ַ�
			std::vector<Item> new_items;
			push_dot(states[i].items, new_items, after[j]); //�ƶ����γ��µ�items
			for (int k = 0; k < new_items.size(); k++) { //�����ܵ��µ�items
				get_items(new_items, new_items[k]);
			}
			int flag = is_same_items(new_items, states);
			if (flag == -1) {   //�����ʱû����ͬ��
				count++;
				State astate;
				astate.items=new_items;
				astate.serial = count;
				states.push_back(astate);
				states[i].trans[after[j]] = count;
			}
			else {
				states[i].trans[after[j]] = flag;
			}
		}
		std::cout << "I" << i << "\n";
		test_print_items(states[i].items);
	}
}

//����ƶ����״̬
void LR1:: push_dot(std::vector<Item> old_item, std::vector<Item>& new_item, std::string a) {
	for (int i = 0; i < old_item.size(); i++) {
		if (old_item[i].dotPos < gra.all_gra[old_item[i].lefti][old_item[i].rightj].size()) {
			if (gra.all_gra[old_item[i].lefti][old_item[i].rightj][old_item[i].dotPos] == a) {
				Item item;
				item.lefti = old_item[i].lefti;
				item.rightj = old_item[i].rightj;
				item.tail = old_item[i].tail;
				item.dotPos = old_item[i].dotPos + 1;
				new_item.push_back(item);
			}
		}
	}
}

void LR1::test_print_items(std::vector<Item>& items) {
	for (int i = 0; i < items.size(); i++) {
		std::cout << gra.non_ter[items[i].lefti] << "->";
		for (int j = 0; j < gra.all_gra[items[i].lefti][items[i].rightj].size(); j++) {
			if (j == items[i].dotPos) {
				std::cout << ".";
			}
			std::cout << gra.all_gra[items[i].lefti][items[i].rightj][j];
		}
		if (items[i].dotPos == gra.all_gra[items[i].lefti][items[i].rightj].size()) {
			std::cout << ".";
		}
		std::cout << "\t\t";
		for (int j = 0; j < items[i].tail.size(); j++) {
			std::cout << items[i].tail[j] << " ";
		}
		std::cout << "\n";
	}
}

void LR1::test_print_states(std::vector<State>& states) {
	for (int i = 0; i < states.size(); i++) {
		test_print_items(states[i].items);
	}
}

void LR1::test_print_table() {
	std::cout << "\t\t\t\tAction\t\t\t\t\t\tGoto\t\n";
	std::cout << "\t+\t-\t*\t/\t(\t)\tnum\t$\tE\tT\tF\n";
	for (int i = 0; i < states.size(); i++) {
		std::cout << i << "\t";
		for (int j = 0; j < Action[i].size(); j++) {
			std::cout << Action[i][j] << "\t";;
		}
		for (int j = 0; j < Goto[i].size(); j++) {
			std::cout << Goto[i][j] << "\t";
		}
		std::cout << "\n";
	}
}


//���������
void LR1::get_table() {
	Action.resize(states.size());
	Goto.resize(states.size());
	for (int i = 0; i < states.size(); i++) {
		Action[i].resize(gra.terminal.size());
		Goto[i].resize(gra.non_ter.size()-1);
		for (int j = 0; j < states[i].items.size(); j++) { //���ҹ�Լ��
			if (states[i].items[j].dotPos == gra.all_gra[states[i].items[j].lefti][states[i].items[j].rightj].size()) {
				if (states[i].items[j].lefti == 3 && states[i].items[j].rightj == 0) { //�����ʱ����չ��Ŀ
					Action[i][gra.terminal.size() - 1] = "ACC";
				}
				else {
					for (int k = 0; k < states[i].items[j].tail.size(); k++) {  //��Сβ���ڵĵط���Լ
						auto it = find(gra.terminal.begin(), gra.terminal.end(), states[i].items[j].tail[k]);
						if (it == gra.terminal.end()) {
							std::cout << "error!";
						}
						else {
							int pos = distance(gra.terminal.begin(), it);
							Action[i][pos] = "R"+(reduces[states[i].items[j].lefti][states[i].items[j].rightj]);
					
						}
					}
				}
			}
		}
		for (auto j = states[i].trans.begin(); j != states[i].trans.end(); j++) {
			std::string temp;
			temp = (*j).first;
			auto it = find(gra.terminal.begin(), gra.terminal.end(), temp);
			if (it != gra.terminal.end()) { //���ת�����ս��
				int pos = distance(gra.terminal.begin(), it);
				Action[i][pos] = "S" + std::to_string((*j).second);
			}
			else { // ���ת���Ƿ��ս��
				it = find(gra.non_ter.begin(), gra.non_ter.end(), temp);
				int pos = distance(gra.non_ter.begin(), it);
				Goto[i][pos] = std::to_string((*j).second);
			}
		}
	}
	test_print_table();
}

//Ԥ������������д�ʱ���ַ�������Ҫ����dfaģ�ͷ�������
//�ʼΪ0��ʾ������
void LR1::parse_string(std::string s) {
	int state = 0;
	int ip = 0;
	int len_s = s.size();
	std::string temps;
	while (ip < len_s) {
		switch (state)
		{
		case 0:
			temps = "0";
			if (s[ip] == '+' || s[ip] == '-' || s[ip] == '*' || s[ip] == '/' || s[ip] == '(' || s[ip] == ')' || s[ip] == '$') {
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
			else {
				std::cout << "wrong char!\n";
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
			std::cout << "error";
			break;
		}
	}
}

void LR1::parse(std::string w) {
	parse_string(w + "$");

	s_states.push_back(0);
	s_symbols.push_back("-");

	int s = 0;
	int ip = 0;
	std::string a;
	std::string action_str;
	do {
		print_process(ip);
		action_str = "";
		s = s_states[s_states.size()-1];
		a = parse_s[ip];
		if (a[0] == '0') {  //�����ʱ��num
			a = "num";
		}
		int pos = is_ter(a);
		if (pos == -1) {
			std::cout << "error!";
		}
		else {
			std::cout << std::setw(20);
			std::string temp = Action[s][pos];
			if (temp == "ACC") {
				action_str = "ACCEPT\n";
				std::cout << action_str;
				return;
			}
			else if (temp[0] == 'S') { //��ʱ��Ҫshift
				int t_state = 0;
				for (int i = 1; i < temp.size(); i++) {
					t_state = t_state * 10 + temp[i] - '0';
				}
				s_states.push_back(t_state);
				s_symbols.push_back(a);
				ip++;
				std::cout << "Shift " << t_state << "\n";
			}
			else if (temp[0] == 'R') { //��ʱ��Ҫ��Լ
				int t_re = 0;
				for (int i = 1; i < temp.size(); i++) {
					t_re = t_re * 10 + temp[i] - '0';
				}
				int pi = (t_re - 1) / 3;
				int pj = (t_re - 1) % 3;
				std::cout << "Reduce by " << gra.non_ter[pi] << "->";
				for (int i = 0; i < gra.all_gra[pi][pj].size(); i++) {
					std::cout << gra.all_gra[pi][pj][i];
					s_states.pop_back();
					s_symbols.pop_back();
				}
				std::cout << "\n";
				int pos1 = s_states[s_states.size() - 1];
				std::string tempc = gra.non_ter[pi];
				s_symbols.push_back(tempc);
				int pos2 = is_unter(tempc);
				if (pos2 == -1) {
					std::cout << "Error!";
					return;
				}
				else {
					int t_state = 0;
					for (int j = 0; j < Goto[pos1][pos2].size(); j++) {
						t_state = t_state * 10 + Goto[pos1][pos2][j] - '0';
					}
					s_states.push_back(t_state);
				}

			}
			else {
				std::cout << "Error!\n";
				return;
			}
		}
	} while (1);
}

void LR1::print_process(int ip) {
	for (int i = 0; i < s_states.size(); i++) {
		std::cout << std::setw(2) << s_states[i] << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < s_symbols.size(); i++) {
		std::cout << std::setw(2) << s_symbols[i] << " ";
	}
	std::cout << std::setw(9);
	for (int i = ip; i < parse_s.size(); i++) {
		if (parse_s[i][0] == '0') {
			std::string temps(++parse_s[i].begin(), parse_s[i].end());
			std::cout << temps;
		}
		else {
			std::cout << parse_s[i];
		}
	}
	//std::cout << "\n";
}