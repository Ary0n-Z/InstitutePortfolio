#include "Parser.h"
#include "FileManager.h"
#include "Tables.h"
#include "ErrorLog.h"
Parser::Parser()
{
	unique_ptr<FileManager> manager(new FileManager());
	manager->Open("statement.txt");
	if (manager->CanRead()) {
		unique_ptr<ILineReader> reader(dynamic_cast<ILineReader*>(manager.release()));
		scanner = new Scanner(std::move(reader));
	}
}

Parser::~Parser()
{
	if (scanner != nullptr)delete scanner;
}


void Parser::Parse()
{
	ReadNS();
	if (NS->type == StandartType::ENDF)return;
	STATEMENT();
}
string Parser::GetLexemName() {
	switch (NS->type) {
	case StandartType::IDN:
		return Table_Identifiers[NS->index].lexem;
	case StandartType::TRM:
		return Table_ReservedWords[NS->index].lexem;	
	case StandartType::LIT:
		return Table_Literals[NS->index].lexem;
	case StandartType::ENDF:
		return "EOF!";
	}
}

void Parser::STATEMENT(){
		switch (NS->type)
		{
		case StandartType::IDN:
			ASSIGMENT();
			break;
		case StandartType::TRM:
			FOR_STATEMENT();
			break;
		default:
			ErrorLog::Instance()->AddParseError(string("Identifire \"")+ GetLexemName() +string("\" is not defined"),scanner->CurLine(),scanner->CurWord());
			break;
		}
}

void Parser::FOR_STATEMENT() {
	Quadruple q;
	if (Table_ReservedWords[NS->index].index == 6) {//for
		ReadNS();
		INITIAL_VALUE();
		q.op2 = TEMP;
		if (NS->type == StandartType::TRM && Table_ReservedWords[NS->index].index == 7) {//to
			ReadNS();
			EXPRESION();
			q.output = TEMP;
			if (NS->type == StandartType::TRM && Table_ReservedWords[NS->index].index == 8) {//do
				q.operation = "BE";
				Quads.push_back(q);
				int quadRecIndex = Quads.size()-1;
				ReadNS();
				STATEMENT();
				Quads[quadRecIndex].op1 = to_string(Quads.size()+3);


				// i + 1
				q.output = ("T" + to_string(TEMPINDEX++));
				q.op2 = "1"; 
				q.operation = "+";
				q.op1 = Quads[quadRecIndex].op2;
				Quads.push_back(q);

				// i = 1;
				q.output = Quads[quadRecIndex].op2;
				q.op2 = "";
				q.operation = ":=";
				q.op1 = Quads[Quads.size()-1].output;
				Quads.push_back(q);

				//br
				q.output = ""; q.op2 = ""; q.operation = "BR"; q.op1 = to_string(quadRecIndex);
				Quads.push_back(q);
			}
			else ErrorLog::Instance()->AddParseError("\"do\" keyword is missing", scanner->CurLine(), scanner->CurWord());
		}
		else ErrorLog::Instance()->AddParseError("\"to\" keyword is missing; found= \"" + GetLexemName() + "\"" , scanner->CurLine(), scanner->CurWord());
	}
	else ErrorLog::Instance()->AddParseError("\"for\" keyword is missing", scanner->CurLine(), scanner->CurWord());
}

void Parser::INITIAL_VALUE() {
	VAR();
	if (NS->type == StandartType::TRM &&Table_ReservedWords[NS->index].index == 29) { //:=
		Quadruple q;
		q.output = TEMP;
		q.operation = ":=";
		ReadNS();
		EXPRESION();
		q.op1 = TEMP;
		Quads.push_back(q);
		INDEX++;
		TEMP = q.output;
	}

}

void Parser::ASSIGMENT() {
	VAR();
	if (NS->type == StandartType::TRM && Table_ReservedWords[NS->index].index == 29) { //:=
		Quadruple q;
		q.output = TEMP;
		q.operation = ":=";

		ReadNS();
		EXPRESION();

		q.op1 = TEMP;
		Quads.push_back(q);
		INDEX++;
		TEMP = q.output;

		if (!(NS->type == StandartType::TRM && Table_ReservedWords[NS->index].index == 18)) //;
			ErrorLog::Instance()->AddParseError("\";\" keyword is missing; statement end index expected", scanner->CurLine(), scanner->CurWord());
	}
	else
		ErrorLog::Instance()->AddParseError("\":=\" keyword is missing; assigment expected", scanner->CurLine(), scanner->CurWord());
}

void Parser::VAR() {
	if (NS->type != StandartType::IDN)
		ErrorLog::Instance()->AddParseError(string("Var id expected; found = \"") + GetLexemName() + string("\""), scanner->CurLine(), scanner->CurWord());
	else {
		string localName = GetLexemName();
		ReadNS();
		if (NS->type == StandartType::TRM) {
			switch (Table_ReservedWords[NS->index].index) {
			case 17: { //.
				ReadNS();
				VAR();
				localName += "." + TEMP;
			}break;
			case 22: {//[
				ReadNS();			
				EXPRESION();
				if (Table_ReservedWords[NS->index].index != 23) {
					ErrorLog::Instance()->AddParseError(string("\"]\" is missing") + GetLexemName() + string("\""), scanner->CurLine(), scanner->CurWord());
				}
				else {
					localName += "[" + TEMP + "]";
					ReadNS();
				}
			}break;
			}
		}
		TEMP = localName;
	}
}

void Parser::EXPRESION() {
	TERM();
	// + -
	int sign = Table_ReservedWords[NS->index].index ;
	while (NS->type == StandartType::TRM && (Table_ReservedWords[NS->index].index == 21 || Table_ReservedWords[NS->index].index == 20) ){
		Quadruple q;
		q.op1 = TEMP;

		if (sign == 21)
			q.operation = "+";
		else
			q.operation = "-";

		ReadNS();
		TERM();
		q.op2 = TEMP;
		q.output = ("T" + to_string(TEMPINDEX++));
		Quads.push_back(q);
		TEMP = q.output;
	}
}

void Parser::TERM() {
	FACTOR();
	// * /
	int sign = Table_ReservedWords[NS->index].index;
	while (NS->type == StandartType::TRM && (Table_ReservedWords[NS->index].index == 28 || Table_ReservedWords[NS->index].index == 27)) {
		Quadruple q;
		q.op1 = TEMP;

		if (sign == 27)
			q.operation = "*";
		else
			q.operation = "/";
		
		ReadNS();
		FACTOR();
		q.op2 = TEMP;
		q.output = ("T" + to_string(TEMPINDEX++));
		Quads.push_back(q);
		TEMP = q.output;
	}
}

void Parser::FACTOR() {
	switch (NS->type) {
	case StandartType::IDN: { 				
		VAR();
	}break;
	case StandartType::LIT: {
		if (Table_Literals[NS->index].code != Lexeme_Class::INT)
			ErrorLog::Instance()->AddParseError(string("String liter \" ") + GetLexemName() + string("\" is unable"), scanner->CurLine(), scanner->CurWord());
		else {
			TEMP = GetLexemName();
			ReadNS();
		}
	}break;

	default: {
		ErrorLog::Instance()->AddParseError(string("Unexpected terminal lexem \"") + GetLexemName() + string("\""), scanner->CurLine(), scanner->CurWord());
	}break;
	}
}


void Parser::ReadNS() {
	NS = scanner->Scan();
}