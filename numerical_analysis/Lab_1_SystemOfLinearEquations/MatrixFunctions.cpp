#include "MatrixFunctionsh.h"
#include"LinearSystemElimination.h"

float vectorNorm(const vector<float>& v) {
	/*float sumOfSquares = 0;
	for (float i : v)
		sumOfSquares += i * i;
	return sqrt(sumOfSquares);*/
	float sumOfModules = 0;
	for (auto i : v)
		sumOfModules += fabs(i);
	return sumOfModules;
}

float matrixNorm(const vector<vector<float>>& a) {
	float sumOfVectorNorm = 0;
	for (auto i : a)
		sumOfVectorNorm += vectorNorm(i);
	return sumOfVectorNorm;
}

float Det(vector<vector<float>> a) {
	auto k = GaussianForwardElimination(a);
	float det = 1;
	for (size_t i = 0; i < a.size(); ++i) {
		det *= a[i][i];
	}
	return ( k & 1) ? -det : det;
}

float ExperementalConditionNumber(
	vector<vector<float>> a) {
	//vector<float> b(a.size());

	//size_t maxBElemIndex = 0;
	//for (size_t i = 0; i < a.size(); i++) {
	//	b[i] = a[i][a.size()];
	//	if (fabs(b[maxBElemIndex]) < fabs(b[i]))
	//		maxBElemIndex = i;
	//}
	//// 1
	//float nB = vectorNorm(b);
	////2
	////auto X_1 = Gauss(a);
	////float nX_1 = vectorNorm(X_1);
	////3
	//vector<float>delta_B(b.size(), 0);
	//delta_B[maxBElemIndex] += 0.01*b[maxBElemIndex];
	//a[maxBElemIndex][a.size()] += delta_B[maxBElemIndex];
	//float nB_delta = vectorNorm(delta_B);
	////4
	////auto X_2 = GaussianElimination(a);
	//for (size_t i = 0; i < X_2.size(); i++)
	//	X_2[i] -= X_1[i];
	//float nX_delta = vectorNorm(X_2);
	//return (nX_delta*nB) / (nX_1 *  nB_delta);
	return 0;
}
