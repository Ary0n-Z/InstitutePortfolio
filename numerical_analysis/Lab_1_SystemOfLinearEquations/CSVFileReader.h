#pragma once
#include <vector>
#include <fstream>

using std::ifstream;
using std::vector;

class CSVFileReader
{
private:
	const char* filepath = nullptr;
	std::streamoff lines(ifstream& f);
public:
	CSVFileReader(const char* filepath);
	~CSVFileReader();
	vector<vector<float>> readLinearSystem();
	void changeFile(const char* newFilepath);
	static bool isFileExist(const char* filepath);
};

