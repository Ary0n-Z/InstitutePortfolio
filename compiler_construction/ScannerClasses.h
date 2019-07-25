#pragma once

enum Symbol_Class {
	UNKNOWN = -1,
	DIGIT = 0,
	ALPHA = 1,
	DELIM_1 = 2,
	DELIM_2 = 3,
	CSTREDGE = 4
};

enum Lexeme_Class
{
	NONE = -1,
	ID = -2,
	DELIM1 = -3,
	DELIM2 = -4,
	CSTR = -5,
	KEYWORD = -6,
	INT = -7,
	ERROR_CODE_1 = -8,
	DELIM = -9
};