#pragma once
#include <vector>
#include <string>
#include "ScannerClasses.h"

using std::vector;
using std::string;
enum StandartType {IDN = 0, TRM = 1, LIT = 2,ENDF =3};

constexpr int NO_EXIST_IN_TABLE = -1;

struct LiteralRecord{
	Lexeme_Class code;
	string lexem;
};
struct KeyWordRecord {
	unsigned int index;
	string lexem;
	bool isDelim;
};
struct IdentifierRecord {
	unsigned int index;
	string lexem;
};
struct StandartSymbolRecord {
	StandartType type;
	unsigned int index;
};

extern vector<LiteralRecord> Table_Literals;
extern vector<IdentifierRecord> Table_Identifiers;
extern vector<KeyWordRecord> Table_ReservedWords;
extern vector<StandartSymbolRecord> Table_StandartSymbols;


static int isIdentifireExist(const string& str) {
	int searchResult = NO_EXIST_IN_TABLE;
	for (size_t i = 0; i < Table_Identifiers.size(); ++i)
		if (Table_Identifiers[i].lexem == str) {
			searchResult = i;
			i = Table_Identifiers.size(); // End loop
		}
	return searchResult;
}
static int isReservedWordExist(const string& str) {
	int searchResult = -1;
	for (size_t i = 0; i < Table_ReservedWords.size(); ++i)
		if (Table_ReservedWords[i].lexem == str) {
			searchResult = i;
			break;
		}
	return searchResult;
}