#pragma once
#include <vector>
using std::vector;

unsigned short GaussianForwardElimination(vector<vector<float>> &a);
//vector<float> GaussianElimination(vector<vector<float>> a);
vector<float> SOR(vector<vector<float>> A, float  relaxParam, float acc, int* iterationCount);
vector<double> Gauss(vector<vector<double>>& A, vector<double>& B);