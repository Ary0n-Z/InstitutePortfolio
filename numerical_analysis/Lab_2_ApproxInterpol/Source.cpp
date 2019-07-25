#include <vector>
using std::vector;
vector<double> Gauss(vector<vector<double>>& A, vector<double>& B) {
	unsigned int i, j, k, size = A.size();
	for (i = 1; i < size; ++i) {

		k = i - 1;
		for (size_t m = i; m < size; ++m) {
			if (fabs(A[m][i - 1]) > fabs(A[k][i - 1]))
				k = m;
		}
		if (k != (i - 1)) {
			auto temp = A[i - 1];
			A[i - 1] = A[k];
			A[k] = temp;
		}

		for (j = i; j < size; ++j) {
			double m =
				A[j][i - 1] / A[i - 1][i - 1]; 
			for (size_t k = 0; k < size + 1; ++k)
				A[j][k] -= m * A[i - 1][k]; 
			B[j] -= m * B[i - 1];
		}
	}
	vector<double> X(size);
	for (i = size - 1; i >= 0; --i) {
		X[i] = B[i]
			/ A[i][i];
		for (j = size - 1; j > i; --j)
			X[i] = X[i] - A[i][j] * X[j] / A[i][i];
	}
	return X;
}

struct Point { double x; double y; };
//Polynomial least squares
vector<Point> PLS(vector<double>& xpoints, vector<double>& ypoints, unsigned int degree, double step){
	unsigned int size = degree + 1;
	vector<vector<double>> A(size,vector<double>(size));
	vector<double> B(size);
	for (int i = 0; i < size; ++i) {
		for (int k = 0; k < size; ++k)
			for (int j = 0; j < size; j++)
				A[i][k] += pow(xpoints[j], i) * pow(xpoints[j], k);
		for (int k = 0; k < size; k++)
			B[i] += ypoints[k] * pow(xpoints[k], i);

	}
	vector<double> coeff = Gauss(A,B);

	vector<Point> approximatedPoints;
	double currentX = xpoints[0], PolyFunc;
	while (currentX < xpoints[xpoints.size() - 1]) {
		PolyFunc = 0;
		for (int i = 0; i < coeff.size(); i++)
			PolyFunc += pow(currentX, i)*coeff[i];
		approximatedPoints.push_back({ currentX, PolyFunc});
		currentX += step;
	}
	return approximatedPoints;
}
// Set point method
vector<Point> SPM(vector<double>& xpoints, vector<double>& ypoints, double step) {
	unsigned int size = xpoints.size();
	vector<vector<double>> A(size, vector<double>(size));
	vector<double> B(ypoints);
	for (unsigned int i = 0; i < size; i++)
		for (unsigned int j = 0; j < size; j++)
			A[i][j] = pow(xpoints[i], j);
	vector<double> coeff = Gauss(A, B);

	vector<Point> approximatedPoints;
	double currentX = xpoints[0], PolyFunc;
	unsigned int degree = 0;
	while (currentX < xpoints[xpoints.size() - 1]) {
		PolyFunc = 0;
		for (int i = 0; i < coeff.size(); i++)
			PolyFunc += pow(currentX, i)*coeff[i];
		approximatedPoints.push_back({ currentX, PolyFunc });
		currentX += step;
	}
	return approximatedPoints;
}


