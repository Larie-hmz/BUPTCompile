#include "dfa.h"

//dfa主程序
void dfa::dfa_run() {
	char a1[8] = "include", a2[8] = "define";
	int count = 0;
	int flag_exp = 1;
	do {
		switch (state) {
		case 0:
			flag_exp = 1;
			temps = "";
			scan.get_char();
			scan.get_nbc();
			C = scan.get_c();
			temps += C;
			state = judge_case0(C);
			break;
		case 1: //标识符
			C = scan.get_char();
			if (isalpha(C) || isdigit(C) || C == '_') {
				temps += C;
				state = 1;
			}
			else {
				scan.retract();
				//查找是否是关键字
				if (is_keywords() == -1) { //不是关键字
					indentry=table_insert();
					token_ptr = new token(tokenType::ID,indentry , scan.line, scan.row);
					all_token.push_back(token_ptr);
					counter[(int)tokenType::ID]++;
				}
				else {
					token_ptr = new token(tokenType(is_keywords()+1), keywords[is_keywords()], scan.line, scan.row);
					all_token.push_back(token_ptr);
					counter[(int)tokenType(is_keywords() + 1)]++;
				}
				state = 0;
			}
			break;
		case 2://查找是否是数字
			C = scan.get_char();
			if (isdigit(C)) {
				temps += C;
				state = 2;
				break;
			}
			switch (C) {
			case '.': temps += C; state = 3; break;
			case 'E':case 'e':
				temps += C; state = 5; break;
			default: //如果是整数
				scan.retract();
				state = 0;
				token_ptr = new token(tokenType::NUM, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::NUM]++;
				break;
			}
			break;
		case 3:
			C = scan.get_char();
			if (isdigit(C)) {
				temps += C;
				state = 4;
			}
			else {
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::EEEOR_NUM, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::EEEOR_NUM]++;
			}
			break;
		case 4:
			C = scan.get_char();
			if (isdigit(C)) {
				temps += C;
				state = 4;
			}
			else if(C == 'E'|| C == 'e'){
				temps += C;
				state = 5;
			}
			else { //识别出小数
				scan.retract();
				state = 0;
				token_ptr = new token(tokenType::NUM, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::NUM]++;
				break;
			}
			break;
		case 5:
			C = scan.get_char();
			if (isdigit(C)) {
				temps += C;
				state = 7;
			}
			else if (C == '+'|| C == '-') {
				temps += C;
				state = 6;
			}
			else { //识别错误
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::EEEOR_NUM, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::EEEOR_NUM]++;
			}
			break;
		case 6:
			C = scan.get_char();
			if (isdigit(C)) {
				temps += C;
				state = 7;
			}
			else {
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::EEEOR_NUM, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::EEEOR_NUM]++;
			}
			break;
		case 7://含有指数的数
			C = scan.get_char();
			if (isdigit(C)) {
				temps += C;
				state = 7;
			}
			else {
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::NUM, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::NUM]++;
			}
			break;
		case 8: // <
			C = scan.get_char();
			temps += C;
			if (C == '=') {
				state = 0;
				token_ptr = new token(tokenType::LESS_EQUAL, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::LESS_EQUAL]++;
			}
			else if (C == '<') {
				state = 0;
				token_ptr = new token(tokenType::SHL, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::SHL]++;
			}
			else {
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::LESS,"<" , scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::LESS]++;
			}
			break;
		case 9: // >
			C = scan.get_char();
			temps += C;
			if (C == '=') {
				state = 0;
				token_ptr = new token(tokenType::GREATER_EQUAL, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::GREATER_EQUAL]++;
			}
			else if (C == '>') {
				state = 0;
				token_ptr = new token(tokenType::SHR, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::SHR]++;
			}
			else {
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::GREATER,">", scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::GREATER]++;
			}
			break;
		case 10:// =
			C = scan.get_char();
			temps += C;
			if (C == '=') {
				state = 0;
				token_ptr = new token(tokenType::EQUAL, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::EQUAL]++;
			}
			else if (C == '>') {
				state = 0;
				token_ptr = new token(tokenType::ARROW, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::ARROW]++;
			}
			else {
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::ASSIGN, "=", scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::ASSIGN]++;
			}
			break;
		case 11: //+
			C = scan.get_char();
			temps += C;
			if (C == '=') {
				state = 0;
				token_ptr = new token(tokenType::ADD_ASSIGN, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::ADD_ASSIGN]++;
			}
			else if (C == '+') {
				state = 0;
				token_ptr = new token(tokenType::INC, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::INC]++;
			}
			else {
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::ADD, "+", scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::ADD]++;
			}
			break;
		case 12: // -
			C = scan.get_char();
			temps += C;
			if (C == '=') {
				state = 0;
				token_ptr = new token(tokenType::SUB_ASSIGN, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::SUB_ASSIGN]++;
			}
			else if (C == '-') {
				state = 0;
				token_ptr = new token(tokenType::DEC, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::DEC]++;
			}
			else {
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::SUB, "-", scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::SUB]++;
			}
			break;
		case 13:// *
			C = scan.get_char();
			temps += C;
			if (C == '=') {
				state = 0;
				token_ptr = new token(tokenType::MUL_ASSIGN, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::MUL_ASSIGN]++;
			}
			else {
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::MUL, "*", scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::MUL]++;
			}
			break;
		case 14: // /
			C = scan.get_char();
			temps += C;
			if (C == '=') {
				state = 0;
				token_ptr = new token(tokenType::DIV_ASSIGN, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::DIV_ASSIGN]++;
			}
			else if (C == '/' ){
				state = 15;
			}
			else if (C == '*') {
				state = 16;
			}
			else{
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::DIV, "/", scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::DIV]++;
			}
			break;
		case 15:
			//行注释
			C = scan.get_char();
			if (C != '\n') {
				state = 15;
			}
			else {
				state = 0;
			}
			break;
		case 16:
			//块注释
			C = scan.get_char();
			flag_exp = 0;
			if (C == '*') {
				C = scan.get_char();
				if (C != '/') {
					scan.retract();
					state = 16;
					break;
				}
				else {
					flag_exp = 1;
					state = 0;
					break;
				}
			}
			state = 16;
			break;
		case 17: // !
			C = scan.get_char();
			temps += C;
			if (C == '=') {
				state = 0;
				token_ptr = new token(tokenType::INEUQUAL, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::INEUQUAL]++;
			}
			else {
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::NOT, "！", scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::NOT]++;
			}
			break;
		case 18: // "
			C = scan.get_char();
			temps += C;
			if (C != '"') {
				if (C == '\n') {
					state = 0;
					token_ptr = new token(tokenType::ERROR_STRING, temps, scan.line, scan.row);
					all_token.push_back(token_ptr);
					counter[(int)tokenType::ERROR_STRING]++;
					break;
				}
				state = 18;
			}
			else {
				state = 0;
				token_ptr = new token(tokenType::STRING_BLOCK, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::STRING_BLOCK]++;
			}
			break;
		case 19: // %
			C = scan.get_char();
			temps += C;
			if (C == '=') {
				state = 0;
				token_ptr = new token(tokenType::MOD_ASSIGN, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::MOD_ASSIGN]++;
			}
			else{
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::MOD, "%", scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::MOD]++;
			}
			break;
		case 20: // |
			C = scan.get_char();
			temps += C;
			if (C == '|') {
				state = 0;
				token_ptr = new token(tokenType::OR, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::OR]++;
			}
			else{
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::BITWISE_OR, "|", scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::BITWISE_OR]++;
			}
			break;
		case 21: // &
			C = scan.get_char();
			temps += C;
			if (C == '&') {
				state = 0;
				token_ptr = new token(tokenType::ADD, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::ADD]++;
			}
			else{
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::BITWISE_AND, "&", scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::BITWISE_AND]++;
			}
			break;
		case 22://#
			scan.get_char();
			scan.get_nbc();
			C = scan.get_c();
			temps += C;
			int i;
			if (C == 'i') {
				for (i = 1; i < 7; i++) {
					C = scan.get_char();
					if (C == a1[i]) {
						temps += C;
					}
					else {
						state = 0;
						scan.retract();
						token_ptr = new token(tokenType::EEROR_PREACTION, temps, scan.line, scan.row);
						all_token.push_back(token_ptr);
						counter[(int)tokenType::EEROR_PREACTION]++;
						break;
					}
				}
				if (i == 7) {
					token_ptr = new token(tokenType::PREACTION, temps, scan.line, scan.row);
					all_token.push_back(token_ptr);
					counter[(int)tokenType::PREACTION]++;
				}
			}
			else if (C == 'd') {
				for (i = 1; i < 6; i++) {
					C = scan.get_char();
					if (C == a2[i]) {
						temps += C;
					}
					else {
						state = 0;
						scan.retract();
						token_ptr = new token(tokenType::EEROR_PREACTION, temps, scan.line, scan.row);
						all_token.push_back(token_ptr);
						counter[(int)tokenType::EEROR_PREACTION]++;
						break;
					}
				}
				if (i == 6) {
					token_ptr = new token(tokenType::PREACTION, temps, scan.line, scan.row);
					all_token.push_back(token_ptr);
					counter[(int)tokenType::PREACTION]++;
				}
			}
			else {
				state = 0;
				scan.retract();
				token_ptr = new token(tokenType::EEROR_PREACTION, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::EEROR_PREACTION]++;
			}
			state = 0;
			break;
		case 23: // \'
			scan.get_char();
			//scan.get_nbc();
			C = scan.get_c();
			temps += C;
			if (C == '\\') {//不处理
				break;
			}
			scan.get_char();
			//scan.get_nbc();
			C = scan.get_c();
			temps += C;
			//目前情况是无法识别出可以用\转义的字符
			if (C == '\'') {
				token_ptr = new token(tokenType::ACHAR, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::ACHAR]++;
			}
			else {
				scan.retract(); scan.retract();
				token_ptr = new token(tokenType::ERROE_CHAR, temps, scan.line, scan.row);
				all_token.push_back(token_ptr);
				counter[(int)tokenType::ERROE_CHAR]++;
			}
			state = 0;
			break;
		default:
			std::cout << "error!!!";
		}

		//count++;

	} while (C != EOF);
	if (flag_exp == 0) {
		token_ptr = new token(tokenType::ERROR_EXP, temps, scan.line, scan.row);
		all_token.push_back(token_ptr);
		counter[(int)tokenType::ERROR_EXP]++;
	}
}

//在state0的情况下进行判断
int dfa::judge_case0(char x) {
	int t_state;
	if (isalpha(x)) {
		t_state = 1;
	}
	else if(isdigit(x)) {
		t_state = 2;
	}
	else {
		switch (x) {
		case '<': t_state = 8; break;
		case '>': t_state = 9; break;
		case '=': t_state = 10; break;
		case '+': t_state = 11; break;
		case '-': t_state = 12; break;
		case '*': t_state = 13; break;
		case '/': t_state = 14; break;
		case '!': t_state = 17; break;
		case '"': t_state = 18; break;
		case '%': t_state = 19; break;
		case '|': t_state = 20; break;
		case '&': t_state = 21; break;
		case '#': t_state = 22; break;
		case '\'':t_state = 23; break;
		case '?':
			t_state = 0;
			token_ptr = new token(tokenType::QUESTION, "?", scan.line, scan.row);
			counter[(int)tokenType::QUESTION]++;
			all_token.push_back(token_ptr);
			break;
		case '^':
			t_state = 0;
			token_ptr = new token(tokenType::BITWISE_XOR, "^", scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::BITWISE_XOR]++;
			break;
		case '(':
			t_state = 0;
			token_ptr = new token(tokenType::L_PAREN, "(", scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::L_PAREN]++;
			break;
		case ')':
			t_state = 0;
			token_ptr = new token(tokenType::R_PAREN, ")", scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::R_PAREN]++;
			break;
		case '[':
			t_state = 0;
			token_ptr = new token(tokenType::L_SQUARE, "[", scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::L_SQUARE]++;
			break;
		case ']':
			t_state = 0;
			token_ptr = new token(tokenType::R_SQUARE, "]", scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::R_SQUARE]++;
			break; 
		case '{':
			t_state = 0;
			token_ptr = new token(tokenType::L_BRACE, "{", scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::L_BRACE]++;
			break; 
		case '}':
			t_state = 0;
			token_ptr = new token(tokenType::R_BRACE, "}", scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::R_BRACE]++;
			break; 
		case ',':
			t_state = 0;
			token_ptr = new token(tokenType::COMMA, ",", scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::COMMA]++;
			break;
		case ';':
			t_state = 0;
			token_ptr = new token(tokenType::SEMICOLON, ";", scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::SEMICOLON]++;
			break; 
		case ':':
			t_state = 0;
			token_ptr = new token(tokenType::COLON, ":", scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::COLON]++;
			break;
		case '~':
			t_state = 0;
			token_ptr = new token(tokenType::BITWISE_NOT, "~", scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::BITWISE_NOT]++;
			break;
		case '.': 
			t_state = 0;
			token_ptr = new token(tokenType::DOT, ".", scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::DOT]++;
			break;
		case '\t':case '\n':t_state = 0; break;
		default:
			t_state = 0;
			token_ptr = new token(tokenType::UNKNOWN, temps, scan.line, scan.row);
			all_token.push_back(token_ptr);
			counter[(int)tokenType::UNKNOWN]++;
			break;
		}
	}
	return t_state;
}

//符号表的插入
int dfa::table_insert() {
	int ident = my_table.size();
	my_table.push_back(temps);
	return ident;
}

//判断是否是关键字
//不是关键字return -1 关键字则返回其在表中的位置
int dfa::is_keywords() {
	auto it = find(keywords.begin(), keywords.end(), temps);
	if (it == keywords.end()) {
		return -1; //不是关键字
	}
	return distance(keywords.begin(),it) ;
}

//以记号形式输出单词符号
void dfa::print_token() {
	std::cout << "\n词法分析结果如下，并以记号形式输出\n";
	int token_len = all_token.size();
	for (int i = 0; i < token_len; i++) {
		if (all_token[i]->type != tokenType::ID) {
			int suoyin = (int)all_token[i]->type;
			std::cout << "< " << string_keywords[suoyin] << " , " << all_token[i]->value << " > ";
		}
		else {
			int suoyin = (int)all_token[i]->type;
			std::cout << "< " << string_keywords[suoyin] << " , " << my_table[all_token[i]->symbolPos]<< " > ";
		}
		std::cout << "\nline: " << all_token[i]->line1 << "   rows:" << all_token[i]->row1<<"\n";
	}

}

//输出统计结果
void dfa::print_static() {
	std::cout << "\n程序语句行数 ：" << scan.line-1 << "\n";
	std::cout << "各类单词数据统计如下：\n";
	int sum = 0;
	for (int i = 0; i < type_number;i++) {
		std::cout << string_keywords[i] << " : " << counter[i]<<"\n";
		sum += counter[i];
	}
	std::cout << "\n字符总数为：" << sum << "\n";
}
