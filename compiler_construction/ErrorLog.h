#pragma once
#include <string>
#include <vector>

using std::vector;
using std::string;
struct Err {
	string msg;
	size_t line;
	size_t word;
};
class ErrorLog {
public:
	vector<Err> errors;
	void AddParseError(string errorMsg,size_t line, size_t word) {
		errors.push_back({ errorMsg, line, word });
	}
	static ErrorLog* Instance() {
		static ErrorLog instance;
		return &instance;
	} 	
	~ErrorLog(void) { }
private:
	ErrorLog(void) {}
	ErrorLog(ErrorLog& other) {}
	ErrorLog& operator=(ErrorLog& other) {}
};