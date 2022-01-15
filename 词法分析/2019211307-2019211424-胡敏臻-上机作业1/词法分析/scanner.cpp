#include "scanner.h"

scanner scan;
//读入缓冲区
void scanner::read_half(char buffer[]) {
	//std::cout << 2222222222 << "\n";
	std::cin.unsetf(std::ios::skipws);
	char c;
	int i = 0;
	for (i = 0; i < buffer_len-1&&!myfile.eof(); i++) {
		myfile.get(c);
		buffer[i] = c;
	}
	if (myfile.eof()) {
		buffer[i] = EOF;
	}
	else {
		buffer[i] = '\0';
	}
}

void scanner::init() {
	read_half(buffer_1);
}

//读入非空字符
char scanner::get_char() {
	c = *forwardp;
	//如果读到缓冲区结尾，需要覆盖另一处缓冲区
	if (*(forwardp + 1) == '\0') {
		if (flag) {
			//std::cout << 1111111111 << "\n";
			//读入上半缓冲区
			read_half(buffer_1);
			forwardp = buffer_1;
		}
		else {
			//读入下半缓冲区
			//std::cout << 2222222222 << "\n";
			read_half(buffer_2);
			forwardp = buffer_2;
		}
		flag = !flag;
	}
	else {
		forwardp++;
	}
	if (c == ' ') {
		lexemebegin = forwardp;
	}
	//记录行和列的位置
	if (c == '\n') {
		line++;
		t_row = row;
		row = 0;
	}
	else {
		row++;
	}
	//std::cout << c<<" " ;
	return c;
}

//读入空字符串
void scanner::get_nbc() {
	if (c == ' '||c == '\t'||c == '\n'){
		//lexemebegin=forwardp;
		get_char();
	}
}

//回退forward指针
void scanner::retract() {
	if (c == '\n') {
		line--;
		row = t_row;
	}
	else {
		row--;
	}
	if (forwardp != buffer_1 && forwardp != buffer_2) {
		forwardp--;
	}
	else if (forwardp == buffer_1) {
		forwardp = &buffer_2[buffer_len - 2];
	}
	else if (forwardp == buffer_2) {
		forwardp = &buffer_1[buffer_len - 2];
	}
}

char scanner::get_c() {
	return c;
}

//bool scanner::is_end() {
//	if (c == EOF) {
//		return true;
//	}
//	return false;
//}