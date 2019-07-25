#include "FileManager.h"
#include <fstream>


FileManager::FileManager(){}

FileManager::~FileManager(){
	iStream.close();
}

size_t FileManager::LineNum() {return lineIndex;}

string FileManager::NextLine() { // return nullptr!!!
	if (iStream.eof())iStream.close();
	if (iStream.is_open()) {
		//iStream >> line;
		std::getline(iStream, line);
		++lineIndex;
	}
	else
		line.clear();
	return line;
}
bool FileManager::Open(const char* cFilePath) {
	if (iStream.is_open())iStream.close();
	iStream.open(cFilePath, std::ios::in);
	return iStream.is_open();
}
bool FileManager::CanRead() {
	return iStream.is_open() && !iStream.eof();
}
