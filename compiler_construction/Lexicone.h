#pragma once
#include <vector>
#include <string>
#include <map>
#include "ScannerClasses.h"

using std::vector;
using std::string;
using std::pair;

class Lexicone {
private:
	unsigned int keyWords_BeginIndex;
	unsigned int delimiters_BeginIndex;
	unsigned int delimiters2_BeginIndex;

	vector<string> keyWords;
	string delimiters;
	vector<pair<char,char>> delimiters2;
private:
	int lookForDelim2(const string& delim);
public:
	static const int LOOKUP_NOT_RESERVED = -1;
public:	
	bool isDelim2First(char c);
	bool isdelim(char c);
	bool isDelim2Second(const string& str);
	Lexicone(const char *filename);
	~Lexicone();
	int Lookup(const string& str, const Lexeme_Class searchClass);
};