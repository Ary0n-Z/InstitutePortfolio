#include "Scanner.h"

Scanner::Scanner(unique_ptr<ILineReader> lineContainer){
	lexicone = new Lexicone("lexicone\\reservedWords.txt");
	lineController = new LineController(std::move(lineContainer));
	LEXEM.reserve(10); // Suposed length of lexems. For speed optimization.
	GC();
}


Scanner::~Scanner() { 
	delete lineController; 
	delete lexicone;
}

void Scanner::Init() {
	LEXEM_DATA = Lexeme_Class::NONE;
	LEXEM.clear();
	LEXEM_CLASS = NONE;
	BACKUP = '\0';
}
void Scanner::IGNORE() {
	while (CHAR == ' ' || CHAR == '\n' || CHAR == '\t')GC();
}
static unsigned int identifiersIndex = 0;

StandartSymbolRecord* Scanner::Scan(){
	if (EndOfFile) {
		Table_ReservedWords.push_back({ 0, "EOF", false });
		Table_StandartSymbols.push_back({ StandartType::ENDF, Table_ReservedWords.size()-1 });
		return &Table_StandartSymbols[Table_StandartSymbols.size() - 1];
	}
		IGNORE();
		FSM();
		switch (LEXEM_CLASS) {
		case Lexeme_Class::INT:
			Table_Literals.push_back({ Lexeme_Class::INT,LEXEM });
			Table_StandartSymbols.push_back({ StandartType::LIT, Table_Literals.size() - 1 });
			break;
		case Lexeme_Class::ID: {
				auto index = isIdentifireExist(LEXEM);
				if (index == NO_EXIST_IN_TABLE) {
					Table_Identifiers.push_back({ identifiersIndex,LEXEM });
					Table_StandartSymbols.push_back({ StandartType::IDN, identifiersIndex++ });
				}
				else
					Table_StandartSymbols.push_back({ StandartType::IDN, unsigned(index) });
			}break;
		case Lexeme_Class::CSTR:
				Table_Literals.push_back({ Lexeme_Class::CSTR, LEXEM });
				Table_StandartSymbols.push_back({ StandartType::LIT, Table_Literals.size() - 1 });

				break;
		case Lexeme_Class::ERROR_CODE_1:
				errorLog = {
					lineController->WhatLine(),
					lineController->CurrenIndex(),CHAR };
				return false;
		default: {
				long int index = isReservedWordExist(LEXEM);
				if (index  == -1 ) {
					Table_ReservedWords.push_back({ LEXEM_DATA, LEXEM, LEXEM_CLASS == DELIM });
					index = Table_ReservedWords.size()-1;
				}
				Table_StandartSymbols.push_back({ StandartType::TRM, (unsigned int)index });
			}
		}
	return &Table_StandartSymbols[Table_StandartSymbols.size() - 1];
}

void Scanner::FSM() {
	Init();
	//----------------------------------
	if (isalpha(CHAR)) {
		do {
			LEXEM.push_back(CHAR);
			GC();
		} while (isalnum(CHAR));
		int id = lexicone->Lookup(LEXEM, Lexeme_Class::ID);
		if (id > -1) {
			LEXEM_DATA = id;
			LEXEM_CLASS = Lexeme_Class::KEYWORD;
		}
		else
			LEXEM_CLASS = Lexeme_Class::ID;
		return;
	};
	//----------------------------------
	if (isdigit(CHAR)) {
		do {
			LEXEM.push_back(CHAR);
			GC();
		} while (isdigit(CHAR));
		LEXEM_CLASS = Lexeme_Class::INT;
		return;
	};
	//----------------------------------
	if (lexicone->isDelim2First(CHAR)) {
		LEXEM.push_back(CHAR);
		GC();
		BACKUP = LEXEM[0];
		LEXEM.push_back(CHAR);
		if (lexicone->isDelim2Second(LEXEM)) {
			LEXEM_DATA = lexicone->Lookup(LEXEM, Lexeme_Class::DELIM2);
			LEXEM_CLASS = Lexeme_Class::DELIM;
			BACKUP = '\0';
			GC();
			return;
		}
		else {
			LEXEM = "";
			std::swap(BACKUP, CHAR);
		}
	};
	//----------------------------------
	if (lexicone->isdelim(CHAR)) {
		LEXEM.push_back(CHAR);
		LEXEM_DATA = lexicone->Lookup(LEXEM, Lexeme_Class::DELIM1);
		LEXEM_CLASS = Lexeme_Class::DELIM;		
		GC();
		return;
	};
	//----------------------------------
	if (CHAR == '\'') {
		GC();
		while (CHAR != LineController::EMPTY_CHAR)
		{
			LEXEM.push_back(CHAR);
			GC();
			if (CHAR == '\'')
				CHAR = LineController::EMPTY_CHAR;
		}
		LEXEM_CLASS = Lexeme_Class::CSTR;
		GC();
		return;
	};
	LEXEM_CLASS = Lexeme_Class::ERROR_CODE_1;
}

void Scanner::GC() {
	if(BACKUP == '\0')
		CHAR = lineController->NextCharWithWrapping();
	else {
		CHAR = BACKUP;
		BACKUP = '\0';
	}
	EndOfFile = CHAR == '\0';
}	

SymbolError Scanner::GetError() {
	return errorLog;
}
