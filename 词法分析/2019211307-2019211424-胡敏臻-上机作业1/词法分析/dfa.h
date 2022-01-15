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
	int state = 0; //记录此时处于自动机的哪个状态
	//int line = 0, row = 0;//记录此时的行数和列数
	std::string temps; //记录此时临时字符串
	std::vector<std::string> my_table; //记录标识符的符号表
	int counter[type_number]; //计数，记录每种种类出现过几次  
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
	"ID", //标识符
	"NUM", //数字
	"ACHAR", //字符
	"STRING_BLOCK", //字符块
	"PREACTION", //预处理
	"TAB",//制表符
	"ERROR_EXP", //注释错误
	"EEEOR_NUM",  //数字表达错误
	"ERROE_CHAR", //单引号字符错误
	"ERROR_STRING", //字符串引号错误
	"EEROR_PREACTION", //预处理错误
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

