#include "CSVFileReader.h"
#include <sys/stat.h>

CSVFileReader::CSVFileReader(const char* filepath)
{
	this->filepath = filepath;
}


CSVFileReader::~CSVFileReader()
{
}

std::streamoff CSVFileReader::lines(ifstream& f) {
	return std::count(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>(), '\n');
}

void CSVFileReader::changeFile(const char* newFilepath) {
	delete[] filepath;
	filepath = newFilepath;
}

bool CSVFileReader::isFileExist(const char* filepath) {
	struct stat buffer;
	return (stat(filepath, &buffer) == 0);
}
vector<Point> CSVFileReader::readTable() {
	vector<Point>  ab;
	ifstream f(filepath);
	if (f.is_open()) {
		double temp; char c;
		auto size = lines(f) + 1;
		f.seekg(0, f.beg);
		ab.resize(size);
		for (unsigned short i = 0; i < size; ++i) {
			if (f >> temp >> c)
				ab[i].x = temp;
			if (f >> temp >> c)
				ab[i].y = temp;
		}
		f.close();
	}
	return ab;
}

vector<vector<float>> CSVFileReader::readLinearSystem() {
	vector<vector<float>> ab;
	ifstream f(filepath);
	if (f.is_open()) {
		float temp; char c;
		auto size = lines(f) + 1;
		f.seekg(0, f.beg);

		ab.resize(size);		
		for (unsigned short i = 0; i < ab.size(); ++i) {
			ab[i].resize(size + 1);
			for (unsigned short j = 0; j < ab.size() + 1; ++j)
				if (f >> temp >> c)
					ab[i][j] = temp;
		}
		f.close();
	}
	return ab;
}