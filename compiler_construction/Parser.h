#pragma once
#include <iostream>
#include <string>
#include "Scanner.h"

using namespace std;
struct Quadruple {
	string operation;
	string op1;
	string op2;
	string output;
};

class Parser
{
private:
	Scanner* scanner = nullptr;	
	StandartSymbolRecord* NS = nullptr;
public:
	Parser();
	~Parser();
	void Parse();
	vector<Quadruple> Quads;
private:
	int INDEX = 0;
	string TEMP = "";
	string GVAR = "";
	string GetLexemName();
	int TEMPINDEX = 1;
	void STATEMENT();
	void FOR_STATEMENT();
	void ASSIGMENT();
	void VAR();
	void INITIAL_VALUE();
	void EXPRESION();
	void ReadNS();
	void TERM();
	void FACTOR();
};

