#pragma once
#include<vector>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<iostream>

enum class tokenType {
	//识别有误
	UNKNOWN = 0,
	//保留关键字
	AUTO, BREAK, CASE, CHAR, CONST, CONTINUE,
	DEFAULT, DO, DOUBLE, ELSE, ENUM, EXTERN, FLOAT, FOR, GOTO,
	IF, INT, LONG, REGISTER, RETURN, SHORT, SIGNED, STATIC,
	SIZEOF, STRUCT, SWITCH, TYPEDEF, UNIONUNSIGNED, VOID, VOLATILE, WHILE,
	//运算符
	ASSIGN,       //=
	ADD,          //=
	INC,          //++
	ADD_ASSIGN,   //+=
	SUB,          //-
	DEC,          //--
	SUB_ASSIGN,   //-=
	MUL,          //*
	MUL_ASSIGN,   //*=
	DIV,          // /
	DIV_ASSIGN,   // /=
	MOD,          //%
	MOD_ASSIGN,   //%=  
	BITWISE_AND,  //&
	BITWISE_OR,   // |
	BITWISE_XOR,  // ^
	BITWISE_NOT,  // ~
	SHL,          // <<
	SHR,          // >>
	AND,          // &&
	OR,           // ||
	NOT,          // !
	LESS,         // <
	LESS_EQUAL,   // <=
	EQUAL,        // ==
	INEUQUAL,     // !=
	GREATER,      // >
	GREATER_EQUAL,// >=    
	QUESTION,    //?
	COMMA,       //,
	COLON,       //:
	SEMICOLON,   //;
	DOT,         //. 
	ARROW,       //=>
	L_BRACE,     //{
	R_BRACE,     //}
	L_SQUARE,    //[
	R_SQUARE,    //]
	L_PAREN,     //(
	R_PAREN,     //)
	WELL,        //#

	ID, //标识符
	NUM, //数字
	ACHAR, //字符
	STRING_BLOCK, //字符块
	PREACTION, //预处理
	TAB, //制表符

	ERROR_EXP, //注释错误
	EEEOR_NUM,  //数字表达错误
	ERROE_CHAR, //单引号字符错误
	ERROR_STRING, //字符串引号错误
	EEROR_PREACTION, //预处理错误

};


class token
{
public:
	tokenType type;
	int symbolPos = -1;
	std::string value = "";
	int line1, row1;
public:
	token(tokenType type, int symbolPos, int line, int row) {
		this->type = type;
		this->symbolPos = symbolPos;
		this->line1 = line;
		this->row1 = row;
		//std::cout << (int)type << " "<<symbolPos <<"line: "<< line <<"row: "<< row<<"\n";
	}
	token(tokenType type,std::string value, int line, int row) {
		this->type = type;
		this->value = value;
		this->line1 = line;
		this->row1 = row;
		//std::cout << (int)type << "value: " << value << "line: " << line << "row: " << row<<"\n";
	}
	~token() {

	}
};

