#include "LinearSystemElimination.h"

using namespace std;
typedef short ushort;

unsigned short GaussianForwardElimination(vector<vector<float>> &A) {
	size_t i, j;
	size_t matrixSize = A.size();
	ushort countOfReplace = 0;
	for (i = 1; i < matrixSize; ++i) {
		// selection of the main element
		ushort l = i - 1;
		for (size_t m = i; m < matrixSize; ++m) {
			if (fabs(A[m][i - 1]) > fabs(A[l][i - 1]))
				l = m;
		}
		if (l != (i - 1)) {
			auto temp = A[i - 1];
			A[i - 1] = A[l];
			A[l] = temp;
			++countOfReplace;
		}

		for (j = i; j < matrixSize; ++j) {//rows
			// row j - row i - 1 * m
			float m =
				A[j][i - 1] / // elem under duagonal
				A[i - 1][i - 1]; // diagonale
			for (size_t k = 0; k < matrixSize + 1; ++k)// colomn iteration
				A[j][k] -= // row j; each elem
				m * A[i - 1][k]; // prev row * m; each elem
		}
	}
	return countOfReplace;
}


vector<float> GaussianBackSubstitution(const vector<vector<float>> &A) {
	ushort matrixSize = A.size();
	ushort BIndex = matrixSize;
	vector<float> X(matrixSize);
	for (int i = matrixSize - 1; i >= 0; --i) {
		X[i] = A[i][BIndex] // B in AX=B
			/ A[i][i]; // most left non-zero element
		for (int j = matrixSize - 1; j > i; --j)
			X[i] = X[i] - A[i][j] * X[j] / A[i][i];
	}
	return X;
}
vector<float> GaussianElimination(vector<vector<float>> A) {
	// forward elimination
	GaussianForwardElimination(A);
	// back substitution
	return GaussianBackSubstitution(A);
}

//Successive over - relaxation
float Error(vector<float> A, vector<float> B){
	float temp;
	float error = fabs(A[0] - B[0]);
	for (int i = 1; i < A.size(); i++) {
		temp = fabs(A[i] - B[i]);
		if (temp > error)
			error = temp;
	}
	return error;

}
vector<float> SOR(vector<vector<float>> A, float  relaxParam,float acc,int* iterationCount) {
	size_t matrixSize = A.size();
	size_t BIndex = matrixSize;
	vector<float> X(matrixSize,0),XPrev(matrixSize,0);
	do{
		XPrev = X;
		//iteration
		for (size_t i = 0; i < matrixSize; ++i){
			float var = 0;
			//sum of left from diagonale elements 
			for (size_t j = 0; j < i; ++j)
				var += (A[i][j] * X[j]);
			//sum of right from diagonale elements
			for (size_t j = i + 1; j < matrixSize; ++j)
				var += (A[i][j] * XPrev[j]);
			//new X value
			X[i] = (A[i][BIndex] - var) / A[i][i];
			// + relax offset
			X[i] = relaxParam * X[i] + (1 - relaxParam)*XPrev[i];
		}
		(*iterationCount)++;
	} while (Error(X,XPrev) > acc);
	return X;
}