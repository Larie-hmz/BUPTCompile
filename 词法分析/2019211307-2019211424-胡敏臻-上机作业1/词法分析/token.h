#pragma once
#include<vector>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<iostream>

enum class tokenType {
	//ʶ������
	UNKNOWN = 0,
	//�����ؼ���
	AUTO, BREAK, CASE, CHAR, CONST, CONTINUE,
	DEFAULT, DO, DOUBLE, ELSE, ENUM, EXTERN, FLOAT, FOR, GOTO,
	IF, INT, LONG, REGISTER, RETURN, SHORT, SIGNED, STATIC,
	SIZEOF, STRUCT, SWITCH, TYPEDEF, UNIONUNSIGNED, VOID, VOLATILE, WHILE,
	//�����
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

	ID, //��ʶ��
	NUM, //����
	ACHAR, //�ַ�
	STRING_BLOCK, //�ַ���
	PREACTION, //Ԥ����
	TAB, //�Ʊ��

	ERROR_EXP, //ע�ʹ���
	EEEOR_NUM,  //���ֱ�����
	ERROE_CHAR, //�������ַ�����
	ERROR_STRING, //�ַ������Ŵ���
	EEROR_PREACTION, //Ԥ�������

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

