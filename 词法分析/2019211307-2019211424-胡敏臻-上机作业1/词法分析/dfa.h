#pragma once
#include"scanner.h"
#include"token.h"
#include<cstdio>
#include<cctype>
#include<string>
#include<algorithm>
#define type_number 84
class dfa
{
private:
	int state = 0; //��¼��ʱ�����Զ������ĸ�״̬
	//int line = 0, row = 0;//��¼��ʱ������������
	std::string temps; //��¼��ʱ��ʱ�ַ���
	std::vector<std::string> my_table; //��¼��ʶ���ķ��ű�
	int counter[type_number]; //��������¼ÿ��������ֹ�����  
	int indentry=0;
	char C;
	token* token_ptr = nullptr;
	std::vector<token*> all_token;
	std::vector<std::string>  keywords{ "auto","break","case","char","const","continue",
	"default","do","double","else","enum","extern","float","for","goto",
	"if","int","long ","register","return","short","signed","static",
	"sizeof","struct","switch","typedef","unionunsigned","void","volatile","while " };
	std::vector<std::string> string_keywords{
	"UNKNOWN ",	"AUTO", "BREAK", "CASE", "CHAR", "CONST", "CONTINUE","DEFAULT", "DO", "DOUBLE", 
	"ELSE", "ENUM", "EXTERN", "FLOAT", "FOR", "GOTO","IF", "INT", "LONG", "REGISTER", 
	"RETURN", "SHORT", "SIGNED", "STATIC","SIZEOF", "STRUCT", "SWITCH", "TYPEDEF", "UNIONUNSIGNED", "VOID", 
	"VOLATILE", "WHILE","ASSIGN", "ADD",  "INC", "ADD_ASSIGN","SUB", "DEC",	"SUB_ASSIGN","MUL",
	"MUL_ASSIGN", "DIV","DIV_ASSIGN","MOD","MOD_ASSIGN","BITWISE_AND","BITWISE_OR", "BITWISE_XOR","BITWISE_NOT", "SHL",	
	"SHR", 	"AND", 	"OR","NOT",	"LESS",	"LESS_EQUAL","EQUAL", "INEUQUAL", "GREATER","GREATER_EQUAL,","QUESTION", 
	"COMMA","COLON", "SEMICOLON", "DOT","ARROW", "L_BRACE"," R_BRACE","L_SQUARE", "R_SQUARE","L_PAREN",
	"R_PAREN", "WELL",
	"ID", //��ʶ��
	"NUM", //����
	"ACHAR", //�ַ�
	"STRING_BLOCK", //�ַ���
	"PREACTION", //Ԥ����
	"TAB",//�Ʊ��
	"ERROR_EXP", //ע�ʹ���
	"EEEOR_NUM",  //���ֱ�����
	"ERROE_CHAR", //�������ַ�����
	"ERROR_STRING", //�ַ������Ŵ���
	"EEROR_PREACTION", //Ԥ�������
	};

public:
	void dfa_run();
	int judge_case0(char x);
	int table_insert();
	int is_keywords();
	void print_token();
	void print_static();
	//void print_error();
};

