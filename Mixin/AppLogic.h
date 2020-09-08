#pragma once
#include<vector>
using std::vector;

class Logic {
	int pSum;
public:
	int prefSum(const vector<int>& A);
	void reset();
};