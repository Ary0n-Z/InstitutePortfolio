#pragma once
#include <vector>
#include "Point.h"

using std::vector;
vector<Point> LeastSquaresPolynomialApprox(const vector<Point>& XY, unsigned short degree, float step);

vector<Point> BesselPolynomialsApproximation(vector<Point>& XY, unsigned short degree, float step);