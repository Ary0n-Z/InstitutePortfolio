#pragma once
#include "ILineReader.h"


using std::unique_ptr;
class LineController
{
private:
	unique_ptr<ILineReader> lineContainer;
	size_t currentCharIndex = 0;
	string line;
public:
	LineController(unique_ptr<ILineReader> lineContainer);
	~LineController();
	char NextCharWithWrapping();
	size_t WhatLine();
	size_t CurrenIndex();
	static constexpr char EMPTY_CHAR = '\0';
};

