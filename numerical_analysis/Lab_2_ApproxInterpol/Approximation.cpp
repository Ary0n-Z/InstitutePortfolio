#include "LinearSystemElimination.h"
#include "Approximation.h"
#include <iostream>
#include <math.h>

using namespace std;

double Approx(double(*basis)(double x, double degree), float x, vector<float> &a) {
	double result = 0;
	for (int i = 0; i < a.size(); i++)
		result += basis(x, i)*a[i];
	return result;
}
vector<Point> LeastSquaresPolynomialApprox(const vector<Point>& XY, unsigned short degree, float step) {
	std::cout << " LeastSquaresPolynomialApprox:\n";
	vector<vector<float>> AB(degree + 1);
	for (int i = 0; i < degree + 1; i++) { //row iterator
		AB[i].resize(AB.size() + 1);
		for (int k = 0; k < degree + 1; k++) { //column iterator, except B col
			for (int j = 0; j < XY.size(); j++) { //point iterator
				AB[i][k] += pow(XY[j].x, i) * pow(XY[j].x, k);
			}
		}
		for (int k = 0; k < XY.size(); k++) {
			AB[i][AB.size()] += XY[k].y * pow(XY[k].x, i);
		}

	}
	std::cout << "Approx order(degree + 1) = " << degree + 1 << "\nLinear System:\n";
	for (auto it = AB.begin(); it < AB.end(); ++it) {
		for (auto jt = (*it).begin(); jt < --(*it).end(); ++jt) {
			std::cout << *jt << " ";
		}
		std::cout << " = " << *(--(*it).end()) << '\n';
	}
	auto A = GaussianElimination(AB);// A coeff
	cout << "A coeff:\n";
	for (float a : A)
		cout << a << " ";
	cout << endl;
	vector<Point> ps;
	//ps.reserve((XY[XY.size() - 1].x - XY[0].x) / step + 1.5);
	int j = 0;
	for (double i = XY[0].x; i <= XY[XY.size() - 1].x; i += step, j++) {
		ps.push_back({ i,Approx(pow,i,A) });
	}
	ps.push_back({ XY[XY.size() - 1].x,Approx(pow,XY[XY.size() - 1].x,A) });
	return ps;
}


void transformX(vector<Point>& XY, float left, float right) {
	for (auto it = XY.begin(); it < XY.end(); it++)
		(*it).x = 2 * (((*it).x - left) / (right - left)) - 1;
}
void unTransformX(vector<Point>& XY, float left, float right) {
	for (auto it = XY.begin(); it < XY.end(); it++)
		(*it).x = (right + left) / 2.0 + (right - left) / 2.0*(*it).x;
}
double BesselPolynomial(double x, unsigned int degree) {
	if (degree == 0) return 1.0;
	if (degree == 1) return 2.0*x;
	return 2.0*x*BesselPolynomial(x, degree - 1) - BesselPolynomial(x, degree - 2);
}

double BesselApprox(float x, vector<float> &a) {
	double result = 0;
	for (unsigned int i = 0; i < a.size(); i++)
		result += BesselPolynomial(x, i)*a[i];
	return result;
}

vector<Point> BesselPolynomialsApproximation(vector<Point>& XY, unsigned short degree, float step) {
	cout << "\n BesselPolynomialsApproximation:\n";
	vector<float> A(degree+1);
	float left = XY[0].x, right = XY[XY.size() - 1].x;
	transformX(XY, left, right);
	//step = 2 * ((step - left) / (right - left)) - 1;
	for (unsigned int i = 0; i < degree+1; i++) {
		float numerator = 0, denominator = 0;
		for (unsigned int j = 0; j < XY.size(); j++) {
			float U = BesselPolynomial(XY[j].x, i);
			numerator += XY[j].y*U;
			denominator += U * U;
		}
		A[i] = numerator / denominator;
	}
	//unTransformX(XY, left, right);
	vector<Point> ps;
	ps.reserve((XY[XY.size() - 1].x - XY[0].x) / step + 1.5);
	int j = 0;
	double temp = 0;
	cout << " Bessel polynom values:\n";
	for (double i = XY[0].x; i <= XY[XY.size() - 1].x; i += step, j++) {
		temp = BesselApprox(i, A);
		ps.push_back({ i,temp });
		cout << "x = " << i << "  U(x,A) = " << temp << endl;
	}
	ps.push_back({ 1,BesselApprox(1, A) });
	unTransformX(ps, left, right);
	unTransformX(XY, left, right);
	return ps;
}
