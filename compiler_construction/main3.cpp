#include "Tables.h"
#include "Scanner.h"
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include "Lexicone.h"
#include "Table.h"
#include "Parser.h"
#include "ErrorLog.h"
vector<LiteralRecord> Table_Literals;
vector<IdentifierRecord> Table_Identifiers;
vector<KeyWordRecord> Table_ReservedWords;
vector<StandartSymbolRecord> Table_StandartSymbols;

int main() {
	Parser p;
	p.Parse();
	if (ErrorLog::Instance()->errors.size() > 0) {
		cout << " Parsing failed!\n Errors:\n";
		for (int i = 0; i < ErrorLog::Instance()->errors.size(); i++) {
			auto temp = ErrorLog::Instance()->errors[i];
			cout << i << ": (" << temp.line << ',' << temp.word << ") Msg:  " << temp.msg << endl;
		}
	}
	else {
		cout << " Parse success! Quads: \n";
		for (int i = 0; i < p.Quads.size(); i++) {
			cout << "(" << i << "), " << p.Quads[i].operation << ", "
				<< p.Quads[i].op1 << ", "
				<< p.Quads[i].op2 << ", "
				<< p.Quads[i].output << "\n";
		}
	}

	system("PAUSE");
}