#pragma once
#include <fstream>
#include <string>
#include "ILineReader.h"

using std::ifstream;
using std::string;

class FileManager: public ILineReader
{
private:
	string line;
	ifstream iStream;
	size_t lineIndex = -1;
public:
	FileManager();
	~FileManager();
public:
	size_t LineNum();
	string NextLine();
	bool Open(const char* cFilePath);
	bool CanRead();
};

