#include "Lexicone.h"
#include <cctype>
#include <algorithm>
#include <fstream>

using std::ifstream;
Lexicone::Lexicone(const char *filename) {
	ifstream is(filename);
	if (is.is_open()) {
		size_t reservedWordsCount;

		is >> reservedWordsCount;
		is >> keyWords_BeginIndex;
		is >> delimiters_BeginIndex;
		is >> delimiters2_BeginIndex;

		unsigned int i = keyWords_BeginIndex;
		keyWords.resize(delimiters_BeginIndex);
		is.ignore(1,'\n'); // to ignore end of line char
		while (i < delimiters_BeginIndex)
			std::getline(is,keyWords[i++]);
		i = 0;
		unsigned int elementsCount = delimiters2_BeginIndex - delimiters_BeginIndex;
		delimiters.resize(elementsCount);
		while (i < elementsCount)
			is >> delimiters[i++];
		i = 0;
		elementsCount = reservedWordsCount - delimiters2_BeginIndex; // TODO:: Make uniq
		delimiters2.resize(elementsCount);
		while (i < elementsCount) {
			is >> delimiters2[i].first;
			is >> delimiters2[i].second;
			i++;
		}
	}
	is.close();
}
Lexicone::~Lexicone() {}

bool Lexicone::isDelim2First(char c) {
	bool searchResult = false;
	for (size_t i = 0; i < delimiters2.size(); i++) {
		if (delimiters2[i].first == c) {
			searchResult = true;
			i = delimiters2.size(); // end loop
		}
	}
	return searchResult;
}
bool Lexicone::isDelim2Second(const string& str) {
	bool searchResult = false;
	for (size_t i = 0; i < delimiters2.size(); i++)
		if (delimiters2[i].first == str[0])
			if (delimiters2[i].second == str[1]) {
				searchResult = true;
				i = delimiters2.size(); // end loop
			}
	return searchResult;
}

int Lexicone::lookForDelim2(const string& delim) {
	int searchResult(Lexicone::LOOKUP_NOT_RESERVED);
	for (size_t i = 0; i < delimiters2.size(); i++)
		if (delimiters2[i].first == delim[0]) {
			if (delimiters2[i].second == delim[1]) {
				searchResult = i;
				i = delimiters2.size();// end loop
			}
		}
	return searchResult;
}
int Lexicone::Lookup(const string& str, const Lexeme_Class searchClass) {
	int index = Lexicone::LOOKUP_NOT_RESERVED;
	switch (searchClass) {
	case Lexeme_Class::ID: {
		auto it = std::find(keyWords.begin(), keyWords.end(), str);
		if (it != keyWords.end())
			index = std::distance(keyWords.begin(), it);
	}break;
	case Lexeme_Class::DELIM1: {
		auto pos = delimiters.find_first_of(str[0]);
		if (pos != string::npos) 
			index = pos + delimiters_BeginIndex; // offset for delimiters
	}break;
	case Lexeme_Class::DELIM2: 
		index = lookForDelim2(str);
		if(index != Lexicone::LOOKUP_NOT_RESERVED)
			index += delimiters2_BeginIndex; // offset for delimiters 2
		break;
	}
	return index;
}

bool Lexicone::isdelim(char c) {
	return delimiters.find_first_of(c) != std::string::npos;
}
