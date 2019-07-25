#pragma once
#include "ILineReader.h"
#include "LineController.h"
#include "Lexicone.h"
#include "Tables.h"

using std::unique_ptr;

struct SymbolError{
	size_t line;
	size_t charIndex;
	char symbol;
};
class Scanner
{
private:	
	Lexicone* lexicone;
	LineController* lineController;
	SymbolError errorLog;
	char CHAR = LineController::EMPTY_CHAR;
	char BACKUP = LineController::EMPTY_CHAR;
	string LEXEM;
	unsigned int LEXEM_DATA;
	Lexeme_Class LEXEM_CLASS; 
	bool EndOfFile;
public:
	Scanner(unique_ptr<ILineReader> lineContainer);
	~Scanner();
	StandartSymbolRecord* Scan();
	SymbolError GetError();
	size_t CurWord() {
		return lineController->CurrenIndex();
	}
	size_t CurLine(){
		return lineController->WhatLine();
	}
private:
	void Init();
	void FSM();
	void GC();
	void IGNORE();
};

