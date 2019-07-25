#pragma once
#include <string>

using std::string;

class ILineReader
{
public:
	virtual ~ILineReader() {};
	virtual string NextLine() = 0;
	virtual size_t LineNum() = 0;
	virtual bool CanRead() = 0;
};

