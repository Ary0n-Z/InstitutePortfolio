#include "LinearSystemElimination.h"
#include "CSVFileReader.h"
#include "MatrixFunctionsh.h"
#include <string>
#include <iostream>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

using namespace std;

vector<vector<float>> linearSystem;

void printLinearSystem() {
	if (!linearSystem.empty()) {
		const auto itEnd = linearSystem.end();
		for (auto it = linearSystem.begin(); it < itEnd; ++it) {
			const auto columns = (*it).size() - 1;
			cout << (*it)[0] << "x1";
			for (int i = 1; i < columns; i++) {
				cout << " + " << (*it)[i] << 'x' << i + 1;
			}
			cout << " = " << (*it)[columns] << endl;
		}
	}
	else 
		cout << "not selected\n";
}
void openFile() {
	string filepath;
	cout << "Enter file name > ";
	cin >> filepath;
	if (!CSVFileReader::isFileExist(filepath.c_str())) {
		cout << " Invalid file path!\n";
		getchar();
		system("PAUSE");
	}
	else {
		CSVFileReader reader(filepath.c_str());
		linearSystem = reader.readLinearSystem();
	}
}
void printMenu() {
	cout << "1) Open File\n2) Evaluate\n3) Matrix params\n4) Exit\n\nCurrent linear system:\n";
	printLinearSystem();
	cout << endl;
}
void Evaluate() {
	if (!linearSystem.empty()) {
		//Gauss
		auto t1 = Clock::now();
			//auto X = GaussianElimination(linearSystem);
		vector<vector<double>> a = { {2,-1,-1},{1,3,-2},{1,2,3} };
		vector<double> b = {5,7,10};

		auto X = Gauss(a,b);
		auto t2 = Clock::now();
		cout << " Gaussian elimination result:\n";
		int i = 1;
		for (auto x : X)
			cout << 'x' << i++ << " = " << x << "; ";
		std::cout << "Gauss time: "
			<< std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
			<< " nanoseconds\n\n";
		//SOR
		float relaxParam = 0;
		cout << "relaxation param =";
		cin >> relaxParam;
		/*while (relaxParam > 1 || relaxParam < 0) {
			cout << "relaxation param must be between 0 and 1\nrelaxation param [0:1] =";
			cin >> relaxParam;
		};*/
		cout << "accuracy = ";
		float acc;
		int iterationCount = 0;
		cin >> acc;
		t1 = Clock::now();
		//X = SOR(linearSystem , relaxParam, acc, &iterationCount);
		t2 = Clock::now();
		cout << " SOR result:\n";
		i = 1;
		for (auto x : X)
			cout << 'x' << i << " = " << x << "; ";
		std::cout << "Iteration count = "<< iterationCount << "; SOR time: "
			<< std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
			<< " nanoseconds\n";
	}
	else
		cout << " no linear system selected\n";
	system("PAUSE");

}
void MatrixParams() {
	if (!linearSystem.empty()) {
		cout << "Cond(A) = " << ExperementalConditionNumber(linearSystem) << endl << "Det(A) = " << Det(linearSystem) << endl;
	}
	else
		cout << " no linear system selected\n";
	system("PAUSE");

}

int main() {
	bool run = true;		
	int num = 0;
	do {
		system("cls");
		printMenu();
		cout << " > ";
		cin >> num;
		switch (num) {
			case 1: openFile(); break;
			case 2: Evaluate(); break;
			case 3: MatrixParams(); break;
			case 4: run = false;
		}
	} while (run);
}
