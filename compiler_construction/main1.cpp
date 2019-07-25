//#include "Tables.h"
//#include "Scanner.h"
//#include "FileManager.h"
//#include <iostream>
//#include <fstream>
//#include "Lexicone.h"
//#include "Table.h"
//
//using namespace std;
//
// vector<LiteralRecord> Table_Literals;
// vector<IdentifierRecord> Table_Identifiers;
// vector<KeyWordRecord> Table_ReservedWords;
// vector<StandartSymbolRecord> Table_StandartSymbols;
//
//void writetablestofile() {
//	ofstream of;
//	of.open("Table_Literals.csv", ios_base::trunc);
//	for (auto it = Table_Literals.begin(); it < Table_Literals.end(); it++)
//		of << ((*it).code == Lexeme_Class::CSTR ?"CSTR":"INT")<< " " << (*it).lexem << endl;
//	of.close();
//
//	of.open("Table_Identifiers.csv", ios_base::trunc);
//	for (auto it = Table_Identifiers.begin(); it < Table_Identifiers.end(); it++)
//		of << (*it).index << " "<< (*it).lexem << endl;
//	of.close();
//
//	of.open("Table_ReservedWords.csv", ios_base::trunc);
//	for (auto it = Table_ReservedWords.begin(); it < Table_ReservedWords.end(); it++)
//		of << (*it).index << " " << (*it).lexem << " " << (*it).isDelim << endl;
//	of.close();
//
//	of.open("Table_StandartSymbols.csv", ios_base::trunc);
//	for (auto it = Table_StandartSymbols.begin(); it < Table_StandartSymbols.end(); it++)
//		of << ((*it).type == StandartType::IDN ? "IDN" : "TRM") << " " << (*it).index << endl;
//	of.close();
//}
//void menu(){
//	cout << "menu:\n 1 Table_Literals\n"
//		" 2 Table_Identifiers\n"
//		" 3 Table_ReservedWords\n"
//		" 4 Table_StandartSymbols\n"
//		" 5 Write to file\n"
//		" 0 Exit\n > ";
//}
//void printTableLiterals() {
//	TextTable table;
//	table.add("CODE");
//	table.add("LEXEM");
//	table.endOfRow();
//	for (int i = 0; i < Table_Literals.size(); i++) {
//		table.add((Table_Literals[i].code == Lexeme_Class::CSTR ? "CSTR" : "INT"));
//		table.add(Table_Literals[i].lexem);
//		table.endOfRow();
//	}
//	table.setAlignment(2, TextTable::Alignment::RIGHT);
//	std::cout << table;
//}
//void printTableID() {
//	TextTable table;
//	table.add("INDEX");
//	table.add("LEXEM");
//	table.endOfRow();
//	char buf[12];
//	for (int i = 0; i < Table_Identifiers.size(); i++) {
//		sprintf_s(buf, "%d", Table_Identifiers[i].index);
//		table.add(buf );
//		table.add(Table_Identifiers[i].lexem);
//		table.endOfRow();
//	}
//	table.setAlignment(2, TextTable::Alignment::RIGHT);
//	std::cout << table;
//}
//void printTableReserved() {
//	TextTable table;
//	table.add("INDEX");
//	table.add("LEXEM");
//	table.add("DELIM");
//	table.endOfRow();
//	char buf[12];
//	for (int i = 0; i < Table_ReservedWords.size(); i++) {
//		sprintf_s(buf, "%d", Table_ReservedWords[i].index);
//		table.add(buf);
//		table.add(Table_ReservedWords[i].lexem);
//		table.add((Table_ReservedWords[i].isDelim ? "true" : "false"));
//		table.endOfRow();
//	}
//	table.setAlignment(2, TextTable::Alignment::RIGHT);
//	std::cout << table;
//}
//void printTableStandart() {
//	TextTable table;
//	table.add("TYPE");
//	table.add("INDEX");
//	table.endOfRow();
//	char buf[12];
//	for (int i = 0; i < Table_StandartSymbols.size(); i++) {
//		table.add((Table_StandartSymbols[i].type == StandartType::IDN ? "IDN" : "TRM"));
//		sprintf_s(buf, "%d", Table_StandartSymbols[i].index);
//		table.add(buf);
//		table.endOfRow();
//	}
//	table.setAlignment(2, TextTable::Alignment::RIGHT);
//	std::cout << table;
//}
//int main(){
//	unique_ptr<FileManager> manager(new FileManager());
//	manager->Open("code.txt");
//	if (manager->CanRead()) {
//		unique_ptr<ILineReader> reader(dynamic_cast<ILineReader*>(manager.release()));
//		Scanner sc(std::move(reader));
//
//		if (sc.Scan()!=nullptr) {
//			cout << "Scan success!\n";
//			unsigned short in = 0;
//			do {
//				menu();
//				cin >> in;
//				switch (in) {
//				case 1:printTableLiterals(); system("PAUSE"); break;
//				case 2:printTableID(); system("PAUSE"); break;
//				case 3:printTableReserved(); system("PAUSE"); break;
//				case 4:printTableStandart(); system("PAUSE"); break;
//				case 5: writetablestofile(); break;
//				case 0:break;
//				default:;
//				}
//				system("cls");
//			} while (in);
//		}
//		else {
//			auto error = sc.GetError();
//			cout << "Unrecognized symbol ='"<< error.symbol<<"' at "
//				<< error.line + 1 << " line, "
//				<< error.charIndex + 1 << "th symbol!\n";
//		}
//	}
//	else
//	{
//		cout << "No file to compile found found!\n";
//	}
//	system("PAUSE");
//}
