#include "scanner.h"

scanner scan;
//���뻺����
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

//����ǿ��ַ�
char scanner::get_char() {
	c = *forwardp;
	//���������������β����Ҫ������һ��������
	if (*(forwardp + 1) == '\0') {
		if (flag) {
			//std::cout << 1111111111 << "\n";
			//�����ϰ뻺����
			read_half(buffer_1);
			forwardp = buffer_1;
		}
		else {
			//�����°뻺����
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
	//��¼�к��е�λ��
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

//������ַ���
void scanner::get_nbc() {
	if (c == ' '||c == '\t'||c == '\n'){
		//lexemebegin=forwardp;
		get_char();
	}
}

//����forwardָ��
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